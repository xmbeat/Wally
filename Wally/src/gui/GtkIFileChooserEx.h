#ifndef GTKIFILECHOOSEREX_H
#define GTKIFILECHOOSEREX_H
#include <Utils/ArrayList.h>
class GtkIFileChooserEx
{
public:
	virtual operator GtkFileChooser*() = 0;
	virtual void setAction(GtkFileChooserAction action)
	{
		gtk_file_chooser_set_action (*this, action);
	}
	virtual GtkFileChooserAction getAction()
	{
		return gtk_file_chooser_get_action(*this);
	}
	virtual void setLocalOnly(bool value)	
	{
		gtk_file_chooser_set_local_only(*this, value);
	}
	virtual bool getLocalOnly()
	{
		return gtk_file_chooser_get_local_only  (*this);
	}
	virtual void setSelectMultiple(bool value)
	{
		gtk_file_chooser_set_select_multiple(*this, value);
	}
	virtual bool getSelectMultiple()
	{
		return gtk_file_chooser_get_select_multiple(*this);
	}
	virtual void setShowHidden(bool value)
	{
		gtk_file_chooser_set_show_hidden (*this, value);
	}
	virtual bool getShowHidden()
	{
		return gtk_file_chooser_get_show_hidden (*this);
	}
	virtual void setDoOverwriteConfirmation(bool value)
	{
		gtk_file_chooser_set_do_overwrite_confirmation(*this, value);
	}
	virtual bool getDoOverWriteConfirmation()
	{
		return gtk_file_chooser_get_do_overwrite_confirmation(*this);
	}
	virtual void setCreateFolders(bool value)
	{
		gtk_file_chooser_set_create_folders(*this, value);
	}
	virtual bool getCreateFolders()
	{
		return gtk_file_chooser_get_create_folders(*this);
	}
	virtual void setFilename(const char* filename)
	{
		gtk_file_chooser_set_filename(*this, filename);
	}
	virtual String getFilename()
	{
		char* tmp = gtk_file_chooser_get_filename(*this);
		String ret(tmp);
		g_free(tmp);
		return ret;
	}
	virtual bool selectFilename(const char* filename)
	{
		return gtk_file_chooser_select_filename(*this, filename);
	}
	virtual void unSelectFilename(const char* filename)
	{
		gtk_file_chooser_unselect_filename(*this, filename);
	}
	virtual void selectAll()
	{
		gtk_file_chooser_select_all(*this);
	}
	virtual void unSelectAll()
	{
		gtk_file_chooser_unselect_all(*this);
	}
	virtual ArrayList<String> getFilenames()
	{
		ArrayList<String> ret;
		GSList *lista = gtk_file_chooser_get_filenames(*this);
		GSList *tmp = lista;
		while(tmp)
		{
			ret.add((const char*)(tmp->data));
			g_free(tmp->data);
			tmp = tmp->next;
		}
		g_slist_free(lista);
		return ret;
	}
	virtual void setCurrentName(const char*name)
	{
		gtk_file_chooser_set_current_name(*this, name);
	}		
	virtual void setCurrentFolder(const char*folder)
	{
		gtk_file_chooser_set_current_folder(*this, folder);
	}	
	virtual String getCurrentFolder()
	{
		char *tmp = gtk_file_chooser_get_current_folder(*this);
		String ret(tmp);
		g_free(tmp);
		return ret;
	}
	virtual bool addShortcutFolder(const char *folder)
	{
		GError *error;
		if (gtk_file_chooser_add_shortcut_folder(*this, folder, &error))
		{
			return true;
		}
		else{
			g_error_free(error);
			return false;
		}
	}
	virtual bool removeShortcutFolder(const char *folder)
	{
		GError *error;
		if (gtk_file_chooser_remove_shortcut_folder(*this,folder, &error))
		{
			return true;
		}
		else
		{	
			g_error_free(error);
			return false;
		}
	}
	virtual ArrayList<String> listShortcutFolders()
	{
		ArrayList<String> ret;
		GSList *lista = gtk_file_chooser_list_shortcut_folders(*this);
		GSList *tmp = lista;
		while(tmp)
		{
			ret.add((const char*)(tmp->data));
			g_free(tmp->data);
			tmp = tmp->next;
		}
		g_slist_free(lista);
		return ret;
	}
	virtual void setFilter(GtkFileFilter* filter){
		gtk_file_chooser_set_filter(*this, filter);
	}
};
#endif
