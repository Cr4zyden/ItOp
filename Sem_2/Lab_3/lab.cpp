#include <iostream>

// Определение структуры узла бинарного дерева
struct TreeNode {
    int value; // Значение узла
    TreeNode* left; // Указатель на левого потомка
    TreeNode* right; // Указатель на правого потомка

    // Конструктор для удобства создания узлов
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Определение структуры узла односвязного списка (для стека)
struct StackNode {
    TreeNode* node; // Указатель на узел дерева
    StackNode* next; // Указатель на следующий узел

    // Конструктор для удобства создания узлов
    StackNode(TreeNode* n) : node(n), next(nullptr) {}
};

// Функция для проверки, пуст ли стек
bool isEmpty(StackNode* topNode) {
    return topNode == nullptr;
}

// Функция для добавления элемента в стек
void push(StackNode** topNode, TreeNode* node) {
    StackNode* newNode = new StackNode(node);
    newNode->next = *topNode; // Новый узел указывает на текущую вершину
    *topNode = newNode; // Обновляем вершину стека
}

// Функция для удаления элемента из стека
void pop(StackNode** topNode) {
    if (isEmpty(*topNode)) {
        std::cerr << "Ошибка: попытка удалить элемент из пустого стека!" << std::endl;
        return;
    }
    StackNode* temp = *topNode; // Сохраняем текущую вершину
    *topNode = (*topNode)->next; // Перемещаем вершину на следующий узел
    delete temp; // Освобождаем память
}

// Функция для получения значения верхнего элемента стека
TreeNode* top(StackNode* topNode) {
    if (isEmpty(topNode)) {
        std::cerr << "Ошибка: попытка получить значение из пустого стека!" << std::endl;
        return nullptr; // Возвращаем nullptr как ошибочное значение
    }
    return topNode->node;
}

// Функция для добавления значения в бинарное дерево поиска
TreeNode* insertIntoBST(TreeNode* root, int value) {
    if (!root) {
        return new TreeNode(value); // Если дерево пустое, создаем новый узел
    }

    if (value < root->value) {
        root->left = insertIntoBST(root->left, value); // Добавляем в левое поддерево
    } else {
        root->right = insertIntoBST(root->right, value); // Добавляем в правое поддерево
    }

    return root;
}

// Функция для поиска минимального значения в бинарном дереве с использованием стека
int findMinimumValue(TreeNode* root) {
    if (!root) {
        return 0; // Если дерево пустое, возвращаем 0 (можно изменить на другое значение)
    }

    // Инициализация стека для обхода в глубину
    StackNode* stackTop = nullptr;
    push(&stackTop, root);

    // Переменная для хранения минимального значения
    int minValue = root->value;

    // Обход дерева в глубину с использованием стека
    while (!isEmpty(stackTop)) {
        TreeNode* current = top(stackTop); // Получаем указатель на текущий узел
        pop(&stackTop); // Удаляем вершину стека

        // Обновляем минимальное значение
        if (current->value < minValue) {
            minValue = current->value;
        }

        // Добавляем потомков в стек (если они существуют)
        if (current->left) {
            push(&stackTop, current->left);
        }
        if (current->right) {
            push(&stackTop, current->right);
        }
    }

    return minValue;
}

// Пример использования
int main() {
    std::cout << "Введите числа через пробел (для завершения введите 0): ";

    TreeNode* root = nullptr;
    int value;

    // Считываем числа до тех пор, пока не будет введен 0
    while (std::cin >> value && value != 0) {
        root = insertIntoBST(root, value);
    }

    // Поиск минимального значения
    int minValue = findMinimumValue(root);
    std::cout << "Минимальное значение в дереве: " << minValue << std::endl;

    // Освобождение памяти (опционально, если не используется умный указатель)
    // Здесь нужно реализовать рекурсивное удаление дерева
    return 0;
}