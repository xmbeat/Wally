#ifndef GTKSTATUSICONEX
#define GTKSTATUSICONEX
#include "GtkWidgetEx.h"
class GtkStatusIconEx
{
public:
	virtual operator GtkStatusIcon*()
	{
		return tray;
	}
	GtkStatusIconEx()
	{
		tray = gtk_status_icon_new();
	}
	virtual void setIcon(GdkPixbuf *icon)
	{
		gtk_status_icon_set_from_pixbuf(*this, icon);
	}
	virtual GdkPixbuf* getIcon(){
		return gtk_status_icon_get_pixbuf(*this);
	}
	virtual void setIconFromFile(const char* filename)
	{
		gtk_status_icon_set_from_file(*this, filename);
	}
	virtual void setIconFromStock(const char* stockID)
	{
		gtk_status_icon_set_from_stock(*this, stockID);
	}	
	virtual const char* getIconFromStock()
	{
		return gtk_status_icon_get_stock(*this);
	}
	virtual void setTooltipText(const char* text)
	{
		gtk_status_icon_set_tooltip_text(*this, text);
	}
	virtual String getTooltipText()
	{
		char* tmp = NULL;
		tmp = gtk_status_icon_get_tooltip_text(*this);
		String ret = tmp;
		if (tmp) g_free(tmp);
		return ret;
	}
	virtual void setTooltipMarkup(const char* markup)
	{
		gtk_status_icon_set_tooltip_markup(*this, markup);
	}
	virtual String getTooltipMarkup()
	{
		char* tmp = NULL;
		tmp = gtk_status_icon_get_tooltip_markup(*this);
		String ret = tmp;
		if (tmp) g_free(tmp);
		return ret;
	}
	virtual void setHasTooltip(bool value)
	{	
		gtk_status_icon_set_has_tooltip(*this, value);
	}
	virtual bool getHasTooltip()
	{
		return gtk_status_icon_get_has_tooltip(*this);
	}
	virtual void setTitle(const char* title)
	{
		gtk_status_icon_set_title(*this, title);
	}
	virtual const char* getTitle()
	{
		return gtk_status_icon_get_title(*this);
	}
	virtual void setName(const char* name)
	{
		gtk_status_icon_set_name(*this, name);
	}
	virtual void setVisible(bool value)
	{
		gtk_status_icon_set_visible(*this, value);
	}
	virtual bool getVisible()
	{
		return gtk_status_icon_get_visible(*this);
	}
	virtual void setPopupMenu(GtkMenu* menu)
	{
		g_signal_connect(G_OBJECT(tray), "popup-menu", G_CALLBACK(popupEvent), menu);
	}
private:
	static void popupEvent (GtkStatusIcon* statusIcon, int button, int activateTime, GtkMenu* menu)
	{
		gtk_menu_popup(menu, NULL, NULL, gtk_status_icon_position_menu, statusIcon, button, activateTime);
	}
	GtkStatusIcon *tray;
};
#endif
