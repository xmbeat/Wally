/*
 * GtkDialog.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef GTKDIALOGEX_H_
#define GTKDIALOGEX_H_
#include "GtkWindowEx.h"
#include <Utils/ArrayList.h>
#include <stdarg.h>
class GtkDialogEx:public GtkWindowEx{
public:
	GtkDialogEx(): GtkWindowEx((GtkWidget*)NULL){
		setWidget(gtk_dialog_new());
	}
	GtkDialogEx(GtkWidget* widget):GtkWindowEx(widget){
	}
	virtual operator GtkDialog*(){
		return GTK_DIALOG(getWidget());
	}
	virtual int run(){
		return gtk_dialog_run(*this);
	}
	virtual GtkWidget* addButton(const char* text, int responseId){
		return gtk_dialog_add_button(*this, text, responseId);
	}

	virtual void response(int responseId){
		gtk_dialog_response(*this, responseId);
	}

	virtual void addActionWidget(GtkWidget* child, int responseId){
		gtk_dialog_add_action_widget(*this, child, responseId);
	}

	virtual void setDefaultResponse(int responseId){
		gtk_dialog_set_default_response(*this, responseId);
	}

	virtual void setResponseSensitive(int responseId, bool value){
		gtk_dialog_set_response_sensitive(*this, responseId, value);
	}

	virtual int getResponseForWidget(GtkWidget* widget){
		return gtk_dialog_get_response_for_widget(*this, widget);
	}

	virtual GtkWidget* getWidgetForResponse(int responseId){
		return gtk_dialog_get_widget_for_response(*this, responseId);
	}

	virtual GtkWidget* getActionArea(){
		return gtk_dialog_get_action_area(*this);
	}

	virtual GtkWidget* getContentArea(){
		return gtk_dialog_get_content_area(*this);
	}

	virtual void setAlternativeButtonOrder(int firstResponseId, ...){
		ArrayList<int> list;
		va_list params;
		va_start(params, firstResponseId);
		int aux = va_arg(params, int);
		while(aux != -1){
			list.add(aux);
		}
		va_end(params);
		gtk_dialog_set_alternative_button_order_from_array(*this, list.size(), list.toArray());
	}
	virtual void actToResponseEvent(GtkEventWatcher *listener){
		g_signal_connect(getWidget(), "response", G_CALLBACK(dialogResponseEvent), listener);
	}
	virtual void actToCloseEvent(GtkEventWatcher *listener){
		g_signal_connect(getWidget(), "close", G_CALLBACK(dialogCloseEvent), listener);
	}
private:
	static void dialogResponseEvent(GtkDialog* dialog, int responseId, GtkEventWatcher* listener){
		listener->onResponse(dialog, responseId);
	}

	static void dialogCloseEvent(GtkDialog* dialog, GtkEventWatcher* listener){
		listener->onClose(dialog);
	}

};



#endif /* GTKDIALOG_H_ */
