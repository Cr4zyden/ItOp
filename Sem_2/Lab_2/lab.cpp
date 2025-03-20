#include <iostream>
using namespace std;

const int MAX_SIZE = 3; // Максимальный размер очереди

// Структура для обеих очередей
struct Queue {
    int data[MAX_SIZE]; // Массив для хранения элементов
    int front, back;    // Указатели на начало и конец очереди
    int size;           // Текущий размер очереди
    bool isCircular;    // Флаг для определения типа очереди
};

// Общие функции для обеих очередей
void initQueue(Queue &q, bool isCircular) {
    q.front = q.back = 0;
    q.size = 0;
    q.isCircular = isCircular;
}

bool isEmpty(const Queue &q) {
    return q.size == 0;
}

bool isFull(const Queue &q) {
    return q.size == MAX_SIZE;
}

void shiftElements(Queue &q) {
    if (!q.isCircular && q.front > 0) { // Перенос только для линейной очереди
        for (int i = q.front; i < q.back; ++i) {
            q.data[i - q.front] = q.data[i];
        }
        q.back -= q.front;
        q.front = 0;
    }
}

int enqueue(Queue &q, int value) {
    cout<<"BACK: "<<q.back<<endl;
    cout<<"FRONT: "<<q.front<<endl;

    if (isFull(q)) {
        if (!q.isCircular) {
            shiftElements(q); // Переносим элементы для линейной очереди
            if (isFull(q)) {
                return 1; // Очередь всё ещё полная
            }
        } else {
            return 1; // Циклическая очередь полная
        }
    }

    q.data[q.back] = value;
    if (q.isCircular) {
        q.back = (q.back + 1) % MAX_SIZE; // Циклический переход
    } else {
        q.back++; // Линейный переход
    }
    q.size++;
    return 0; // Успешно добавлено
}

int dequeue(Queue &q, int &value) {
    cout<<"BACK: "<<q.back<<endl;
    cout<<"FRONT: "<<q.front<<endl;

    if (isEmpty(q)) {
        return 2; // Очередь пуста
    }
    value = q.data[q.front];
    if (q.isCircular) {
        q.front = (q.front + 1) % MAX_SIZE; // Циклический переход
    } else {
        q.front++; // Линейный переход
    }
    q.size--;
    return 0; // Успешно взято
}

// Функция для вывода элементов очереди
void printQueue(const Queue &q) {
    cout << "Текущее состояние очереди: ";
    if (isEmpty(q)) {
        cout << "Очередь пуста.\n";
        return;
    }

    if (q.isCircular) {
        for (int i = 0; i < q.size; ++i) {
            int index = (q.front + i) % MAX_SIZE; // Индекс с учётом цикличности
            cout << q.data[index] << " ";
        }
    } else {
        for (int i = q.front; i < q.back; ++i) {
            cout << q.data[i] << " ";
        }
    }
    cout << "\n";
}

void handleQueue(Queue &q) {
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Проверить, пуста ли очередь\n";
        cout << "2. Добавить элемент\n";
        cout << "3. Взять элемент\n";
        cout << "4. Выход\n";
        int op;
        cin >> op;

        if (op == 1) {
            if (isEmpty(q)) {
                cout << "Очередь пуста.\n";
            } else {
                cout << "Очередь не пуста.\n";
            }
        } else if (op == 2) {
            cout << "Введите элемент для добавления: ";
            int value;
            cin >> value;
            int result = enqueue(q, value);
            if (result == 1) {
                cout << "Ошибка: очередь переполнена.\n";
            } else {
                cout << "Элемент добавлен.\n";
            }
        } else if (op == 3) {
            int value;
            int result = dequeue(q, value);
            if (result == 2) {
                cout << "Ошибка: очередь пуста.\n";
            } else {
                cout << "Извлечён элемент: " << value << "\n";
            }
        } else if (op == 4) {
            break;
        } else {
            cout << "Неверный выбор!\n";
        }

        // Вывод текущего состояния очереди после каждой операции
        printQueue(q);
    }
}

// Интерфейс для пользователя
void menu() {
    cout << "Выберите тип очереди:\n";
    cout << "1. Линейная очередь с переносом\n";
    cout << "2. Циклическая очередь\n";
    int choice;
    cin >> choice;

    Queue q;
    if (choice == 1) {
        initQueue(q, false); // Линейная очередь
        handleQueue(q);
    } else if (choice == 2) {
        initQueue(q, true); // Циклическая очередь
        handleQueue(q);
    } else {
        cout << "Неверный выбор!\n";
    }
}

int main() {
    menu();
    return 0;
}