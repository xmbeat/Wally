/*
 * String.cpp
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */

#include "String.h"

#ifndef NULL
#define NULL 0
#endif

String::operator const char *(){
	return mCadena;
}
const char* String::c_str(){
	return mCadena;
}
int String::length(){
	return mLongitud;
}

bool String::operator!=(const char *c) {
	return !(*this == c);
}
bool String::operator !=(const String &c) {
	return !(*this == c);
}
void String::init(const int size) {
	if (size > 0) {
		mLongitud = size;
		mCadena = new char[size + 1];
		for (int i = 0; i <= size; i++)
			mCadena[i] = 0;
	} else {
		mLongitud = 0;
		mCadena = NULL;
	}
}

String::String():mCadena(NULL) {
	mLongitud = 0;
}

String::String(const int size) {
	init(size);
}

String::String(const unsigned int size) {
	init(size);
}

String::String(const char *c) {
	mLongitud = strLen(c);
	if (mLongitud) {
		mCadena = new char[mLongitud + 1];
		strCopy(mCadena, c, 0, 0, 0, true);
	} else {
		mCadena = NULL;
	}
}
String::String(const char c) {
	mLongitud = 1;
	mCadena = new char[2];
	mCadena[0] = c;
	mCadena[1] = 0;
}
String::String(const String &c) :
		mCadena(NULL) {
	*this = c;
}

String::~String() {
	delete[] mCadena;
}
String String::operator +(const int& i) {
	return *this + String::toBaseString(i, 10);
}
String String::operator +(const String &c) {
	int longA, longB;
	String temp;
	longA = mLongitud;
	longB = c.mLongitud;
	temp.mLongitud = longA + longB;
	if (temp.mLongitud > 0) {
		temp.mCadena = new char[temp.mLongitud + 1];
		strCopy(temp.mCadena, mCadena, 0, 0, longA);
		strCopy(temp.mCadena, c.mCadena, longA, 0, longB, true);
	} else {
		temp.mLongitud = 0;
		temp.mCadena = NULL;
	}

	return temp;
}

String &String::operator=(const String &c) {
	if (this != &c) {
		if (mCadena) delete[] mCadena;
		mLongitud = c.mLongitud;

		if (mLongitud) {
			mCadena = new char[mLongitud + 1];

			strCopy(mCadena, c.mCadena, 0, 0, mLongitud, true);

		} else {
			mCadena = NULL;
		}
	}
	return *this;
}
bool String::operator==(const char *c) {
	return *this == String(c);
}

bool String::operator==(const String &c) {
	int b = c.mLongitud;
	int a = mLongitud;
	if (a == b) {
		while (a--)
			if (this->mCadena[a] != c.mCadena[a])
				return false;

		return true;
	}
	return false;
}

String &String::operator+=(const String &c) {
	return (*this = *this + c);
}

int String::strLen(const char *c) {
	if (c == NULL)
		return 0;
	int i = 0;
	while (c[i++])
		;
	return (i - 1);
}

char *String::strCopy(char *dest, const char *origen) {
	int i = 0;
	if (origen != NULL) {
		while (origen[i]) {
			dest[i] = origen[i];
			i++;
		}
	}
	return dest;
}

char *String::strCopy(char *dest, const char *origen, int inicio, int index,
		int len, bool addZero) {
//inicio=2//index 7 len 20
	if (origen != NULL) {
		if (len == 0) {
			while (origen[index]) {
				dest[inicio++] = origen[index++];
			}
		} else {
			while (len-- > 0) { //19-0
				dest[inicio++] = origen[index++];
			}
		}
	}
	if (addZero) {
		dest[inicio] = 0;
	}
	return dest;
}
String String::substring(int index) {
	return substring(index, mLongitud - index);
}

String String::substring(int index, int len) {
	String temp;
	if (index >= 0 && index < mLongitud) {
		if (len > 0) {
			len = index + len > mLongitud ? mLongitud - index : len; //en caso de que la mLongitud sea mayor al maximo esperado lo limito
			temp.mLongitud = len;
			temp.mCadena = new char[len + 1];
			strCopy(temp.mCadena, mCadena, 0, index, len, true);
		}
	}
	return temp;
}
/*regresa un char segun su indice en la mCadena, no comprueba
 la existencia de la mCadena ni su mLongitud, la debe hacer el programador*/
char String::charAt(int index) {
	return mCadena[index];
}
void String::setChar(int index, const char c) {
	mCadena[index] = c;
}
bool String::equals(const char *c, bool ignoreCase) {
	return equals(String(c), ignoreCase);
}

