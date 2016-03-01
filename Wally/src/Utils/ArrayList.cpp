/*
 * ArrayList.cpp
 *
 *  Created on: 19/07/2015
 *      Author: xmbeat
 */
#ifdef ARRAYLIST_H_

#include "ArrayList.h"
#include <Utils/String.h>
#include <Exception/IndexOutOfBoundException.h>
template <class T>
ArrayList<T>::~ArrayList(){
	delete []_arreglo;
}
template <class T>
T ArrayList<T>::operator[](int index)const{
    if (index< _size && index>=0)
        return _arreglo[index];
    throw IndexOutOfBoundException(String("Index") + index); //trabajando que excepiones generara*/
}
template <class T>
T &ArrayList<T>::operator [](int index)
{
    if (index < _size && index >= 0)
        return _arreglo[index];
    throw IndexOutOfBoundException(String("Index") + index); //trabajando que excepiones generara*/
}
template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> &c){
	this->_size = c._size;
	this->_capacity = c._capacity;
	this->_step = c._step;
	this->_arreglo = new T[c._capacity];
	for (int i = 0; i < _size; i++){
		this->_arreglo[i] = c._arreglo[i];
	}
}
template <class T>
bool ArrayList<T>::operator==(const ArrayList<T> &a)
{
	if (&a != this && a._size == _size){
		for (int i = 0; i < _size; i++)
		{
			if (!(_arreglo[i]==a._arreglo[i]))
				return false;
		}
	}
	return true;
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T> &a)
{
    if (&a!=this)
    {
    	if (_arreglo)
    		delete [] _arreglo;
        initialize(a._size);
        _size = a._size;
        for (int i = 0; i < _size; i++)
        {
            _arreglo[i] = a._arreglo[i];
        }
    }
    return *this;
}

template <class T>
bool ArrayList<T>::containsAll(List<T>*c)
{
    for (int i = 0; i < c->size(); i++)
    {
        if (indexOf(c->get(i)) < 0)//no se encontro
            return false;
    }
    return true;
}
template <class T>
ArrayList<T> ArrayList<T>::subArrayList(int fromIndex, int toIndex)
{
    ArrayList<T> list;
    for (;fromIndex < toIndex;fromIndex++)
    {
        list.add(get(fromIndex));
    }
    return list;
}

template <class T>
List<T>* ArrayList<T>::subList(int fromIndex, int toIndex)
{
    List<T> *list = new ArrayList<T>();
    for (;fromIndex<toIndex;fromIndex++)
    {
        list->add(get(fromIndex));
    }
    return list;
}

template <class T>
bool ArrayList<T>::retainAll(List <T>*c)
{
    int num = 0;
    for (int i = 0; i < _size; i++)
    {
        if (c->indexOf(_arreglo[i])<0)//no se encontro este elemento en la lista
            num++;
        else//se encontro
            _arreglo[i-num] = _arreglo[i];
    }
    _size-=num;
    return num>0;
}

template <class T>
bool ArrayList<T>::removeAll(List <T>*c)
{
    int num=0;
    for (int i = 0; i < _size; i++)
    {
        if (c->indexOf(_arreglo[i])>=0)
            num++;
        else
            _arreglo[i-num]=_arreglo[i];
    }
    _size-=num;
    return num>0;
}

template <class T>
bool ArrayList<T>::addAll(int index, List<T>*c)
{
    if (index<=_size && index>=0)
    {
    	int size = c->size() + _size;
        ensureCapacity(size);
        shiftElements(index, c->size());
        _size = size;
        for (int i = 0; i < c->size(); i++){
        	_arreglo[i + index] = c->get(i);
        }
        return true;
    }
    return false;
}

template <class T>
bool ArrayList<T>::addAll(List <T>*c)
{
    return addAll(size(),c);
}

template <class T>
ArrayList<T>::ArrayList(List <T>*c)
{
    initialize(c->size());
    for (int i = 0; i < _size; i++)
    {
        _arreglo[i] = c->get(i);
    }
}

template <class T>
T* ArrayList<T>::toArray()
{
    return _arreglo;
}

template <class T>
int ArrayList<T>::size()
{
    return _size;
}

template <class T>
T ArrayList<T>::set(int index, T element)
{
    T tmp = get(index);
    _arreglo[index] = element;
    return tmp;
}

template <class T>
T ArrayList<T>::remove(int index)
{
    T tmp = get(index);
    shiftElements(index+1,-1);
    _size--;
    return tmp;
}

template <class T>
bool ArrayList<T>::isEmpty()
{
    return (_size==0);
}

template <class T>
int ArrayList<T>::lastIndexOf(T element)
{
    for (int i = _size; i-- > 0;)
    {
        if (_arreglo[i]==element)
            return i;
    }
    return -1;
}

