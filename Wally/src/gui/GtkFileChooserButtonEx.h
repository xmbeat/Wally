#ifndef GTKFILECHOOSERBUTTON_EX_H
#define GTKFILECHOOSERBUTTON_EX_H
#include "GtkBoxEx.h"
#include "GtkIFileChooserEx.h"
class GtkFileChooserButtonEx: public GtkHBoxEx, public GtkIFileChooserEx
{
public:
	virtual operator GtkFileChooser*()
	{
		return (GtkFileChooser*)getWidget();
	}
	virtual operator GtkFileChooserButton*()
	{
		return (GtkFileChooserButton *)getWidget();
	}
	GtkFileChooserButtonEx(const char *title = NULL, GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN):
	GtkHBoxEx(-1)//no instanciamos
	{
		setWidget(gtk_file_chooser_button_new(title, action));
	}
	virtual String getTitle()
	{
		return gtk_file_chooser_button_get_title(*this);
	}
	virtual void setTitle(const char *title)
	{
		gtk_file_chooser_button_set_title (*this, title);
	}
	virtual bool getFocusOnClick()
	{
		return  gtk_file_chooser_button_get_focus_on_click(*this);
	}
	virtual void setFocusOnClick(bool value)
	{
		 gtk_file_chooser_button_set_focus_on_click(*this, value);
	}
	virtual void actToFileSetEvent(GtkEventWatcher*listener)
	{
		g_signal_connect(getWidget(), "file-set", G_CALLBACK(fileSetEvent), listener);
	}
private:
	static void fileSetEvent(GtkWidget*widget, GtkEventWatcher* listener)
	{
		listener->onFileSet(widget);
	}
};
#endif
