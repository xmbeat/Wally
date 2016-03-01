#ifndef GTKMISCEX_H
#define GTKMISCEX_H
#include "GtkWidgetEx.h"
class GtkMiscEx: public GtkWidgetEx
{
public:
	virtual operator GtkMisc*()
	{
		return GTK_MISC(getWidget());
	}
	virtual void setAlignment(float xalign, float yalign)
	{
		gtk_misc_set_alignment(*this, xalign, yalign);
	}
	virtual void getAlignment(float *xalign, float *yalign)
	{
		gtk_misc_get_alignment(*this, xalign, yalign);
	}
	virtual void setPadding(int xpad, int ypad)
	{
		gtk_misc_set_padding(*this, xpad, ypad);
	}
	virtual void getPadding(int *xpad, int *ypad)
	{
		gtk_misc_get_padding(*this, xpad, ypad);
	}
};	
#endif
