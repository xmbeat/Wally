/*
 * GtkStatusBarEx.h
 *
 *  Created on: 21/07/2015
 *      Author: xmbeat
 */

#ifndef GTKSTATUSBAREX_H_
#define GTKSTATUSBAREX_H_

#include "GtkBoxEx.h" //En realidad de GtkHBox

class GtkStatusBarEx: public GtkBoxEx{
public:
	GtkStatusBarEx(GtkWidget* widget){
		setWidget(widget);
	}
	GtkStatusBarEx(){
		setWidget(gtk_statusbar_new());
	}
	virtual ~GtkStatusBarEx(){}
	virtual operator GtkStatusbar*(){
		return GTK_STATUSBAR(getWidget());
	}
	virtual int push(int contextId, const char* text){
		return gtk_statusbar_push(*this, contextId, text);
	}
	virtual void pop(int contextId){
		gtk_statusbar_pop(*this, contextId);
	}
	virtual void remove(int contextId, int messageId){
		gtk_statusbar_remove(*this, contextId, messageId);
	}
	virtual void removeAll(int contextId){
		gtk_statusbar_remove_all(*this, contextId);
	}
	virtual void setHasResizeGrip(bool setting){
		gtk_statusbar_set_has_resize_grip(*this, setting);
	}
	virtual bool getHasResizeGrip(){
		return gtk_statusbar_get_has_resize_grip(*this);
	}
	virtual GtkWidget* getMessageArea(){
		return gtk_statusbar_get_message_area(*this);
	}
	virtual int getContextId(const char* contextDescription){
		return gtk_statusbar_get_context_id(*this, contextDescription);
	}
};


#endif /* GTKSTATUSBAREX_H_ */
