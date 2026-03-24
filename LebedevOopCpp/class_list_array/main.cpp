#include <iostream>
#include <locale>
#include <ctime>
#include <fstream>
#include "LineList.h"

using namespace std;

// Решение задачи Иосифа-Флавия с использованием LineList
int josephus(int N, int k) {
    LineList<int> list;
    
    // Инициализация списка числами от 1 до N
    for (int i = N; i >= 1; --i) {
        list.insertFirst(i);
    }
    
    LineListElem<int>* current = list.getStart();
    
    // Удаляем элементы, пока не останется один
    while (true) {
        // Проверяем, остался ли один элемент
        LineListElem<int>* check = current->getNext();
        bool onlyOne = true;
        while (check) {
            check = check->getNext();
            if (check) {
                onlyOne = false;
                break;
            }
        }
        if (onlyOne) break;
        
        // Отсчитываем k-1 элементов (k-й удаляем)
        for (int i = 1; i < k; ++i) {
            if (current->getNext()) {
                current = current->getNext();
            } else {
                current = list.getStart();
                for (int j = 1; j < k - i; ++j) {
                    if (current->getNext()) {
                        current = current->getNext();
                    } else {
                        current = list.getStart();
                    }
                }
                break;
            }
        }
        
        // Удаляем текущий элемент
        if (current == list.getStart()) {
            try {
                list.deleteFirst();
                current = list.getStart();
            } catch (...) {
                break;
            }
        } else {
            // Находим предыдущий элемент
            LineListElem<int>* prev = list.getStart();
            while (prev && prev->getNext() != current) {
                prev = prev->getNext();
            }
            if (prev) {
                try {
                    list.deleteAfter(prev);
                    current = prev->getNext();
                    if (!current) current = list.getStart();
                } catch (...) {
                    break;
                }
            }
        }
    }
    
    return list.getStart() ? list.getStart()->getData() : -1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    // Массив значений N для тестирования
    int N_values[] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int k = 2; // Шаг удаления
    int numTests = sizeof(N_values) / sizeof(N_values[0]);
    
    // Открываем CSV файл для записи
    ofstream outFile("results.csv");
    if (!outFile) {
        cerr << "Ошибка открытия файла results.csv для записи!" << endl;
        return 1;
    }
    
    // Записываем заголовок CSV
    outFile << "N;Ответ;Время расчета (сек)" << endl;
    
    cout << "Задача Иосифа-Флавия (k=" << k << ")" << endl;
    cout << "========================================" << endl;
    
    for (int i = 0; i < numTests; ++i) {
        int N = N_values[i];
        
        clock_t start = clock();
        int result = josephus(N, k);
        clock_t end = clock();
        
        double timeSec = (double)(end - start) / CLOCKS_PER_SEC;
        
        cout << "N=" << N << " -> Ответ: " << result << " Время: " << timeSec << " сек" << endl;
        
        // Записываем результат в CSV
        outFile << N << ";" << result << ";" << timeSec << endl;
    }
    
    outFile.close();
    
    cout << "========================================" << endl;
    cout << "Результаты сохранены в results.csv" << endl;
    
    // Самопроверка
    cout << "\nСамопроверка:" << endl;
    cout << "N=100, k=2 -> Ожидаем: 73, Получили: " << josephus(100, 2) << endl;
    cout << "N=1000, k=2 -> Ожидаем: 977, Получили: " << josephus(1000, 2) << endl;
    
    return 0;
}
