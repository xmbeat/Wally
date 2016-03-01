#ifndef GTKCONTAINEREX_H
#define GTKCONTAINEREX_H
#include "GtkWidgetEx.h"

class GtkContainerEx: public GtkWidgetEx
{
    public:
        GtkContainerEx() {}
        virtual operator GtkContainer*()
        {
            return (GtkContainer*)getWidget();
        }
        virtual ~GtkContainerEx() {}
        virtual void setBorderWidth(int val)
        {
            gtk_container_set_border_width(GTK_CONTAINER(getWidget()), val);
        }
        virtual void add(GtkWidgetEx *widget)
        {
            add(widget->getWidget());
        }
        virtual void add(GtkWidget *widget)
        {
            gtk_container_add(GTK_CONTAINER(getWidget()), widget);
        }
    protected:
    private:
};

#endif // GTKCONTAINEREX_H
