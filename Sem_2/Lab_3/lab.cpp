#include <iostream>

// Определение структуры узла бинарного дерева
struct TreeNode {
    int value; // Значение узла
    TreeNode* left; // Указатель на левого потомка
    TreeNode* right; // Указатель на правого потомка

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Определение структуры узла односвязного списка (для стека)
struct StackNode {
    TreeNode* node; // Указатель на узел дерева
    StackNode* next; // Указатель на следующий узел

    StackNode(TreeNode* n) : node(n), next(nullptr) {}
};

// Функция для проверки, пуст ли стек
bool isEmpty(StackNode* topNode) {
    return topNode == nullptr;
}

// Функция для добавления элемента в стек
void push(StackNode** topNode, TreeNode* node) {
    StackNode* newNode = new StackNode(node);
    newNode->next = *topNode; 
    *topNode = newNode; 
}

// Функция для удаления элемента из стека
void pop(StackNode** topNode) {
    if (isEmpty(*topNode)) {
        std::cerr << "Ошибка: попытка удалить элемент из пустого стека!" << std::endl;
        return;
    }
    StackNode* temp = *topNode; 
    *topNode = (*topNode)->next; 
    delete temp; 
}

// Функция для получения значения верхнего элемента стека
TreeNode* top(StackNode* topNode) {
    if (isEmpty(topNode)) {
        std::cerr << "Ошибка: попытка получить значение из пустого стека!" << std::endl;
        return nullptr; 
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
        return 0; // Если дерево пустое, возвращаем 0 
    }

    // Инициализация стека для обхода в глубину
    StackNode* stackTop = nullptr;
    push(&stackTop, root);

    // Переменная для хранения минимального значения
    int minValue = root->value;

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

int main() {
    std::cout << "Введите числа через пробел (для завершения введите 0): \n";

    TreeNode* root = nullptr;
    int value;

    while (std::cin >> value && value != 0) {
        root = insertIntoBST(root, value);
    }

    int minValue = findMinimumValue(root);
    std::cout << "Минимальное значение в дереве: " << minValue << std::endl;

    return 0;
}