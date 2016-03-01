#ifndef GTKTREEVIEWCOLUMNEX_H
#define GTKTREEVIEWCOLUMNEX_H
#include "GtkWidgetEx.h"
class GtkTreeViewColumnEx
{
public:
	virtual operator GtkTreeViewColumn*()
	{
		return tvc;
	}
	GtkTreeViewColumnEx()
	{
		tvc = gtk_tree_view_column_new();
	}
	virtual void setText(const char *title)
	{
		gtk_tree_view_column_set_title(*this, title);
	}
	virtual String getText()
	{
		return gtk_tree_view_column_get_title(*this);
	}
	virtual void addAttribute(GtkCellRenderer* renderer, const char* attrib, int column, bool pack = false)
	{
		if (pack)
		{
			packStart(renderer, true);
		}
		gtk_tree_view_column_add_attribute(*this, renderer, attrib, column);
	}
	virtual void packStart(GtkCellRenderer* renderer, bool expand)
	{
		gtk_tree_view_column_pack_start(*this, renderer, expand);
	}
	virtual void packEnd(GtkCellRenderer* renderer, bool expand)
	{
		gtk_tree_view_column_pack_end(*this, renderer, expand);
	}
	virtual void setSpacing(int value)
	{
		gtk_tree_view_column_set_spacing(*this, value);
	}
	virtual int getSpacing()
	{
		return gtk_tree_view_column_get_spacing(*this);
	}
	virtual void setVisible(bool value)
	{
		gtk_tree_view_column_set_visible(*this, value);
	}
	virtual bool getVisible()
	{
		return gtk_tree_view_column_get_visible(*this);
	}
	virtual void setResizable(bool value)
	{
		gtk_tree_view_column_set_resizable(*this, value);
	}
	virtual bool getResizable()
	{
		return gtk_tree_view_column_get_resizable(*this);
	}
	virtual void setSizing(GtkTreeViewColumnSizing value)
	{
		gtk_tree_view_column_set_sizing(*this, value);
	}
	virtual GtkTreeViewColumnSizing getSizing()
	{
		return gtk_tree_view_column_get_sizing(*this);
	}
	virtual int getWidth()
	{
		return gtk_tree_view_column_get_width(*this);
	}
	virtual int getFixedWidth()
	{
		return gtk_tree_view_column_get_fixed_width(*this);
	}
	virtual void setFixedWidth(int value)
	{
		gtk_tree_view_column_set_fixed_width(*this, value);
	}
	virtual void setMinWidth(int value)
	{
		gtk_tree_view_column_set_min_width(*this, value);
	}
	virtual int getMinWidth()
	{
		return gtk_tree_view_column_get_min_width(*this);
	}
	virtual void setMaxWidth(int value)
	{
		gtk_tree_view_column_set_max_width(*this, value);
	}
	virtual int getMaxWidth()
	{
		return gtk_tree_view_column_get_max_width(*this);
	}
	virtual void setExpand(bool value)
	{
		 gtk_tree_view_column_set_expand (*this, value);
	}
	virtual bool getExpand()
	{
		return gtk_tree_view_column_get_expand (*this);
	}
	virtual void setClickable(bool value)
	{
		 gtk_tree_view_column_set_clickable(*this, value);
	}
	virtual bool getClickable()
	{
		return  gtk_tree_view_column_get_clickable(*this);
	}
	virtual void setWidget(GtkWidget *widget)
	{
		gtk_tree_view_column_set_widget(*this, widget);
	}
	virtual GtkWidget* getWidget()
	{
		return gtk_tree_view_column_get_widget(*this);
	}
	virtual void setAlignment(float value)
	{
		gtk_tree_view_column_set_alignment(*this, value);
	}
	virtual float getAlignment()
	{
		return gtk_tree_view_column_get_alignment(*this);
	}
	virtual void setReorderable(bool value)
	{
		gtk_tree_view_column_set_reorderable(*this, value);
	}
	virtual bool getReorderable()
	{
		return gtk_tree_view_column_get_reorderable(*this);
	}

private:
	GtkTreeViewColumn* tvc;
};
#endif
