#ifndef GTKCOMBOBOXEX_H
#define GTKCOMBOBOXEX_H
#include "GtkContainerEx.h"

class GtkComboBoxEx: public GtkContainerEx
{
    public:
		GtkComboBoxEx(bool noInstance)
		{}
        GtkComboBoxEx(){
            setWidget(gtk_combo_box_new_text());
        }
        GtkComboBoxEx(GtkWidget* widget){
        	setWidget(widget);
        }
        virtual operator GtkComboBox*()
        {
            return GTK_COMBO_BOX(getWidget());
        }
        virtual ~GtkComboBoxEx(){}
        virtual int getActive()
        {
            return gtk_combo_box_get_active(*this);
        }
        virtual void setActive(int index)
        {
            gtk_combo_box_set_active(*this, index);
        }
        virtual String getActiveText(int index)
        {
            char *c = gtk_combo_box_get_active_text(*this);
            if (c)
            {
                String ret(c);
                g_free(c);//liberamos
                return ret;
            }
            return "";
        }
        virtual void addText(const char *text, int index = -1)
        {
            if (index>=0)
                gtk_combo_box_insert_text(*this, index, text);
            else
                gtk_combo_box_append_text(*this,text);
        }
        virtual void appendText(const char* text){
        	gtk_combo_box_append_text(*this, text);
        }
        virtual void insertText(int index, const char* text){
        	gtk_combo_box_insert_text(*this, index, text);
        }
        virtual void removeText(int index)
        {
            gtk_combo_box_remove_text(*this, index);
        }
        virtual void setCanGetFocus(bool value)
        {
            gtk_combo_box_set_focus_on_click (*this, value);
        }
        virtual bool canGetFocus()
        {
            return gtk_combo_box_get_focus_on_click(*this);
        }
        virtual int getListCount()
        {
        	return gtk_tree_model_iter_n_children(
        			gtk_combo_box_get_model(*this), NULL);
        }
        virtual void setButtonSensitivity(GtkSensitivityType type){
        	gtk_combo_box_set_button_sensitivity(*this, type);
        }
        virtual GtkSensitivityType getButtonSensitivity(){
        	return gtk_combo_box_get_button_sensitivity(*this);
        }
        virtual void clear()
        {
            /*GtkTreeModel *store = gtk_combo_box_get_model(*this);
            if (store)
            	gtk_list_store_clear(GTK_LIST_STORE(store));*/
        	int len = getListCount();

        	for (int i = 0; i < len; i++)
        	{
        		removeText(0);
        	}
        }
        virtual void actToChangeEvent(GtkEventWatcher *listener)
        {
            g_signal_connect(getWidget(), "changed", G_CALLBACK(changeEvent), listener);
        }
    private:
        static void changeEvent(GtkWidget* combo, GtkEventWatcher *listener)
        {
            listener->onChange(combo);
        }
};

#endif // GTKCOMBOBOXEX_H
