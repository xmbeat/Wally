/*
 * GtkAppIndicatorEx.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef GTKAPPINDICATOREX_H_
#define GTKAPPINDICATOREX_H_

#include "GtkWidgetEx.h"
#include <libappindicator/app-indicator.h>

class GtkAppIndicatorEx{
public:
	GtkAppIndicatorEx(String id, String icon, AppIndicatorCategory categoria = APP_INDICATOR_CATEGORY_APPLICATION_STATUS){
		mIndicator = app_indicator_new((const char*)id, (const char*)icon, categoria);
	}
	virtual ~GtkAppIndicatorEx(){}
 	virtual operator AppIndicator*(){
		return mIndicator;
	}

	GType getType(){
		return app_indicator_get_type();
	}

	void setStatus(AppIndicatorStatus status){
		app_indicator_set_status(*this, status);
	}

	AppIndicatorStatus getStatus(){
		return app_indicator_get_status(*this);
	}

	void setAttentionIcon(String iconName){
		app_indicator_set_attention_icon(*this, iconName);
	}
	String getAttentionIcon(){
		return app_indicator_get_attention_icon(*this);
	}
	void setMenu(GtkMenu* menu){
		app_indicator_set_menu(*this, menu);
	}
	GtkMenu* getMenu(){
		return app_indicator_get_menu(*this);
	}
	void setIcon(String iconName){
		app_indicator_set_attention_icon(*this, iconName);
	}
	String getIcon(){
		return app_indicator_get_icon(*this);
	}

	void setLabel(String label, String guide){
		app_indicator_set_label(*this, label, guide);
	}
	String getLabel(){
		return app_indicator_get_label(*this);
	}
	String getLabelGuide(){
		return app_indicator_get_label_guide(*this);
	}
	void setIconThemePath(String path){
		app_indicator_set_icon_theme_path(*this, path);
	}
	String getIconThemePath(){
		return app_indicator_get_icon_theme_path(*this);
	}
	void setOrderingIndex(int orderingIndex){
		app_indicator_set_ordering_index(*this, orderingIndex);
	}

	int getOrderingIndex(){
		return app_indicator_get_ordering_index(*this);
	}
	String getId(){
		return app_indicator_get_id(*this);
	}
	AppIndicatorCategory getCategory(){
		return app_indicator_get_category(*this);
	}
private:
	AppIndicator *mIndicator;
};



#endif /* GTKAPPINDICATOREX_H_ */
