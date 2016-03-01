/*
 * GtkFileChooserDialog.h
 *
 *  Created on: 20/07/2015
 *      Author: xmbeat
 */

#ifndef GTKFILECHOOSERDIALOGEX__H_
#define GTKFILECHOOSERDIALOGEX__H_
#include "GtkDialogEx.h"
#include "GtkIFileChooserEx.h"
#include <stdarg.h>
class GtkFileChooserDialogEx: public GtkIFileChooserEx, public GtkDialogEx{
public:
	GtkFileChooserDialogEx(const char* title, GtkWindow* parent, GtkFileChooserAction action, const char* firstButtonText, ...):GtkDialogEx((GtkWidget*)NULL){
		va_list params;
		va_start(params, firstButtonText);
		int id = va_arg(params, int);
		setWidget(gtk_file_chooser_dialog_new(title, parent, action, firstButtonText, id, NULL));

		const char* text = va_arg(params, const char*);

		while(text != NULL){
			id = va_arg(params, int);
			if (id == 0){
				break;
			}
			this->addButton(text, id);
			text = va_arg(params, const char*);
		}
		va_end(params);
	}
	virtual operator GtkFileChooser*(){
		return GTK_FILE_CHOOSER(getWidget());
	}
};



#endif /* GTKFILECHOOSERDIALOG_H_ */
