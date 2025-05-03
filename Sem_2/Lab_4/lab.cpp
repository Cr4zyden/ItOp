#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Element1 {
    string key;
    double value;
};

struct Element2 {
    double value;
    int key;
    string label;
};

// Глобальные таблицы

vector<Element1> table1;
vector<Element2> table2;

// Функции для работы с таблицей 1 

void addElement1Manually() {
    Element1 elem;
    string input;

    // Ввод ключа с проверкой длины
    do {
        cout << "Введите ключ (до 15 символов): ";
        cin >> input;
        if (input.length() > 15) {
            cout << "Ошибка: ключ не должен превышать 15 символов. Попробуйте снова.\n";
        }
    } while (input.length() > 15);
    elem.key = input;

    // Ввод значения
    cout << "Введите вещественное значение: ";
    while (!(cin >> elem.value)) {
        cout << "Ошибка: введите число: ";
        cin.clear();
        string dummy;
        getline(cin, dummy);
    }

    table1.push_back(elem);
    cout << "Элемент добавлен в таблицу 1.\n";
}

void removeElement1ByKey() {
    string key;
    cout << "Введите ключ для удаления: ";
    cin >> key;

    bool removed = false;
    for (int i = 0; i < table1.size(); ) {
        if (table1[i].key == key) {
            table1.erase(table1.begin() + i);
            removed = true;
        } else {
            ++i;
        }
    }

    if (removed)
        cout << "Все элементы с ключом \"" << key << "\" удалены из таблицы 1.\n";
    else
        cout << "Элемент с ключом \"" << key << "\" не найден.\n";
}

void printTable1() {
    if (table1.empty()) {
        cout << "Таблица 1 пуста.\n";
        return;
    }
    cout << "Таблица 1:\n";
    for (const auto& elem : table1) {
        cout << "Ключ: " << elem.key << ", Значение: " << elem.value << endl;
    }
}

// === Функции для работы с таблицей 2 ===

void addElement2Manually() {
    Element2 elem;
    string input;

    // Ввод ключа (целое положительное число)
    cout << "Введите целый ключ: ";
    while (!(cin >> elem.key) || elem.key <= 0) {
        cout << "Ошибка: ключ должен быть положительным числом: ";
        cin.clear();
        string dummy;
        getline(cin, dummy);
    }

    // Ввод значения
    cout << "Введите вещественное значение: ";
    while (!(cin >> elem.value)) {
        cout << "Ошибка: введите число: ";
        cin.clear();
        string dummy;
        getline(cin, dummy);
    }

    // Ввод метки с проверкой длины
    do {
        cout << "Введите метку (до 10 символов): ";
        cin >> input;
        if (input.length() > 10) {
            cout << "Ошибка: метка не должна превышать 10 символов. Попробуйте снова.\n";
        }
    } while (input.length() > 10);
    elem.label = input;

    // Вставка по возрастанию ключа
    size_t pos = 0;
    while (pos < table2.size() && table2[pos].key <= elem.key) {
        ++pos;
    }
    table2.insert(table2.begin() + pos, elem);

    cout << "Элемент добавлен в таблицу 2.\n";
}

void removeElement2ByKey() {
    int key;
    cout << "Введите целый ключ для удаления: ";
    while (!(cin >> key) || key <= 0) {
        cout << "Ошибка: ключ должен быть положительным числом: ";
        cin.clear();
        string dummy;
        getline(cin, dummy);
    }

    bool removed = false;
    for (int i = 0; i < table2.size(); ) {
        if (table2[i].key == key) {
            table2.erase(table2.begin() + i);
            removed = true;
        } else {
            ++i;
        }
    }

    if (removed)
        cout << "Все элементы с ключом " << key << " удалены из таблицы 2.\n";
    else
        cout << "Элемент с ключом " << key << " не найден.\n";
}

void printTable2() {
    if (table2.empty()) {
        cout << "Таблица 2 пуста.\n";
        return;
    }
    cout << "Таблица 2:\n";
    for (const auto& elem : table2) {
        cout << "Значение: " << elem.value << ", Ключ: " << elem.key << ", Метка: " << elem.label << endl;
    }
}

// === Главное меню ===

void showMenu() {
    cout << "\n===== ЛАБОРАТОРНАЯ РАБОТА №4 =====\n";
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент в таблицу 1\n";
    cout << "2. Удалить элемент из таблицы 1 по ключу\n";
    cout << "3. Показать таблицу 1\n";
    cout << "4. Добавить элемент в таблицу 2\n";
    cout << "5. Удалить элемент из таблицы 2 по ключу\n";
    cout << "6. Показать таблицу 2\n";
    cout << "0. Выход\n";
    cout << "-------------------------------\n";
    cout << "Введите номер: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    int choice;

    do {
        showMenu();
        while (!(cin >> choice)) {
            cout << "Ошибка ввода. Введите цифру от 0 до 6: ";
            cin.clear();
            string dummy;
            getline(cin, dummy);
        }

        switch (choice) {
            case 1:
                addElement1Manually();
                break;
            case 2:
                removeElement1ByKey();
                break;
            case 3:
                printTable1();
                break;
            case 4:
                addElement2Manually();
                break;
            case 5:
                removeElement2ByKey();
                break;
            case 6:
                printTable2();
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
