#ifndef GTKTOOLBUTTONEX_H
#define GTKTOOLBUTTONEX_H
#include "GtkToolItemEx.h"

class GtkToolButtonEx:public GtkToolItemEx
{
    public:
        GtkToolButtonEx(const char* caption = NULL, bool isStock = false): GtkToolItemEx(false)
        {
            setWidget(GTK_WIDGET(gtk_tool_button_new(NULL, caption)));
			if (isStock)
            	setStockID(caption);
        }
        virtual void setStockID(const char* stockID)
        {
            gtk_tool_button_set_stock_id(*this, stockID);
        }
		virtual String getStockID()
		{	
			return gtk_tool_button_get_stock_id(*this);
		}
        virtual operator GtkToolButton*()
        {
            return GTK_TOOL_BUTTON(getWidget());
        }

        virtual void setText(const char* text)
        {
            gtk_tool_button_set_label(*this, text);
        }
        virtual String getText()
        {
            return gtk_tool_button_get_label(*this);
        }
        virtual void setUseMnemonic(bool value)
        {
            gtk_tool_button_set_use_underline(*this, value);
        }
        virtual bool isMnemonic()
        {
            return gtk_tool_button_get_use_underline(*this);
        }
        virtual void setIcon(GtkWidget *icon)
        {
            gtk_tool_button_set_icon_widget(*this, icon);
        }
		
        virtual GtkWidget *getIcon()
        {
            return gtk_tool_button_get_icon_widget(*this);
        }

        virtual ~GtkToolButtonEx(){}
        virtual void actToClickEvent(GtkEventWatcher *listener)
        {
            g_signal_connect(getWidget(), "clicked", G_CALLBACK(clickEvent), listener);
        }

    private:
        static void clickEvent(GtkWidget* widget, GtkEventWatcher* listener)
        {
            listener->onClick(widget);
        }
};

#endif // GTKTOOLBUTTONEX_H