template <class T>
int ArrayList<T>::indexOf(T element)
{
    for (int i = 0; i < _size;i++)
    {
        if (_arreglo[i]==element)
            return i;
    }
    return -1;
}

template <class T>
T ArrayList<T>::get(int index)
{
	return (*this)[index];
}

template <class T>
void ArrayList<T>::clear()
{
    delete [] _arreglo;
    initialize(_step);
}

template <class T>
void ArrayList<T>::shiftElements(int fromIndex, int shift)
{
    if (shift > 0)
    {
        for (int i = _size-1; i >=fromIndex; i--)
        {
            _arreglo[i + shift] = _arreglo[i];
        }
    }
    else
    {
        for (int i = fromIndex; i<_size; i++)
        {
            _arreglo[i + shift] = _arreglo[i];
        }
    }
}

template <class T>
bool ArrayList<T>::add(T element)
{
    return add(size(), element);
}

template <class T>
bool ArrayList<T>::add(int index, T element)
{
    if (index > _size || index < 0)
    {
        return false;
        //aun no decido si usar alguna excepcion
    }
    else
    {
        ensureCapacity(_size + 1);//primero aseguro el espacio
        shiftElements(index, 1);//desplazo los elementos un lugar hacia la derecha
        _arreglo[index] = element;
        _size++;//y luego incremento
        return true;
    }
}

template <class T>
ArrayList<T>::ArrayList():_step(10)
{
    initialize(_step);
}

template <class T>
ArrayList<T>::ArrayList(int initialCapacity):_step(initialCapacity)
{
    initialize(_step);
}
template <class T>
void ArrayList<T>::initialize(int minCapacity)
{
    _arreglo = new T[minCapacity];
    _size = 0;
    _capacity = minCapacity;
}

template <class T>
void ArrayList<T>::ensureCapacity(int minCapacity)
{
    if (minCapacity > _capacity)
    {
        _capacity = minCapacity + _step;
        T *tmp = new T[_capacity];
        for (int i = 0;i<_size;i++)
        {
            tmp[i] = _arreglo[i];
        }
        delete [] _arreglo;
        _arreglo = tmp;
    }
}





template <class T>
ArrayList<T*>& ArrayList<T*>::operator=(const ArrayList<T*> &a)
{
    if (&a!=this)
    {
        if (_arreglo) delete [] _arreglo;
        initialize(a._size);
        _size = a._size;
        for (int i = 0; i < _size; i++)
        {
            _arreglo[i] = a._arreglo[i];
        }
    }
    return *this;
}

template <class T>
bool ArrayList<T*>::retainAll(List <T*>*c)
{
    int num = 0;
    for (int i = 0; i < _size; i++)
    {
        if (c->indexOf(_arreglo[i])<0)//no se encontro este elemento en la lista
            num++;
        else//se encontro
            _arreglo[i-num] = _arreglo[i];
    }
    _size-=num;
    return num>0;
}


template <class T>
List<T*> *ArrayList<T*>::subList(int fromIndex, int toIndex)
{
    List<T*> *list = new ArrayList<T*>();
    for (;fromIndex<toIndex;fromIndex++)
    {
        list->add(get(fromIndex));
    }
    return list;
}

template <class T>
bool ArrayList<T*>::removeAll(List <T*>*c)
{
    for (int i = 0, size = c->size(); i < size;i++)
    {
        remove(c->get(i));
    }
    return true;
}

template <class T>
bool ArrayList<T*>::remove(T *element)
{
    int index;
    if ((index = lastIndexOf(element)) >=0){
        remove(index);
        return true;
    }
    return false;
}

template <class T>
bool ArrayList<T*>::containsAll(List<T*>*c)
{
    if (c!=0)
    {
        for(int i = 0, size = c->size(); i<size;i++)
        {
            for (int j = 0; j < _size ; j++)
            {
                if (*_arreglo[j] == *c->get(i))
                    goto found;//ups!, en c++ no hay breaks para bucles andidados
            }
            return false;
            found:;
        }
    }
    return true;//conjunto vacio es subconjunto de todos
}

template <class T>
ArrayList<T*>::ArrayList(List <T*> *c):_step(10)
{
    if (c!=0)
    {
        initialize(c->size());
        for (int i = 0; i < _size; i++)
        {
            _arreglo[i] = c->get(i);
        }
    }
    else{
        //throw
        initialize(_step);
    }
}

template <class T>
T** ArrayList<T*>::toArray()
{
    return _arreglo;
}

template <class T>
int ArrayList<T*>::size()
{
    return _size;
}

template <class T>
T* ArrayList<T*>::set(int index, T* element)
{
    T* tmp = 0;
    if (isValidIndex(index)){
        tmp = get(index);
        _arreglo[index] = element;
    }
    return tmp;
}
/*DESASTROZO SI EL ELEMENTO NO FUE CREADO DINAMICAMENTE*/
template <class T>
void ArrayList<T*>::setAndDelete(int index, T* element)
{
    delete set(index, element);
}

