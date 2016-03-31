/*
 * Controller.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <gui/ClassControls.h>
#include <stdio.h>
#include <stdlib.h>
#include "WallpaperManager.h"
#include "ProfileManager.h"
#include <Utils/MapString.h>
#include <Utils/TreeSet.h>
#include <Utils/File.h>
#include <string.h>
#include <Utils/Thread.h>
#include <IPC/Process.h>

enum {
	COL_PATH, COL_PIXBUF, N_COLS
};

GtkIconView *icon_view;

class Controller: public GtkEventWatcher{
public:
	void setVisible(bool value){
		mVentana->setVisible(value);
		if (value){
			mVentana->present();
		}
	}

	Controller(int argc, char**argv):mProfile(-1){
		//Para poder manejar hilos
		//g_thread_init(NULL);
		gdk_threads_init();
		gtk_init(&argc, &argv);
		mWallpaper = new WallpaperManager();
		mBuilder = new GtkBuilderEx();
		mCurrentImages = new ArrayList<String>();
		mProfileManager = new ProfileManager(File::getUserFolder(NULL) + "/.wally", "profile" );
		GtkBuilderEx &builder = *mBuilder;
		//Obtenemos la ruta absoluta al archivo desktop.png
		String exePath = Process::getPathToExeFile(Process::getPID());
		File icon = File(exePath + "/../resources/desktop.png");
		File xml = File(exePath + "/../resources/interface.xml");
		//Cargamos la interfaz gráfica
		if (!builder.addFromFile(xml.getAbsolutePath())){
			fprintf(stderr, "File not found: %s\n", xml.getAbsolutePath().c_str());
			exit(-1);
		}
		//Obtenemos la ventana para manejar el evento destroy
		mVentana = new GtkWindowEx(builder["main_window"]);
		mVentana->actToWindowCloseEvent(this);
		mVentana->setIconFromFile(icon.getAbsolutePath());
		//Obtenemos los botones y los asignams al arreglo
		mButtons.add(new GtkButtonEx(builder["btn_ok"]));
		mButtons.add(new GtkButtonEx(builder["btn_add"]));
		mButtons.add(new GtkButtonEx(builder["btn_remove"]));
		mButtons.add(new GtkButtonEx(builder["btn_selectall"]));
		mButtons.add(new GtkButtonEx(builder["btn_add_profile"]));
		mButtons[0]->actToClickEvent(this);
		mButtons[1]->actToClickEvent(this);
		mButtons[2]->actToClickEvent(this);
		mButtons[3]->actToClickEvent(this);
		mButtons[4]->actToClickEvent(this);
		mComboBox = new GtkComboBoxEx(builder["cmb_profile"]);
		mComboBox->actToChangeEvent(this);
		//Guardamos las referencias a los widgets q necesitamos
		mStatusBar = new GtkStatusBarEx(builder["status_bar"]);
		mSpinner = new GtkSpinButtonEx(builder["sbtn_delay"]);
		mRandom = new GtkCheckButtonEx(builder["chk_shuffle"]);
		//Creamos el list store, para almacenar las imagenes
		mListStore = new GtkListStoreEx(N_COLS, G_TYPE_STRING, GDK_TYPE_PIXBUF);
		icon_view = GTK_ICON_VIEW(builder.getObject("icon_view"));
		gtk_icon_view_set_model(icon_view, *mListStore);
		gtk_icon_view_set_pixbuf_column(icon_view, COL_PIXBUF);
		gtk_icon_view_set_selection_mode(icon_view, GTK_SELECTION_MULTIPLE);


		//Creamos el menu que debe tener el indicador
		GtkMenuEx menu("Wally");
		mMenuItems.add(new GtkMenuItemEx("Abrir Wally"));
		mMenuItems.add(new GtkMenuItemEx("Fondo Siguiente"));
		mMenuItems.add(new GtkMenuItemEx("Fondo Anterior"));
		mMenuItems.add(new GtkMenuItemEx("Salir"));
		menu.add(mMenuItems[0]);
		menu.addSeparator();
		menu.add(mMenuItems[1]);
		menu.add(mMenuItems[2]);
		menu.addSeparator();
		menu.add(mMenuItems[3]);
		mMenuItems[0]->actToActivateEvent(this);
		mMenuItems[1]->actToActivateEvent(this);
		mMenuItems[2]->actToActivateEvent(this);
		mMenuItems[3]->actToActivateEvent(this);
		menu.showAll();

		//Creamos el indicador de aplicación, en sustituto del area de notificaciones
		mIndicator = new GtkAppIndicatorEx ("Wally", icon.getAbsolutePath());
		mIndicator->setStatus(APP_INDICATOR_STATUS_ACTIVE);
		mIndicator->setAttentionIcon(icon.getAbsolutePath());
		mIndicator->setMenu((GtkMenu*)menu);

		loadConfig();

	}

	void loadConfig(){
		mProfileManager->clear();
		if (mProfileManager->load("config")){
			ArrayList<String> *themes = mProfileManager->get("Theme");
			if (themes){
				mThemes.clear();
				for (int i = 0; i < themes->size(); i++){
					int index = themes->get(i).inString(":");
					if (index >= 0){
						//Obtenemos el id y el nombre de cada perfil
						String key = themes->get(i).substring(0, index);
						String *data = new String(themes->get(i).substring(index+1));
						//Lo agregamos a la lista de temas q teniamos
						String *prev = mThemes.put(key, data);
						if (prev){
							delete prev;
						}
					}
				}
			}
		}
	}


	GdkPixbuf* createThumb(const char* image, int maxWidth, int maxHeight){
		GError *err = NULL;
		GdkPixbuf *img = gdk_pixbuf_new_from_file(image, &err);
		if (err){
			fprintf(stderr, "Error al abrir: %s\nDetalle: %s\n",(const char*) image, err->message);
			g_error_free(err);
			return NULL;
		}
		else{
			//Procedimientos para escalar una imagen
			int w = gdk_pixbuf_get_width (img);
			int h = gdk_pixbuf_get_height (img);
			int nw, nh;
			//Modificamos en relación al ancho
			if ( ((float)maxWidth / (float)maxHeight) > ((float)w/(float)h) ){
				nh = maxHeight;
				nw = nh * w / h;
			}
			//Modificamos en relación al ancho
			else{
				nw = maxWidth;
				nh = nw * h / w;
			}
			//Escalamos la imagen
			GdkPixbuf * scaled = gdk_pixbuf_scale_simple(img, nw, nh, GDK_INTERP_BILINEAR);
			g_object_unref(img);
			return scaled;
		}
	}

	//Clase que se encarga de cargar las imagenes al iconview
	class ImageLoader: public Thread{
	private:
		bool mSave;
		ArrayList<String> mImages;
		Controller* mController;
	public:
		ImageLoader(ArrayList<String> images, Controller* controller, bool save){
			mImages = images;
			mController = controller;
			mSave = save;
		}
		void run(){
			for (int i = 0; i < mImages.size(); i++){
				String image = mImages[i];
				if (mController->mCurrentImages->indexOf(image) == -1){
					gdk_threads_enter(); //Bloqueamos el bucle principal
					String message = String("Agregando: [") + image + "]";
					int contextId = mController->mStatusBar->getContextId("progress");
					int messageId = mController->mStatusBar->push(contextId, message);
					gdk_threads_leave();
					//Creamos la imagen en miniatura que debe ir en el iconview
					GdkPixbuf *thumb = mController->createThumb(image, 100, 80);
					if (thumb){
						gdk_threads_enter();
						mController->mListStore->add(-1, COL_PATH, image.c_str(), COL_PIXBUF, thumb, -1);
						mController->mCurrentImages->add(image);
						gdk_threads_leave();
					}
					gdk_threads_enter();
					mController->mStatusBar->remove(contextId, messageId);
					gdk_threads_leave();
				}
			}

			gdk_threads_enter();
			mController->mWallpaper->setImages(*(mController->mCurrentImages));
			mController->mWallpaper->setRandom(mController->mRandom->isChecked());
			mController->mWallpaper->setDelay(mController->mSpinner->getIntValue());
			if (mController->mProfile > 1){
				mController->saveProfile(mController->mProfile, *(mController->mCurrentImages), mController->mRandom->isChecked(), mController->mSpinner->getValue());
			}
			for (int i = 0; i < mController->mButtons.size(); i++){
				mController->mButtons[i]->setEnabled(true);
			}
			mController->mComboBox->setEnabled(true);
			gdk_threads_leave();
		}
	};

	//Agrega imagenes al arbol binario y al iconview, debe ser llamado en un hilo diferente al gui
	void addImages(ArrayList<String>  &images, bool save = false){
		for (int i = 0; i < mButtons.size(); i++){
			mButtons[i]->setEnabled(false);
		}
		mComboBox->setEnabled(false);
		ImageLoader *loader = new ImageLoader(images, this, save);
		loader->setDeleteReference(true); //Se eliminara el objeto despues de terminar la ejecucion
		loader->start();
	}

	//Clase que se encarga de leer los mensajes que otros procesos iguales a este le mandan
	class MessageReader: public Thread{
	private:
		String mMessage;
		Controller *mController;
	public:
		MessageReader(Controller *controller, String message){
			mController = controller;
			mMessage = message;
		}
		void run(){
			printf("%s\n", mMessage.c_str());
			if (mMessage.equals("restore")){
				gdk_threads_enter();
				mController->setVisible(true);
				gdk_threads_leave();
			}
			else if (mMessage.substring(0, 3).equals("add")){
				ArrayList<String> images;
				int start = 4;
				for (int i = 4; i < mMessage.length(); i++){
					if (mMessage.charAt(i) == ':'){
						images.add(mMessage.substring(start, i - start));
						start =  i + 1;
					}
				}
				if (start < mMessage.length()){
					images.add(mMessage.substring(start));
				}
				gdk_threads_enter();
				mController->addImages(images, true);

				gdk_threads_leave();
			}
		}


	};

	void onMessageArrived(int key){
		SHMemory memory(key, 0);
		memory.setRemovable(true); //Se removera cuando todos los procesos dejen de hacer referencia
		memory.lock(); //Bloqueamos la memoria para q solo uno pueda tener acceso y evitar race condition
		MessageReader *reader = new MessageReader(this, (char*) memory);
		memory.unlock();
		reader->setDeleteReference(true); //Se eliminara la referencia al terminar de correr
		reader->start();

	}
	/**
	 * Ejecutado al cerrar la ventana principal
	 * @object[in] La ventana que recibió el mensaje de cierre
	 * @user_data[in] Datos adicionales al mensaje enviados por el programador
	 */
	bool onWindowClose(GtkWidget *widget, GdkEvent *event){
		mVentana->setVisible(false);
		return true;
	}

	/*
	 * Ejecutado cuando los botones son presionados
	 */
	void onClick(GtkWidget* widget){
		//Ok button
		if (*mButtons[0] == widget){
			mWallpaper->setImages(*mCurrentImages);
			mWallpaper->setRandom(mRandom->isChecked());
			mWallpaper->setDelay(mSpinner->getIntValue());
			if (mProfile > 1){
				saveProfile(mProfile, *mCurrentImages, mRandom->isChecked(), mSpinner->getValue());
			}
		}
		//Add button
		else if (*mButtons[1] == widget){
			if (mProfile > 1){
				GtkFileChooserDialogEx dialog("Abrir imágenes", *mVentana, GTK_FILE_CHOOSER_ACTION_OPEN,
						GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
				GtkFileFilterEx filter;
				filter.setName("Imágenes Aceptadas");
				filter.addPixbufFormats();
				dialog.setFilter(filter);
				dialog.setSelectMultiple(true);

				if (dialog.run() == GTK_RESPONSE_ACCEPT){
					ArrayList<String> images = dialog.getFilenames();
					addImages(images);
				}

				dialog.destroy();
			}
			else{
				showErrorMessage("Seleccione un perfil personalizado para agregar imágenes", "Error");
			}
		}
		//Remove button
		else if (*mButtons[2] == widget){
			if (mProfile > 1){
				removeSelectedItems();
			}
			else{
				showErrorMessage("Seleccione un perfil personalizado para eliminar imágenes", "Error");
			}
		}
		//Select all button
		else if (*mButtons[3] == widget){
			gtk_icon_view_select_all(icon_view);
		}
		//Add profile button
		else if (*mButtons[4] == widget){
			GtkDialogEx dialog;
			dialog.addButton(GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);
			dialog.addButton(GTK_STOCK_OK, GTK_RESPONSE_ACCEPT);
			if (dialog.run() == GTK_RESPONSE_ACCEPT){

			}
			dialog.destroy();
		}
	}
	//https://mail.gnome.org/archives/gtk-app-devel-list/2010-August/msg00058.html
	void removeSelectedItems(){
		GList *elements, *iter;
		//Obtenemos una lista donde se encuentran los elementos seleccionados
		elements = gtk_icon_view_get_selected_items (icon_view);
		/* Convert to row references for safe removal */
		for (iter = elements; iter; iter = g_list_next (iter))
		{
			GtkTreeRowReference *ref;
			GtkTreePath *path = (GtkTreePath *)iter->data;

			ref = gtk_tree_row_reference_new (*mListStore, path);
			gtk_tree_path_free (path);
			iter->data = ref;
		}

		/* Remove now */
		for (iter = elements; iter; iter = g_list_next (iter))
		{
			GtkTreeRowReference *ref = (GtkTreeRowReference *)iter->data;
			GtkTreePath *path = gtk_tree_row_reference_get_path(ref);
			GtkTreeIter remove_me;
			gtk_tree_model_get_iter (*mListStore, &remove_me, path);
			gtk_tree_path_free (path);

			gchar* img_path;
			GdkPixbuf* image;
			gtk_tree_model_get(*mListStore, &remove_me, COL_PATH, &img_path, COL_PIXBUF, &image, -1);
			printf("Removing %s\n", img_path);
			String imgPath(img_path);
			int index = mCurrentImages->lastIndexOf(imgPath);
			mCurrentImages->remove(index);
			mListStore->remove(&remove_me);
			gtk_tree_row_reference_free (ref);
			g_free(img_path);
		}

		g_list_free (elements);
	}

	/**
	 * Ejecutado al cambiar de seleccion en el combobox
	 * @combo[in] El combo box que recibió el mensaje.
	 */
	void onChange(GtkWidget *combo)
	{
		int active = mComboBox->getActive();
		changeProfile(active);
	}

	void changeProfile(int profile){
		//Borramos los paths de las imagenes
		mCurrentImages->clear();
		//Borramos las imagenes del iconview
		mListStore->clear();
		mProfile = profile;
		switch(profile){
			case 0:{
				loadImagesFromFolder("/usr/share/backgrounds");
				break;
			}
			case 1:{
				String folder = File::getUserFolder("PICTURES");
				if (folder != ""){
					loadImagesFromFolder(folder);
				}
				break;
			}
			default:{
				loadUserProfile(profile);
				break;
			}
		}

	}

	void loadImagesFromFolder(String folder){
		File carpeta = File(folder);
		if (carpeta.isDirectory()){
			ArrayList<String> files = carpeta.list(File::ONLY_FILES);
			for (int i = 0; i < files.size(); i++){
				files[i] = carpeta.getAbsolutePath() + "/" + files[i];
			}
			addImages(files);
		}
	}

	bool loadUserProfile(int index){
		mProfileManager->clear();
		if (mProfileManager->load(index)){

			if (mProfileManager->getString("Random") == "True"){
				mRandom->setChecked(true);
			}
			else{
				mRandom->setChecked(false);
			}
			if (mProfileManager->getString("Delay") != ""){
				mSpinner->setValue(String::strVal(mProfileManager->getString("Delay")));
			}
			ArrayList<String> *images = mProfileManager->get("Images");
			if (images)
				addImages(*images);
		    return true;
		}
		return false;
	}

	bool saveProfile(int index, ArrayList<String> &images, bool random, double delay){

		mProfileManager->clear();
	    mProfileManager->add("Images", images);
	    mProfileManager->addString("Random", random?"True":"False");
	    mProfileManager->addString("Delay", String::strStr(delay));
	    if (!mProfileManager->save(index)){
	    	showErrorMessage("No se pudo guardar el perfil", "Error guardando");
	    }
	    return true;
	}

	void showErrorMessage(const char* message, const char* title = NULL){
		GtkDialogEx dialog(gtk_message_dialog_new(*mVentana,
				GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message));
		dialog.setText(title);
		dialog.run();
		dialog.destroy();
	}

	/**
	 * Ejecutado al presionar los menus del appindicator
	 */
	void onActivate(GtkWidget* menu){
		if (*mMenuItems[0] == menu){
			mVentana->setVisible(true);
			mVentana->present();
		}
		else if (*mMenuItems[1] == menu){
			mWallpaper->next();
		}
		else if (*mMenuItems[2] == menu){
			mWallpaper->previous();
		}
		else if (*mMenuItems[3] == menu){
			gtk_main_quit();
		}
	}

	virtual ~Controller(){
		mMenuItems.clearAndDelete();
		mButtons.clearAndDelete();
		delete mProfileManager;
		delete mBuilder;
		delete mIndicator;
		delete mVentana;
		delete mComboBox;
		delete mWallpaper;
		delete mListStore;
	}
private:
	GtkBuilderEx *mBuilder;
	GtkAppIndicatorEx *mIndicator;
	GtkStatusBarEx *mStatusBar;
	ArrayList<GtkMenuItemEx*> mMenuItems;
	ArrayList<GtkButtonEx*> mButtons;
	GtkWindowEx *mVentana;
	GtkComboBoxEx *mComboBox;
	GtkListStoreEx *mListStore;
	GtkSpinButtonEx *mSpinner;
	GtkCheckButtonEx *mRandom;
	WallpaperManager *mWallpaper;
	ProfileManager *mProfileManager;
	ArrayList<String> *mCurrentImages;
	MapString<String*> mThemes;
	int mProfile;
};



#endif /* CONTROLLER_H_ */
