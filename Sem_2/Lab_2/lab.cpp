#include <iostream>
using namespace std;

const int MAX_SIZE = 3; // Максимальный размер массива для очереди

// Структура для элемента стека (односвязный список)
struct StackNode {
    int data;           // Данные элемента
    StackNode* next;    // Указатель на следующий элемент
};

// Структура для стека
struct Stack {
    StackNode* top;     // Указатель на вершину стека
};

// Структура для очереди
struct Queue {
    int data[MAX_SIZE]; // Массив для хранения элементов
    int front, back;    // Указатели на начало и конец
    int size;           // Текущий размер очереди
    bool isCircular;    // Флаг циклической очереди
};

// Инициализация очереди
void initQueue(Queue &q, bool isCircular) {
    q.front = q.back = q.size = 0;
    q.isCircular = isCircular;
}

// Очистка очереди
void clearQueue(Queue &q) {
    q.front = q.back = q.size = 0;
}

// Проверка, пуста ли очередь
bool isEmptyQueue(const Queue &q) {
    return q.size == 0;
}

// Проверка, полна ли очередь
bool isFullQueue(const Queue &q) {
    if (q.isCircular) {
        return q.size == MAX_SIZE;
    } else {
        return q.back == MAX_SIZE;
    }
}

// Перенос элементов для линейной очереди
void shiftElements(Queue &q) {
    if (q.isCircular || q.front == 0) return;

    for (int i = 0; i < q.size; ++i) {
        q.data[i] = q.data[q.front + i];
    }
    q.back = q.size;
    q.front = 0;
}

// Добавление элемента в очередь
int append(Queue &q, int value) {
    if (isFullQueue(q)) {
        if (!q.isCircular) {
            shiftElements(q);
            if (isFullQueue(q)) return 1;
        } else {
            return 1;
        }
    }

    q.data[q.back] = value;
    if (q.isCircular) {
        q.back = (q.back + 1) % MAX_SIZE;
    } else {
        q.back++;
    }
    q.size++;
    return 0;
}

// Удаление элемента из очереди
int dequeue(Queue &q, int &value) {
    if (isEmptyQueue(q)) return 2;

    value = q.data[q.front];
    if (q.isCircular) {
        q.front = (q.front + 1) % MAX_SIZE;
    } else {
        q.front++;
    }
    q.size--;
    return 0;
}

// Вывод состояния очереди
void printQueue(const Queue &q) {
    cout << "Очередь: ";
    if (isEmptyQueue(q)) {
        cout << "пуста\n";
        return;
    }

    int current = q.front;
    for (int i = 0; i < q.size; ++i) {
        cout << q.data[current] << " ";
        current = q.isCircular ? (current + 1) % MAX_SIZE : current + 1;
    }
    cout << "\nfront=" << q.front << ", back=" << q.back 
         << ", size=" << q.size << endl;
}

// Инициализация стека
void initStack(Stack &s) {
    s.top = nullptr; // Стек пустой
}

// Очистка стека
void clearStack(Stack &s) {
    while (s.top != nullptr) {
        StackNode* temp = s.top;
        s.top = s.top->next;
        delete temp;
    }
}

// Проверка, пуст ли стек
bool isEmptyStack(const Stack &s) {
    return s.top == nullptr;
}

// Добавление элемента в стек
int push(Stack &s, int value) {
    StackNode* newNode = new StackNode{value, s.top};
    if (!newNode) return 1; // Ошибка выделения памяти
    s.top = newNode;
    return 0; 
}

// Удаление элемента из стека
int pop(Stack &s, int &value) {
    if (isEmptyStack(s)) return 2; // Стек пуст

    StackNode* temp = s.top;
    value = temp->data;
    s.top = s.top->next;
    delete temp;
    return 0; 
}

// Вывод состояния стека
void printStack(const Stack &s) {
    cout << "Стек: ";
    if (isEmptyStack(s)) {
        cout << "пуст\n";
        return;
    }

    StackNode* current = s.top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Обработка очереди
void handleQueue(Queue &q) {
    while (true) {
        cout << "\nМеню очереди:\n";
        cout << "1. Проверить, пуста ли очередь\n";
        cout << "2. Добавить элемент\n";
        cout << "3. Взять элемент\n";
        cout << "4. Очистить очередь\n";
        cout << "5. Выход\n";
        int op;
        cin >> op;

        if (op == 1) {
            cout << (isEmptyQueue(q) ? "Очередь пуста.\n" : "Очередь не пуста.\n");
        } else if (op == 2) {
            cout << "Введите элемент для добавления: ";
            int value;
            cin >> value;
            int result = append(q, value);
            cout << (result ? "Ошибка: очередь переполнена.\n" : "Элемент добавлен.\n");
        } else if (op == 3) {
            int value;
            int result = dequeue(q, value);
            cout << (result ? "Ошибка: очередь пуста.\n" : "Извлечён элемент: " + to_string(value) + "\n");
        } else if (op == 4) {
            clearQueue(q);
            cout << "Очередь очищена.\n";
        } else if (op == 5) {
            break;
        } else {
            cout << "Неверный выбор!\n";
        }

        printQueue(q);
    }
}

// Обработка стека
void handleStack(Stack &s) {
    while (true) {
        cout << "\nМеню стека:\n";
        cout << "1. Проверить, пуст ли стек\n";
        cout << "2. Добавить элемент\n";
        cout << "3. Взять элемент\n";
        cout << "4. Очистить стек\n";
        cout << "5. Выход\n";
        int op;
        cin >> op;

        if (op == 1) {
            cout << (isEmptyStack(s) ? "Стек пуст.\n" : "Стек не пуст.\n");
        } else if (op == 2) {
            cout << "Введите элемент для добавления: ";
            int value;
            cin >> value;
            int result = push(s, value);
            cout << (result ? "Ошибка: переполнение стека.\n" : "Элемент добавлен.\n");
        } else if (op == 3) {
            int value;
            int result = pop(s, value);
            cout << (result ? "Ошибка: стек пуст.\n" : "Извлечён элемент: " + to_string(value) + "\n");
        } else if (op == 4) {
            clearStack(s);
            cout << "Стек очищен.\n";
        } else if (op == 5) {
            break;
        } else {
            cout << "Неверный выбор!\n";
        }
        printStack(s);
    }
}

// Главное меню
void menu() {
    cout << "Выберите структуру данных:\n";
    cout << "1. Очередь\n";
    cout << "2. Стек\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Выберите тип очереди:\n";
        cout << "1. Линейная очередь с переносом\n";
        cout << "2. Циклическая очередь\n";
        int queueChoice;
        cin >> queueChoice;

        Queue q;
        initQueue(q, queueChoice == 2);
        handleQueue(q);
    } else if (choice == 2) {
        Stack s;
        initStack(s);
        handleStack(s);
    } else {
        cout << "Неверный выбор!\n";
    }
}

int main() {
    menu();
    return 0;
}