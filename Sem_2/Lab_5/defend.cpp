#include <iostream>
#include <vector>
#include <string>
#include <limits> // для очистки буфера

struct ProgramObject {
    std::string name;
    std::string type;
    int memorySize;
    int componentCount;
    std::string componentType;
};

// Функция для вывода таблицы
void printTable(const std::vector<ProgramObject>& table) {
    std::cout << "\nТаблица объектов:\n";
    for (const auto& obj : table) {
        std::cout << "Имя: " << obj.name
                  << ", Тип: " << obj.type
                  << ", Размер памяти: " << obj.memorySize
                  << ", Число компонент: " << obj.componentCount
                  << ", Тип компонент: " << obj.componentType << "\n";
    }
}

void selectionSortByName(std::vector<ProgramObject>& table) {
    int n = table.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (table[j].name < table[minIndex].name) {
                minIndex = j;
            }
        }
        if (minIndex != i)
            std::swap(table[i], table[minIndex]);
    }
}

// Последовательный поиск по имени
int sequentialSearchByName(const std::vector<ProgramObject>& table, const std::string& key) {
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i].name == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Функция для безопасного ввода целого числа
int getIntInput() {
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "Ошибка ввода. Введите число: ";
        } else {
            return value;
        }
    }
}

int main() {

    int n;
    std::cout << "Введите количество объектов: ";
    n = getIntInput();

    std::vector<ProgramObject> table(n);

    // Ввод данных
    for (int i = 0; i < n; ++i) {
        std::cout << "\nОбъект " << i + 1 << ":\n";

        std::cout << "Введите имя: ";
        std::getline(std::cin >> std::ws, table[i].name);

        std::cout << "Введите тип: ";
        std::getline(std::cin >> std::ws, table[i].type);

        std::cout << "Введите размер памяти: ";
        table[i].memorySize = getIntInput();

        std::cout << "Введите число компонент: ";
        table[i].componentCount = getIntInput();

        std::cout << "Введите тип компонент: ";
        std::getline(std::cin >> std::ws, table[i].componentType);
    }

    std::cout << "\nВы ввели следующую таблицу:\n";
    printTable(table);

    // Сортировка
    selectionSortByName(table);
    std::cout << "\nТаблица после сортировки по имени:\n";
    printTable(table);

    // Поиск
    std::string searchKey;
    std::cout << "\nВведите имя объекта для поиска: ";
    std::getline(std::cin >> std::ws, searchKey);

    int index = sequentialSearchByName(table, searchKey);
    if (index != -1) {
        std::cout << "Объект найден:\n";
        std::cout << "Имя: " << table[index].name
                  << ", Тип: " << table[index].type
                  << ", Размер памяти: " << table[index].memorySize
                  << ", Число компонент: " << table[index].componentCount
                  << ", Тип компонент: " << table[index].componentType << "\n";
    } else {
        std::cout << "Объект не найден.\n";
    }

    return 0;
}