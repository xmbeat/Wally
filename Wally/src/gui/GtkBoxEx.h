#ifndef GTKBOXEX_H
#define GTKBOXEX_H
#include "GtkContainerEx.h"

class GtkBoxEx: public GtkContainerEx
{
    public:
        GtkBoxEx() {}
        virtual operator GtkBox*()
        {
            return GTK_BOX(getWidget());
        }
        virtual void add(GtkWidget *widget, bool expand = true, bool fill = true,unsigned int padding = 0, bool atEnd = false)
        {
            if (atEnd)
                gtk_box_pack_end(*this, widget, expand, fill,padding);
            else
                gtk_box_pack_start(*this, widget, expand, fill,padding);
        }
		virtual void reorderChild(GtkWidget *child, int pos)
		{
			gtk_box_reorder_child(*this, child, pos);
		}
		virtual void queryChildPacking(GtkWidget*child, bool *expand, bool* fill, unsigned int* padding, GtkPackType *pack)
		{
			gtk_box_query_child_packing(*this, child,(gboolean*) expand, (gboolean*)fill, (guint*)padding, pack);
		}
		virtual void setChildPacking(GtkWidget*child, bool expand, bool fill, int padding, GtkPackType pack)
		{
			gtk_box_set_child_packing(*this, child, expand, fill, padding, pack);
		}
		virtual void setSpacing(int space)
		{
			gtk_box_set_spacing (*this, space);
		}
		virtual int getSpacing()
		{
			return gtk_box_get_spacing (*this);
		}
        virtual bool isHomogeneus()
        {
             return gtk_box_get_homogeneous(*this);
        }
        virtual void setHomogeneus(bool val)
        {
             gtk_box_set_homogeneous(*this, val);
        }	
        virtual ~GtkBoxEx() {}
};

class GtkButtonBoxEx: public GtkBoxEx
{
	public:
		virtual operator GtkButtonBox*()
		{
			return GTK_BUTTON_BOX(getWidget());
		}
		GtkButtonBoxStyle getLayout()
		{
			return gtk_button_box_get_layout(*this);
		}
		virtual void setLayout(GtkButtonBoxStyle layout)		
		{
			gtk_button_box_set_layout(*this, layout);
		}
		virtual bool getChildSecundary(GtkWidget *child)
		{
			return gtk_button_box_get_child_secondary(*this, child);
		}
		virtual void setChildSecundary(GtkWidget* child, bool value)
		{
			gtk_button_box_set_child_secondary(*this, child, value);
		}
};
class GtkVButtonBoxEx: public GtkButtonBoxEx
{
	public:
		virtual operator GtkVButtonBox*()
		{
			return (GtkVButtonBox*)getWidget();
		}
		GtkVButtonBoxEx()
		{
			setWidget(gtk_vbutton_box_new());
		}
};
class GtkHButtonBoxEx: public GtkButtonBoxEx
{
	public:	
		virtual operator GtkHButtonBox*()
		{
			return (GtkHButtonBox*)getWidget();
		}
		GtkHButtonBoxEx()
		{
			setWidget(gtk_hbutton_box_new());
		}		
};
class GtkVBoxEx: public GtkBoxEx
{
    public:
        GtkVBoxEx(bool homogeneus = false, int spacing = 0)
        {
            create(homogeneus, spacing);
        }
        virtual void create(bool homogeneus, int spacing)
        {
            setWidget(gtk_vbox_new(homogeneus, spacing));
        }
};
class GtkHBoxEx: public GtkBoxEx
{
    public:
        GtkHBoxEx(bool homogeneus = false, int spacing = 0)
        {
            create(homogeneus, spacing);
        }
		GtkHBoxEx(int onlyDerived){}
        virtual void create(bool homogeneus, int spacing)
        {
            setWidget(gtk_hbox_new(homogeneus, spacing));
        }
};
#endif // GTKBOXEX_H
