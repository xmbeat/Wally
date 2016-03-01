#ifndef GTKENTRYEX_H
#define GTKENTRYEX_H
#include "GtkWidgetEx.h"
class GtkEntryEx: public GtkWidgetEx
{
    public:
        GtkEntryEx(){create();}
        GtkEntryEx(GtkWidget* widget){
        	setWidget(widget);
        }
        virtual operator GtkEntry*()
        {
            return GTK_ENTRY(getWidget());
        }
        virtual void create()
        {
            setWidget(gtk_entry_new());
        }
        virtual void setMaxLength(int val)
        {
            gtk_entry_set_max_length(*this, val);
        }
        virtual int getMaxLength()
        {
            return gtk_entry_get_max_length(*this);
        }
        virtual void setText(String text)
        {
            gtk_entry_set_text(*this ,text);
        }
        virtual String getText()
        {
            return gtk_entry_get_text(*this);
        }
        virtual void insertText(String text, int indexPos)
        {
            gtk_editable_insert_text(GTK_EDITABLE(getWidget()), text, -1, &indexPos);
        }
        virtual void setCursorPos(int index)
        {
            gtk_editable_set_position(GTK_EDITABLE(getWidget()), index);
        }
        virtual int getCursorPos()
        {
            return gtk_editable_get_position(GTK_EDITABLE(getWidget()));
        }
        virtual int getTextLength()
        {
            return gtk_entry_get_text_length(*this);
        }
        virtual void selectRegion(int start, int end)
        {
            gtk_editable_select_region(GTK_EDITABLE(getWidget()), start, end);
        }
        virtual void setPasswordChar(gunichar ch)
        {
            gtk_entry_set_invisible_char(*this, ch);
            gtk_entry_set_visibility(*this, ch!=0);
        }
        virtual gunichar getPasswordChar()
        {
            return gtk_entry_get_invisible_char(*this);
        }
        virtual void setEditable(bool value)
        {
            gtk_editable_set_editable(GTK_EDITABLE(getWidget()),value);
        }
        virtual bool isEditable()
        {
            return gtk_editable_get_editable(GTK_EDITABLE(getWidget()));
        }
        virtual void setAlignment(float value)
        {
            gtk_entry_set_alignment(*this, value);
        }
        virtual float getAlignment()
        {
            return gtk_entry_get_alignment(*this);
        }
        virtual void setOverwrite(bool val)
        {
            gtk_entry_set_overwrite_mode(*this, val);
        }
        virtual bool isOverwrite()
        {
            return gtk_entry_get_overwrite_mode(*this);
        }
        //IMPORTANTE PARA MANEJAR EVENTOS DE KEY gtk_entry_im_context_filter_keypress ()
        virtual ~GtkEntryEx(){}
};
#endif
