#include <iostream>

// Определяем структуру узла двусвязного циклического списка
struct Node {
    bool data;
    Node* next;
    Node* prev;
};

// Функция для добавления элемента в конец списка
void append(Node*& head, bool value) {
    Node* newNode = new Node{value, nullptr, nullptr};
    if (head == nullptr) {
        // Если список пуст, создаем новый узел и делаем его циклическим
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    } else {
        // Вставляем новый узел перед головой (так как список циклический)
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }
}

// Функция для вывода списка
void printList(Node* head) {
    if (head == nullptr) {
        std::cout << "Список пуст." << std::endl;
        return;
    }
    Node* temp = head;
    while (true) {
        std::cout << temp->data << " ";
        temp = temp->next;
        if (temp == head) break; // Выход из цикла, если вернулись к голове
    }
    std::cout << std::endl;
}

// Функция для поиска элемента в списке
Node* search(Node* head, bool value) {
    if (head == nullptr) {
        return nullptr; // Список пуст
    }
    Node* temp = head;
    while (true) {
        if (temp->data == value) {
            return temp; // Элемент найден
        }
        temp = temp->next;
        if (temp == head) break; // Выход из цикла, если вернулись к голове
    }
    return nullptr; // Элемент не найден
}

// Функция для удаления элемента из списка
void remove(Node*& head, bool value) {
    if (head == nullptr) {
        return; // Список пуст, нечего удалять
    }

    // Поиск узла с заданным значением
    Node* toDelete = search(head, value);
    if (toDelete == nullptr) {
        return; // Элемент не найден
    }

    // Если удаляемый узел — единственный в списке
    if (toDelete->next == toDelete and toDelete->prev == toDelete) {
        delete toDelete;
        head = nullptr; // Список становится пустым
        return;
    }

    // Если удаляемый узел — голова списка
    if (toDelete == head) {
        head = head->next; // Обновляем голову
    }

    // Пересвязываем соседние узлы
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;

    // Освобождаем память
    delete toDelete;
}

// Функция для освобождения памяти, выделенной под список
void deleteList(Node*& head) {
    if (head == nullptr) return;
    Node* current = head;
    Node* nextNode;
    while (true) {
        nextNode = current->next;
        delete current;
        current = nextNode;
        if (current == head) break; // Выход из цикла, если вернулись к голове
    }
    head = nullptr;
}
// Функция для включения элемента в список
void insert(Node*& head, bool value, bool afterValue) {
    if (head == nullptr) {
        // Если список пуст, просто добавляем элемент
        append(head, value);
        return;
    }

    // Поиск узла, после которого нужно вставить новый элемент
    Node* temp = head;
    do {
        if (temp->data == afterValue) {
            // Создаем новый узел
            Node* newNode = new Node{value, temp->next, temp};
            // Пересвязываем соседние узлы
            temp->next->prev = newNode;
            temp->next = newNode;
            return;
        }
        temp = temp->next;
    } while (temp != head);

    // Если элемент afterValue не найден, добавляем новый элемент в конец списка
    append(head, value);
}

// Функция для определения числа звеньев в списке
int countNodes(Node* head) {
    if (head == nullptr) {
        return 0; // Список пуст
    }
    int count = 0;
    Node* temp = head;
    while (true) {
        count++;
        temp = temp->next;
        if (temp == head) break; // Выход из цикла, если вернулись к голове
    }
    return count;
}

// Функция для копирования списка
Node* copyList(Node* head) {
    if (head == nullptr) return nullptr; // Если исходный список пуст, возвращаем nullptr

    Node* copiedHead = nullptr;
    Node* temp = head;

    do {
        append(copiedHead, temp->data); // Добавляем элементы в новый список
        temp = temp->next;
    } while (temp != head);

    return copiedHead; // Возвращаем голову скопированного списка
}

// Функция для объединения двух списков
Node* mergeLists(Node* list1, Node* list2) {
    if (list1 == nullptr and list2 == nullptr) return nullptr; // Если оба списка пусты, возвращаем nullptr
    if (list1 == nullptr) return list2; // Если первый список пуст, возвращаем второй
    if (list2 == nullptr) return list1; // Если второй список пуст, возвращаем первый

    Node* lastOfList1 = list1->prev; // Последний узел первого списка
    Node* lastOfList2 = list2->prev; // Последний узел второго списка

    // Пересвязываем указатели
    lastOfList1->next = list2;
    list2->prev = lastOfList1;
    lastOfList2->next = list1;
    list1->prev = lastOfList2;

    return list1; // Возвращаем голову объединенного списка
}

int main() {
    // Переменная p — это голова двусвязного циклического списка
    Node* p = nullptr;

    // Добавляем элементы в список
    append(p, true);  
    append(p, false); 

    // Выводим список
    std::cout << "Список p: ";
    printList(p);

    // Освобождаем память
    deleteList(p);

    return 0;
}
