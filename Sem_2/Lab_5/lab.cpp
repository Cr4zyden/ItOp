#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// === Структуры данных ===
struct Element1 {
    string key;     // до 15 символов
    double value;
};

struct Element2 {
    double value;
    int key;        // целое положительное число
    string label;   // до 10 символов
};

// === Функции ввода с проверками ===

string getKey15() {
    string key;
    do {
        cout << "Ключ (до 15 символов): ";
        cin >> ws; // пропустить пробелы/переводы
        getline(cin, key);
        if (key.length() > 15)
            cout << "Ошибка: ключ не должен превышать 15 символов.\n";
    } while (key.length() > 15);
    return key;
}

string getLabel10() {
    string label;
    do {
        cout << "Метка (до 10 символов): ";
        cin >> ws;
        getline(cin, label);
        if (label.length() > 10)
            cout << "Ошибка: метка не должна превышать 10 символов.\n";
    } while (label.length() > 10);
    return label;
}

double getDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите вещественное число.\n";
        } else {
            cin.ignore(10000, '\n');
            return val;
        }
    }
}

int getPositiveInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail() || val <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка: введите положительное целое число.\n";
        } else {
            cin.ignore(10000, '\n');
            return val;
        }
    }
}

// === Сортировка прямым включением (Задание 1а) ===
void insertionSortTask1(vector<Element1>& table) {
    int comparisons = 0, movements = 0;
    for (size_t i = 1; i < table.size(); ++i) {
        Element1 current = table[i];
        int j = i - 1;

        while (j >= 0 && ++comparisons && table[j].value > current.value) {
            table[j + 1] = table[j];
            ++movements;
            --j;
        }

        table[j + 1] = current;
        ++movements;
    }

    cout << "Число сравнений: " << comparisons << endl;
    cout << "Число перемещений: " << movements << endl;
}

// === Вспомогательная функция слияния (общая для всех методов слиянием) ===
template<typename T>
void merge(vector<T>& arr, int left, int mid, int right, int& comp, int& move) {
    vector<T> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (++comp && leftArr[i].value <= rightArr[j].value)
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
        ++move;
    }

    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
        ++move;
    }
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
        ++move;
    }
}

// === Сортировка слиянием (рекурсивная) ===
template<typename T>
void mergeSort(vector<T>& arr, int left, int right, int& comp, int& move) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid, comp, move);
    mergeSort(arr, mid + 1, right, comp, move);

    merge(arr, left, mid, right, comp, move);
}

// === Обёртки для вызова сортировки слиянием ===
void mergeSortTask1(vector<Element1>& table) {
    int comp = 0, move = 0;
    mergeSort(table, 0, table.size() - 1, comp, move);
    cout << "Число сравнений: " << comp << endl;
    cout << "Число перемещений: " << move << endl;
}

void mergeSortTask2(vector<Element2>& table) {
    int comp = 0, move = 0;
    mergeSort(table, 0, table.size() - 1, comp, move);
    cout << "Число сравнений: " << comp << endl;
    cout << "Число перемещений: " << move << endl;
}

// === Основная программа ===
int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        cout << "\n=== Лабораторная работа №5: Управление таблицами ===\n";
        cout << "Выберите задание:\n";
        cout << "1. Задание 1\n";
        cout << "2. Задание 2\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            int subChoice;
            cout << "Выберите метод упорядочения:\n";
            cout << "1. Прямое включение (1а)\n";
            cout << "2. Сортировка слиянием (1е)\n";
            cout << "Ваш выбор: ";
            cin >> subChoice;

            if (subChoice != 1 && subChoice != 2) {
                cout << "Неверный выбор!\n";
                continue;
            }

            int n = getPositiveInt("Введите количество элементов: ");
            vector<Element1> table;

            for (int i = 0; i < n; ++i) {
                Element1 elem;
                cout << "Элемент " << i + 1 << ":\n";
                elem.key = getKey15();
                elem.value = getDouble("Значение: ");
                table.push_back(elem);
            }

            if (subChoice == 1)
                insertionSortTask1(table);
            else
                mergeSortTask1(table);

            cout << "\nОтсортированная таблица:\n";
            for (auto& e : table)
                cout << e.key << ": " << e.value << endl;

        } else if (choice == 2) {
            int n = getPositiveInt("Введите количество элементов: ");
            vector<Element2> table;

            for (int i = 0; i < n; ++i) {
                Element2 elem;
                cout << "Элемент " << i + 1 << ":\n";
                elem.key = getPositiveInt("Целый ключ: ");
                elem.value = getDouble("Вещественное значение: ");
                elem.label = getLabel10();
                table.push_back(elem);
            }

            mergeSortTask2(table);

            cout << "\nОтсортированная таблица:\n";
            for (auto& e : table)
                cout << e.label << " | Ключ: " << e.key << " | Значение: " << e.value << endl;

        } else if (choice == 0) {
            cout << "Выход из программы.\n";
            break;
        } else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

    } while (true);

    return 0;
}
