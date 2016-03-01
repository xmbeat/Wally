#ifndef GTKMENUEX_H
#define GTKMENUEX_H
#include "GtkMenuItemEx.h"
class GtkMenuEx: public GtkContainerEx
{
    private:
        GtkMenuItemEx *menu;
    public:
        virtual operator GtkMenuItem*()
        {
            return GTK_MENU_ITEM(menu->getWidget());
        }
        virtual operator GtkMenu*()
        {
            return GTK_MENU(getWidget());
        }
        virtual ~GtkMenuEx()
        {
            delete menu;
        }
        GtkMenuEx(const char *caption = NULL)
        {
            menu = new GtkMenuItemEx(caption);
            setWidget(gtk_menu_new());
            gtk_menu_item_set_submenu(*menu, getWidget());
            setUseMnemonic(true);
        }
		virtual void popup(int button, int activateTime = gtk_get_current_event_time(), GtkMenuPositionFunc fun = NULL)
		{
			gtk_menu_popup(GTK_MENU(getWidget()), NULL, NULL, fun, NULL, button, activateTime);
		}
        virtual void setText(const char* text)
        {
            gtk_menu_item_set_label(*menu, text);
        }
        virtual String getText()
        {
            return gtk_menu_item_get_label(*menu);
        }
        virtual void setUseMnemonic(bool value)
        {
            gtk_menu_item_set_use_underline(*menu, value);
        }

        virtual bool isMnemonic()
        {
            return gtk_menu_item_get_use_underline(*menu);
        }
        virtual void add(GtkMenuItemEx *submenu)
        {
            add(*submenu);
        }

        virtual void add(GtkMenuItem *submenu)
        {
            gtk_menu_shell_append(GTK_MENU_SHELL(getWidget()), GTK_WIDGET(submenu));
        }
        virtual void add(GtkMenuEx *submenu)
        {
            GtkMenuItem* m = *submenu;
            add(m);
        }
        virtual void addSeparator()
        {
            gtk_menu_shell_append(GTK_MENU_SHELL(getWidget()),gtk_separator_menu_item_new());
        }

};
#endif