bool String::equals(const String &c, bool ignoreCase) {
	int i = 0;
	unsigned char byte, cmp;
	if (mLongitud != c.mLongitud)
		return false;
	i = mLongitud;
	if (ignoreCase) {
		while (i--) {
			byte = c.mCadena[i];
			cmp = mCadena[i];
			if (byte > 64 && byte < 91) { //A-Z
				if ((byte != cmp) && ((byte + 32) != cmp)) {
					return false;
				}
			} else if (byte > 96 && byte < 123) { //a-z
				if ((byte != cmp) && ((byte - 32) != cmp)) {
					return false;
				}
			} else if (byte > 191 && byte < 222) { //vocales con acento ñ's etc.
				if ((byte != cmp) && ((byte + 32) != cmp)) {
					return false;
				}
			} else if (byte > 223 && byte < 255) { //no estoy seguro en estos ultimos caracteres!, quiza deben extender 1 byte mas
				if (byte != cmp && ((byte - 32) != cmp)) {
					return false;
				}
			}
		}
		return true;
	} else {
		while (i--) {
			if (mCadena[i] != c.mCadena[i])
				return false;
		}
		return true;
	}
	return false;
}

int String::inString(const char *c, int index) {
	return inString(String(c), index);
}

int String::inString(const String &c, int index) {
	int limite = mLongitud - c.mLongitud + 1;
	int i, j;
	if (index < 0)
		index = 0;
	for (i = index; i < limite; i++) {
		j = 0;
		while (j < c.mLongitud) {
			if (mCadena[i + j] != c.mCadena[j])
				break; //j=c.mLongitud;
			if (++j == c.mLongitud)
				return i;
		}
	}
	return -1;
}
void String::replace(int start, int len, char *c) {
	String temp(c);
	replace(start, len, temp);
}
void String::replace(int start, int len, String &c) {
	char *d = NULL;
	int size, i;
	if (start > mLongitud || start < 0)
		return;
	if (start + len > mLongitud) { //si se excede la mLongitud de la mCadena
		len = mLongitud - start;
	}
	if (len == c.mLongitud) { //si son de misma mLongitud no tiene caso volver a reservar memoria
		while (len--) {
			mCadena[start + len] = c.mCadena[len];
		}
	} else { //hay que eliminar y reservar memoria
		size = mLongitud - len + c.mLongitud;
		if (size > 0) {
			d = new char[size + 1]; //reservamos memoria
			if (start > 0)
				strCopy(d, mCadena, 0, 0, start);
			strCopy(d, c.mCadena, start, 0, c.mLongitud);
			if ((i = mLongitud - start - len) > 0)
				strCopy(d, mCadena, start + c.mLongitud, start + len, i, true);
			delete[] mCadena;
			mLongitud = size;
			mCadena = d;
		}
	}
}
static double pow(int num, int potencia) { //solo usado para no depender de Math
	double resultado = 1;
	for (int i = 0; i < potencia; i++) {
		resultado *= num;
	}
	for (int i = 0; i > potencia; i--) {
		resultado /= num;
	}
	return resultado;
}
int String::toInteger(String str, int base) {
	int ret = 0;
	for (int i = 1; i <= str.length(); i++) {
		char curChar = str.charAt(i - 1);
		if (curChar >= '0' && curChar <= '9') //Es numero
			curChar -= '0';
		else if (curChar >= 'a' && curChar <= 'z') //Alfanumerico minuscula
			curChar -= 'a' - 10;
		else if (curChar >= 'A' && curChar <= 'Z')
			curChar -= 'A' - 10;
//else //error, caracter no soportado
		ret += curChar * pow(base, str.length() - i);
	}
	return ret;
}

String String::toBaseString(int number, int base) {
	if (!number)
		return "0";
	typedef unsigned char byte;
	byte size = 0;
	unsigned int rest = number;
	while (rest) {
		size++;
		rest /= base;
	}
	String ret((unsigned int) size);
	for (byte i = 1; i <= size; i++) {
		byte residuo = number % base;
		number /= base;
		if (residuo < 10)
			ret.setChar(size - i, '0' + residuo);
		else
			ret.setChar(size - i, 0x57 + residuo);
	}
	return ret;
}

double String::strVal(const char *c) {
	int i = 0, digito, potencia = 6, dot = 0;
	double ret = 0;
	bool positive = true;

	while (c[i]) {
		if (c[i] > 47 && c[i] < 58) { //digito
			digito = c[i] - 48;
			ret += digito * pow(10, potencia--);
		} else if (c[i] == 46 && !dot) { //"."
			dot = potencia;
		} else if (c[i] == 45 && ret == 0) { //"-"
			positive = !positive;
		} else if (c[i] != 43 || ret != 0) {
			break;
		}
		i++;
	}
	if (!dot)
		dot = potencia;
	ret *= pow(10, -potencia - 1 - dot + potencia);
	return positive ? ret : -ret;
}

String String::strStr(double numero) {
	String temp;
	long int residuo, i = 10, cociente;
	char c;
	while (int(numero) != 0) {
		residuo = ((int) numero) % i;
		numero -= residuo;
		residuo /= (i / 10);
		c = residuo + 48;
		temp = String(c) + temp;
		i *= 10;
	}
	if (numero != 0) {
		temp += '.';
		i = 10;
		while (numero != 0) {
			numero *= 10;
			cociente = numero;
			residuo = cociente % 10;
			c = residuo + 48;
			temp += c;
			if (numero > 0)
				numero -= residuo;
		}
	}
	if (!temp.length())
		temp = "0";
	return temp;
}
String String::string(char c, int count) {
	String ret(count);
	for (int i = 0; i < count; i++) {
		ret.setChar(i, c);
	}
	return ret;
}

