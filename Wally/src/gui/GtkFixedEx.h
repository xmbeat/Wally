#ifndef GTKFIXEDEX_H
#define GTKFIXEDEX_H
#include "GtkContainerEx.h"

class GtkFixedEx: public GtkContainerEx
{
    public:
        GtkFixedEx() {
            create();
        }
        virtual operator GtkFixed*(){return (GtkFixed *) getWidget();}
        virtual ~GtkFixedEx() {}
        virtual void create()
        {
            setWidget(gtk_fixed_new());
        }
        virtual void add(GtkWidgetEx *widget, int x, int y)
        {
            add(widget->getWidget(), x, y);
        }
        virtual void add(GtkWidget* widget, int x, int y)
        {
            gtk_fixed_put(GTK_FIXED(getWidget()), widget, x, y);
        }

};

#endif // GTKFIXEDEX_H
