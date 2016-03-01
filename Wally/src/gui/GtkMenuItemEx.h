#ifndef GTKMENUITEMEX_H
#define GTKMENUITEMEX_H
#include "GtkContainerEx.h"
class GtkMenuItemEx: public GtkContainerEx
{
    public:

        GtkMenuItemEx(const char* caption = NULL, bool fromStock = false)
        {
            if (fromStock)
                setWidget(gtk_image_menu_item_new_from_stock(caption, NULL));
            else
                setWidget(gtk_menu_item_new_with_label(caption));
            setUseMnemonic(true);
        }
        virtual operator GtkMenuItem*()
        {
            return GTK_MENU_ITEM(getWidget());
        }


        virtual void setText(const char* text)
        {
            gtk_menu_item_set_label(*this, text);
        }
        virtual String getText()
        {
            return gtk_menu_item_get_label(*this);
        }
        virtual void setUseMnemonic(bool value)
        {
            gtk_menu_item_set_use_underline(*this, value);
        }
        virtual bool isMnemonic()
        {
            return gtk_menu_item_get_use_underline(*this);
        }
        virtual void add(GtkWidgetEx* submenu)
        {
            add(getWidget());
        }
        virtual void add(GtkWidget* submenu)
        {
            gtk_menu_shell_append(GTK_MENU_SHELL(getWidget()), submenu);
        }
        virtual ~GtkMenuItemEx() {}
        virtual void actToActivateEvent(GtkEventWatcher *listener)
        {
            g_signal_connect(getWidget(), "activate", G_CALLBACK(activateEvent), listener);
        }
    private:
        static void activateEvent(GtkMenuItem *menuItem, GtkEventWatcher *listener)
        {
            listener->onActivate(GTK_WIDGET(menuItem));
        }
};

#endif // GTKMENUITEMEX_H
