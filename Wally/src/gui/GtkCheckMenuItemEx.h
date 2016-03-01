#ifndef GTKCHECKMENUITEMEX_H
#define GTKCHECKMENUITEMEX_H
#include "GtkMenuItemEx.h"

class GtkCheckMenuItemEx: public GtkMenuItemEx
{
    public:
        virtual operator GtkCheckMenuItem*()
        {
            return GTK_CHECK_MENU_ITEM(getWidget());
        }
        GtkCheckMenuItemEx()
        {
            create();
        }
        GtkCheckMenuItemEx(String caption)
        {
            create(caption);
        }
        virtual void create(String caption = "")
        {
            setWidget(gtk_check_menu_item_new_with_label(caption));
        }
        virtual ~GtkCheckMenuItemEx() {}

        virtual bool isChecked()
        {
            return gtk_check_menu_item_get_active(*this);
        }
        virtual void setChecked(bool value)
        {
            gtk_check_menu_item_set_active(*this,value);
        }
        virtual bool isInconsitent()
        {
            return gtk_check_menu_item_get_inconsistent(*this);
        }
        virtual void setInconsistent(bool value)
        {
            gtk_check_menu_item_set_inconsistent(*this, value);
        }
        virtual void actToToggledEvent(GtkEventWatcher*listener)
        {
            g_signal_connect(getWidget(), "toggled", G_CALLBACK(toggledEvent), listener);
        }
    private:
        static void toggledEvent(GtkToggleButton*button, GtkEventWatcher *listener)
        {
            listener->onToggled(GTK_WIDGET(button));
        }
};

#endif // GTKCHECKMENUITEMEX_H
