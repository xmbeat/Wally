#ifndef GTKLISTVIEWEX_H
#define GTKLISTVIEWEX_H
#include "GtkContainerEx.h"


class GtkListViewEx:public GtkContainerEx
{
    public:
        GtkListViewEx(GtkListStore* store)
        {
            setWidget(gtk_tree_view_new_with_model(GTK_TREE_MODEL(store)));
        }
        GtkListViewEx()
        {
            setWidget(gtk_tree_view_new());
        }

        virtual ~GtkListViewEx() {}
    protected:
    private:
};

#endif // GTKLISTVIEWEX_H
