#include <iostream>
#include <vector>
#include <string>

using namespace std;



struct Element {
    double value;
    int key;
    string label;
};

// Глобальные таблицы

vector<Element> table;

// === Функции для работы с таблицей 2 ===

void addElementManually() {
    Element elem;
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
    while (pos < table.size() && table[pos].key <= elem.key) {
        ++pos;
    }
    table.insert(table.begin() + pos, elem);

    cout << "Элемент добавлен в таблицу 2.\n";
}

void removeElementByKey() {
    int key;
    cout << "Введите целый ключ для удаления: ";
    while (!(cin >> key) || key <= 0) {
        cout << "Ошибка: ключ должен быть положительным числом: ";
        cin.clear();
        string dummy;
        getline(cin, dummy);
    }

    bool removed = false;
    for (int i = 0; i < table.size(); ) {
        if (table[i].key == key) {
            table.erase(table.begin() + i);
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

void printtable() {
    if (table.empty()) {
        cout << "Таблица пуста.\n";
        return;
    }
    cout << "Таблица :\n";
    for (const auto& elem : table) {
        cout << "Значение: " << elem.value << ", Ключ: " << elem.key << ", Метка: " << elem.label << endl;
    }
}

// === Главное меню ===

void showMenu() {
    cout << "\n===== ЗАЩИТА ЛАБОРАТОРНОЙ РАБОТЫ №4 =====\n";
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент в таблицу 2\n";
    cout << "2. Удалить элемент из таблицы 2 по ключу\n";
    cout << "3. Показать таблицу 2\n";
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
                addElementManually();
                break;
            case 2:
                removeElementByKey();
                break;
            case 3:
                printtable();
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
