#ifndef GTKTOOLBAREX_H
#define GTKTOOLBAREX_H
#include "GtkContainerEx.h"
#include "GtkToolItemEx.h"
class GtkToolbarEx: public GtkContainerEx
{
    public:

        GtkToolbarEx(GtkToolbarStyle style = GTK_TOOLBAR_ICONS)
        {
            setWidget(gtk_toolbar_new());
			setStyle(style);
        }
		virtual void setStyle(GtkToolbarStyle style)
		{
			gtk_toolbar_set_style(*this, style);
		}
		virtual GtkToolbarStyle getStyle()
		{
			return gtk_toolbar_get_style(*this);
		}
        virtual operator GtkToolbar*()
        {
            return GTK_TOOLBAR(getWidget());
        }
        virtual ~GtkToolbarEx() {}

        virtual int getItemCount()
        {
            return gtk_toolbar_get_n_items(*this);
        }
        virtual GtkToolItem* getItem(int index)
        {
            return gtk_toolbar_get_nth_item(*this, index);
        }
        virtual void add(GtkToolItem *item, int index = 0)
        {
            gtk_toolbar_insert(*this, item, index);
        }
        virtual void add(GtkToolItemEx *item, int index =0)
        {
            add(*item);
        }
        virtual void addSeparator(bool showVertical = true)
        {
            GtkToolItem *sep = gtk_separator_tool_item_new();
            gtk_separator_tool_item_set_draw(GTK_SEPARATOR_TOOL_ITEM(sep), showVertical);
            add(sep);
        }
        virtual int getItemIndex(GtkToolItem *item)
        {
            return gtk_toolbar_get_item_index(*this, item);
        }

    protected:
    private:
};

#endif // GTKTOOLBAREX_H
