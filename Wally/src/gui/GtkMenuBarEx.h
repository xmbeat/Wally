#ifndef GTKMENUBAREX_H
#define GTKMENUBAREX_H
#include "GtkMenuEx.h"
#include "GtkContainerEx.h"

class GtkMenuBarEx: public GtkContainerEx
{
    public:
        GtkMenuBarEx() {
            setWidget(gtk_menu_bar_new());
        }
        virtual operator GtkMenuBar*()
        {
            return GTK_MENU_BAR(getWidget());
        }
        virtual operator GtkMenuShell*()
        {
            return GTK_MENU_SHELL(getWidget());
        }

        virtual void add(GtkMenuEx *menu)
        {
            GtkMenuItem* m = *menu;
            add(m);
        }
        virtual void add(GtkMenuItem* menu)
        {
            gtk_menu_shell_append(*this, GTK_WIDGET(menu));
        }
        virtual ~GtkMenuBarEx() {}
    protected:
    private:
};

#endif // GTKMENUBAREX_H
