#ifndef LINELIST_H
#define LINELIST_H

#include <iostream>
#include <stdexcept>

// Исключение для операций со списком
class LineListException : public std::runtime_error {
public:
    LineListException() : std::runtime_error("Error in LineList operation") {}
};

// Объявление основного класса списка (нужно для дружественности в элементе)
template<class T>
class LineList;

// Класс элемента списка (Слайд 13)
template<class T>
class LineListElem {
    T data;
    LineListElem<T>* next;

public:
    // Конструктор
    LineListElem(const T& adata, LineListElem<T>* anext);
    
    // Доступ к данным
    const T& getData() const;
    LineListElem<T>* getNext();

    // Доступ для списка (Слайд 13)
    friend class LineList<T>;
};

// Класс списка (Слайд 14)
template<class T>
class LineList {
    LineListElem<T>* start; // Начало списка

    // Конструктор копирования и оператор присваивания
    LineList(const LineList& list); 
    LineList& operator=(const LineList& list);

public:
    LineList();
    ~LineList();

    LineListElem<T>* getStart();
    
    void deleteFirst();
    void deleteAfter(LineListElem<T>* ptr);
    
    void insertFirst(const T& data);
    void insertAfter(LineListElem<T>* ptr, const T& data);

    // Оператор вывода объявляется как друг с template <>
    template<class U>
    friend std::ostream& operator<<(std::ostream& out, LineList<U>& list);
};

// Объявление оператора вывода (Слайд 21)
template<class T>
std::ostream& operator<<(std::ostream& out, LineList<T>& list);

// Подключение реализации шаблонов
#include "LineList.cpp"

#endif // LINELIST_H