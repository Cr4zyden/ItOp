#include <iostream>
#include <fstream>
#include <string>

struct TreeNode {
    int value; // Значение узла
    TreeNode* left; // Указатель на левого потомка
    TreeNode* right; // Указатель на правого потомка

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

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

TreeNode* removeMaxValue(TreeNode* root) {
    if (!root) {
        std::cerr << "Дерево пустое!" << std::endl;
        return nullptr;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr;
    while (current->right) {
        std::cout<<current->value<<" ";
        parent = current;
        current = current->right;
    }
    std::cout<<std::endl;
    if (!parent) {
        TreeNode* newRoot = root->left; 
        delete root;
        return newRoot;
    }

    parent->right = current->left; 
    delete current;

    return root;
}

void printTree(TreeNode* root) {
    if (!root) {
        return;
    }
    printTree(root->left);
    std::cout << root->value << " ";
    printTree(root->right);
}

int main() {
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    TreeNode* root = nullptr;
    std::string line;

    while (std::getline(file, line)) {
        std::string temp = "";
        for (char ch : line) {
            if (ch == ' ' or ch == '\n') {
                if (!temp.empty()) {
                    int value = std::stoi(temp);
                    root = insertIntoBST(root, value);
                    temp.clear();
                }
            } else {
                temp += ch;
            }
        }
        if (!temp.empty()) {
            int value = std::stoi(temp);
            if (value != 0) root = insertIntoBST(root, value);
        }
    }

    std::cout << "Изначальная последовательность: ";
    printTree(root);
    std::cout << std::endl;

    root = removeMaxValue(root);

    std::cout << "Последовательность после удаления максимального элемента: ";
    printTree(root);
    std::cout << std::endl;

    return 0;
}