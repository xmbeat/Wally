#ifndef GTKTABLEEX_H
#define GTKTABLEEX_H
#include "GtkContainerEx.h"
class GtkTableEx: public GtkContainerEx
{
public:
	virtual operator GtkTable*()
	{
		return GTK_TABLE(getWidget());
	}
	GtkTableEx(int cols, int rows, bool homogeneous){
		setWidget(gtk_table_new(cols, rows, homogeneous));
	}
	virtual ~GtkTableEx()
	{}
	virtual void setRowSpacing(int row, int space)
	{
		gtk_table_set_row_spacing(*this,row, space);
	}
	virtual void setRowSpacings(int space)
	{
		gtk_table_set_row_spacings(*this, space);
	}
	virtual int getRowSpacing(int row)
	{
		return gtk_table_get_row_spacing(*this, row);
	}	
	virtual int getDefaultRowSpacing()
	{
		return gtk_table_get_default_row_spacing(*this);
	}
	virtual void setColSpacings(int space)
	{
		gtk_table_set_col_spacings(*this, space);
	}
	virtual void setColSpacing(int col, int space)
	{
		gtk_table_set_col_spacing(*this, col, space);
	}
	virtual int getColSpacing(int col)
	{
		return gtk_table_get_col_spacing (*this, col);
	}
	virtual int getDefaultColSpacing()
	{
		return gtk_table_get_default_col_spacing(*this);
	}
	virtual void add(GtkWidget*widget, int col, int row, int width = 1, int height = 1, int xoptions = 0, 
					int yoptions = 0, int xpadding = 0, int ypadding = 0)
	{
		
		gtk_table_attach(*this, widget, col, col+width, row, row + height,(GtkAttachOptions) xoptions,(GtkAttachOptions) yoptions, xpadding, ypadding);	
	}
	virtual void setHomogeneous(bool value)
	{
		gtk_table_set_homogeneous(*this, value);
	}
	virtual bool isHomogeneous()
	{
		return gtk_table_get_homogeneous (*this);
	}
};
#endif
