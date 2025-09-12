#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node {
    char data;
    Node* next;
};

Node* makeNode(char c) {
    Node* newNode = new Node;
    newNode->data = c;
    newNode->next = nullptr;
    return newNode;
}

void appendNode(Node*& head, char c) {
    Node* newNode = makeNode(c);
    if (!head) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

bool contains(Node* s1, Node* s2) {
    if (!s1) return true;
    
    while (s2) {
        Node* temp1 = s1;
        Node* temp2 = s2;
        bool fl = true;
        
        while (temp1 and temp2) {
            if (temp1->data != temp2->data) {
                fl = false;
                break;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        
        if (fl and !temp1) return true;
        s2 = s2->next;
    }
    return false;
}

int main() {
    Node* list1 = nullptr;
    Node* list2 = nullptr;
    
    ifstream file("data.txt");    
    string line;
    getline(file, line);
    
    bool second_list = false;
    for(char elem : line) {
        if (elem == ',') {
            second_list = true;
            continue;
        }
        
        if (elem == ' ') continue;
        
        if (!second_list) {
            appendNode(list1, elem);
        } else {
            appendNode(list2, elem);
        }
    }

    if (contains(list2, list1)) {
        cout << "Вторая последовательность содержится в первой\n";
    } else {
        cout << "Вторая последовательность НЕ содержится в первой\n";
    }
    
    if (contains(list1, list2)) {
        cout << "Первая последовательность содержится во второй\n";
    } else {
        cout << "Первая последовательность НЕ содержится во второй\n";
    } 

    while (list1) {
        Node* temp = list1;
        list1 = list1->next;
        delete temp;
    }
    while (list2) {
        Node* temp = list2;
        list2 = list2->next;
        delete temp;
    }
    
    return 0;
}