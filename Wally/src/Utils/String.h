/*
 * String.h
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#ifndef STRING_H_
#define STRING_H_

class String {
private:
	int mLongitud;
	char * mCadena;
	void init(const int);
public:
	//Constructores
	String();
	String(const unsigned int size);
	String(const int size);
	String(const char *c);
	String(const char c);
	String(const String &c);
	//Sobrecarga de operadores
	String &operator=(const String &c);
	String operator+(const String &c);
	String operator+(const int &i);
	virtual bool operator==(const String &c); //comprueba toda la cadena
	virtual bool operator==(const char *c);
	virtual bool operator!=(const String &c);
	virtual bool operator!=(const char *c);
	virtual String &operator+=(const String &c);
	virtual operator const char *();
	//Metodos a fines a la cadena
	virtual int length();
	virtual String substring(int);
	virtual String substring(int beginIndex, int len);
	virtual char charAt(int index);
	virtual void setChar(int index, const char c);
	virtual bool equals(const char *c, bool ignoreCase = false);
	virtual bool equals(const String &c, bool ignoreCase = false);
	virtual int inString(const char *c, int index = 0);
	virtual int inString(const String &c, int index = 0); //estoy checando en saber cuando el BOM es factible
	virtual void replace(int start, int len, String &c);
	virtual void replace(int start, int len, char *c);
	virtual int strLen(const char *c);
	virtual char* strCopy(char *dest, const char *origen);
	virtual char* strCopy(char *dest, const char *origen, int inicio, int index,
			int len = 0, bool addZero = false);
	virtual const char* c_str();
	static String toBaseString(int, int);
	static int toInteger(String, int);
	static double strVal(const char *);
	static String strStr(double);
	static String string(char, int);
	virtual ~String();
};

#endif /* STRING_H_ */
