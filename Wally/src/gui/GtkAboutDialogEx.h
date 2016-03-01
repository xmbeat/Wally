#ifndef GTKABOUTDIALOGEX_H
#define GTKABOUTDIALOGEX_H
#include "GtkDialogEx.h"//Realmente necesito GtkDialog
class GtkAboutDialogEx: public GtkDialogEx
{
public:
	GtkAboutDialogEx():GtkDialogEx(NULL)
	{
		setWidget(gtk_about_dialog_new());
	}
	virtual operator GtkAboutDialog*()
	{
		return GTK_ABOUT_DIALOG(getWidget());
	}
	virtual void setProgramName(const char*name)
	{
		gtk_about_dialog_set_program_name(*this, name);
	}
	virtual String getProgramName()
	{
		return gtk_about_dialog_get_program_name(*this);
	}
	virtual void setVersion(const char *version)
	{
		gtk_about_dialog_set_version(*this, version);
	}
	virtual String getVersion()
	{
		return gtk_about_dialog_get_version(*this);
	}
	virtual void setCopyright(const char *copyright)
	{
		gtk_about_dialog_set_copyright(*this, copyright);
	}
	virtual String getCopyright()
	{
		return gtk_about_dialog_get_copyright(*this);
	}
	virtual void setComments(const char *comments)
	{
		gtk_about_dialog_set_comments(*this, comments);
	}
	virtual String getComments()
	{
		return gtk_about_dialog_get_comments(*this);
	}
	virtual String getLicense()
	{
		return gtk_about_dialog_get_license (*this);
	}
	virtual void setLicense(const char*license)
	{
		gtk_about_dialog_set_license(*this, license);
	}
	virtual void setWrapLicense(bool value)
	{
		gtk_about_dialog_set_wrap_license(*this, value);
	}
	virtual bool getWrapLicense()
	{
		return gtk_about_dialog_get_wrap_license(*this);
	}
	virtual String getWebsite()
	{
		return gtk_about_dialog_get_website(*this);
	}
	virtual void setWebsite(const char* website)
	{
		gtk_about_dialog_set_website(*this, website);
	}
	virtual void setWebsiteText(const char* text)
	{
		gtk_about_dialog_set_website_label(*this, text);
	}
	virtual String getWebsiteText()
	{
		return gtk_about_dialog_get_website_label(*this);
	}
	virtual void setAuthors(const char **authors)
	{
		gtk_about_dialog_set_authors(*this, authors);
	}
	virtual void setArtists(const char **artists)
	{
		gtk_about_dialog_set_artists(*this, artists);
	}
	virtual void setDocumenters(const char **documenters)
	{
		gtk_about_dialog_set_documenters(*this, documenters);
	}
	virtual void setTranslatorCredits(const char* translators)
	{
		gtk_about_dialog_set_translator_credits(*this, translators);
	}
	virtual void setLogoIcon(GdkPixbuf *logo)
	{
		gtk_about_dialog_set_logo(*this, logo);
	}
	virtual void setLogoName(const char *iconName)
	{
		gtk_about_dialog_set_logo_icon_name(*this, iconName);
	}
};
#endif
