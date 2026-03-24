#ifndef LINELIST_CPP
#define LINELIST_CPP
#include "LineList.h"
// Реализация методов LineListElem (Слайд 15)

template<class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem<T>* anext) {
    data = adata;
    next = anext;
}

template<class T>
const T& LineListElem<T>::getData() const {
    return data;
}

template<class T>
LineListElem<T>* LineListElem<T>::getNext() {
    return next;
}

// Реализация методов LineList (Слайды 16-20)

template<class T>
LineList<T>::LineList() {
    start = 0;
}

template<class T>
LineList<T>::~LineList() {
    while (start) {
        deleteFirst();
    }
}

template<class T>
LineListElem<T>* LineList<T>::getStart() {
    return start;
}

template<class T>
void LineList<T>::insertFirst(const T& data) {
    LineListElem<T>* second = start;
    start = new LineListElem<T>(data, second);
}

template<class T>
void LineList<T>::deleteFirst() {
    if (start) {
        LineListElem<T>* temp = start->next;
        delete start;
        start = temp;
    } else {
        throw LineListException();
    }
}

template<class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data) {
    if (ptr) {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    }
}

template<class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr) {
    if (ptr && ptr->next) {
        LineListElem<T>* temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
    } else {
        throw LineListException();
    }
}

// Оператор вывода (Слайд 21)
template<class T>
std::ostream& operator<<(std::ostream& out, LineList<T>& list) {
    LineListElem<T>* ptr = list.start;
    if (!ptr) {
        out << "EMPTY";
    } else {
        while (ptr) {
            out << ptr->getData() << " ";
            ptr = ptr->getNext();
        }
    }
    return out;
}

#endif // LINELIST_CPP