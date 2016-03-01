#ifndef GTKSPINBUTTONEX_H
#define GTKSPINBUTTONEX_H
#include "GtkEntryEx.h"
class GtkSpinButtonEx: public GtkEntryEx
{
public:
	virtual operator GtkSpinButton*()
	{
		return GTK_SPIN_BUTTON(getWidget());
	}
	virtual ~GtkSpinButtonEx(){}

	GtkSpinButtonEx(double min = 0.0, double max = 100.0, double step = 5.0)
	{
		setWidget(gtk_spin_button_new_with_range(min, max, step));
	}
	GtkSpinButtonEx(GtkWidget* widget): GtkEntryEx(widget){
	}
	virtual void setDigits(int digits)
	{
		 gtk_spin_button_set_digits(*this, digits);
	}	

	virtual void setIncrements(double step, double page)
	{
		gtk_spin_button_set_increments(*this, step, page);
	}
	virtual void setRange(double min, double max)
	{
		gtk_spin_button_set_range(*this, min, max);
	}
	virtual int getIntValue()
	{
		return gtk_spin_button_get_value_as_int(*this);
	}	
	virtual void setValue(double value)
	{
		gtk_spin_button_set_value(*this, value);
	}
	virtual void setNumeric(bool value)
	{
		gtk_spin_button_set_numeric (*this, value);
	}
	virtual void spin(GtkSpinType direction, double increment)
	{
		gtk_spin_button_spin(*this, direction, increment);
	}
	virtual void setWrap(bool value)
	{
		gtk_spin_button_set_wrap(*this, value);
	}
	virtual void setSnapToTicks(bool value)
	{
		gtk_spin_button_set_snap_to_ticks(*this, value);
	}
	virtual void update()
	{
		gtk_spin_button_update(*this);
	}
	virtual int getDigits()
	{
		return gtk_spin_button_get_digits(*this);
	}
	virtual void getIncrements(double *step, double *page)
	{
		gtk_spin_button_get_increments(*this, step, page);
	}
	virtual bool getNumeric()
	{
		return gtk_spin_button_get_numeric(*this);
	}
	virtual void getRange(double *min, double *max)
	{
		gtk_spin_button_get_range(*this, min, max);
	}
	virtual bool getSnapToTicks()
	{
		return gtk_spin_button_get_snap_to_ticks(*this);
	}
	virtual double getValue()
	{
		return gtk_spin_button_get_value(*this);
	}
	virtual bool getWrap()
	{
		return gtk_spin_button_get_wrap(*this);
	}
	virtual void actToChangeValueEvent(GtkEventWatcher*listener)
	{
		g_signal_connect(getWidget(), "change-value", G_CALLBACK(changeValueEvent), listener);
	}
private:
	static void changeValueEvent(GtkWidget*spinbutton, GtkScrollType arg1, GtkEventWatcher*listener)
	{
		listener->onChangeValue(spinbutton, arg1);
	}
};	
#endif
