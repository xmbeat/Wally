#ifndef GTKTOOLITEMEX_H
#define GTKTOOLITEMEX_H
#include "GtkContainerEx.h"

class GtkToolItemEx: public GtkContainerEx
{
    public:
		GtkToolItemEx(bool noInstance){}
        GtkToolItemEx() {
            setWidget(GTK_WIDGET(gtk_tool_item_new()));
        }
        virtual operator GtkToolItem*()
        {
            return GTK_TOOL_ITEM(getWidget());
        }
        virtual void setTooltipText(const char* tip)
        {
            gtk_tool_item_set_tooltip_text(*this, tip);
        }
		virtual void setHomogeneous(bool value)
		{
			gtk_tool_item_set_homogeneous(*this, value);
		}
		virtual bool getHomogeneous()
		{
			return gtk_tool_item_get_homogeneous(*this);
		}
		virtual void setExpand(bool value)
		{
			gtk_tool_item_set_expand(*this, value);
		}
		virtual bool getExpand()
		{
			return gtk_tool_item_get_expand(*this);
		}
		virtual void setTooltipMarkup(const char *mark)
		{
			gtk_tool_item_set_tooltip_markup(*this, mark);
		}
		virtual void setVisibleHorizontal(bool value)
		{
			gtk_tool_item_set_visible_horizontal(*this, value);
		}
		virtual bool getVisibleHorizontal()
		{
			return gtk_tool_item_get_visible_horizontal(*this);
		}
		virtual void setVisibleVertical(bool value)
		{
			gtk_tool_item_set_visible_vertical(*this, value);
		}	
		virtual bool getVisibleVertical()
		{
			return gtk_tool_item_get_visible_vertical(*this);
		}
		virtual void setIsImportant(bool value)
		{
			gtk_tool_item_set_is_important(*this, value);
		}
		virtual bool getIsImportant()
		{
			return gtk_tool_item_get_is_important(*this);
		}
        virtual ~GtkToolItemEx() {}
    protected:
    private:
};

#endif // GTKTOOLITEMEX_H