template <class T>
T* ArrayList<T*>::remove(int index)
{
    T *tmp = 0;
    if (isValidIndex(index)){
        tmp = get(index);
        shiftElements(index+1,-1);
        _size--;
    }
    return tmp;
}

template <class T>
void ArrayList<T*>::removeAndDelete(int index)
{
    delete remove(index);
}


template <class T>
bool ArrayList<T*>::isEmpty()
{
    return (_size==0);
}

template <class T>
int ArrayList<T*>::lastIndexOf(T *element)/* compara contenidos no addr */
{
    for (int i = _size; i-- > 0;)
    {
        if (*_arreglo[i]==*element)
            return i;
    }
    return -1;
}


template <class T>
int ArrayList<T*>::indexOf(T *element)/*compara contenidos*/
{
    for (int i = 0; i < _size;i++)
    {
        if (*_arreglo[i]==*element)
            return i;
    }
    return -1;
}

template <class T>
T* ArrayList<T*>::get(int index)
{
	return (*this)[index];
}

template <class T>
bool ArrayList<T*>::contains(T *element)
{
    for (int i = 0; i < _size;i++)
        if (_arreglo[i]==element)
            return true;
    return false;
}

template <class T>
void ArrayList<T*>::clear()
{
    delete [] _arreglo;
    initialize(_step);
}

template <class T>
void ArrayList<T*>::clearAndDelete()
{
    for (int i = 0; i < _size; i++)
    {
        delete _arreglo[i];
    }
    clear();
}
template <class T>
void ArrayList<T*>::shiftElements(int fromIndex, int shift)
{
    if (shift > 0)
    {
        for (int i = _size-1; i >= fromIndex; i--)
        {
            _arreglo[i + shift] = _arreglo[i];
        }
    }
    else
    {
        for (int i = fromIndex; i<_size; i++)
        {
            _arreglo[i + shift] = _arreglo[i];
        }
    }
}

template <class T>
bool ArrayList<T*>::add(T *element)
{
    return add(size(), element);
}

template <class T>
bool ArrayList<T*>::add(int index, T *element)
{
    if (isValidIndex(index,true))
    {
        ensureCapacity(_size + 1);//primero aseguro el espacio
        shiftElements(index, 1);//desplazo los elementos un lugar hacia la derecha
        _arreglo[index] = element;
        _size++;//y luego incremento
        return true;
    }
    return false;
}

template <class T>
void ArrayList<T*>::trimToSize()
{
    int num=0;
    for (int i = 0; i < _size; i++)
    {
        if (_arreglo[i] == 0){
            num++;
        }
        else{
            _arreglo[i-num]=_arreglo[i];
        }
    }
    _size-=num;
}

template <class T>
ArrayList<T*>::ArrayList():_step(10)
{
    initialize(_step);
}

template <class T>
ArrayList<T*>::ArrayList(int initialCapacity):_step(initialCapacity)
{
    initialize(_step);
}
template <class T>
void ArrayList<T*>::initialize(int minCapacity)
{
    _arreglo = new T*[minCapacity];
    for (int i = 0; i < minCapacity; i++ )
        _arreglo[i] = 0;
    _size = 0;
    _capacity = 10;
}
template <class T>
bool ArrayList<T*>::addAll(int index, List<T*>*c)
{
    if (isValidIndex(index,true))
    {
        int size = _size + c->size();
        ensureCapacity(size);
        _size = size;
        for (int i = 0; i < c->size(); i++){
        	_arreglo[i + index] = c->get(i);
        }

        return true;
    }
    return false;
}

template <class T>
bool ArrayList<T*>::addAll(List <T*> *c)
{
    return addAll(size(), c);
}

template <class T>
void ArrayList<T*>::ensureCapacity(int minCapacity)
{
    if (minCapacity>_capacity)
    {
        _capacity = minCapacity + _step;
        T **tmp = new T*[_capacity];
        for (int i = 0;i<_size;i++)
        {
            tmp[i] = _arreglo[i];
        }
        delete [] _arreglo;
        _arreglo = tmp;
    }
}

template <class T>
T*& ArrayList<T*>::operator [](int index){
	if (index < _size && index >= 0){
		return _arreglo[index];
	}
	else{
		throw IndexOutOfBoundException(String("ArrayList::El indice esta fuera del intervalo"));
	}
}

template <class T>
T* ArrayList<T*>::operator[](int index) const{
	if (index < _size && index >= 0){
		return _arreglo[index];
	}
	else{
		throw IndexOutOfBoundException(String("ArrayList::El indice esta fuera del intervalo"));
	}
}
#endif
