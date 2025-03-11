#include <iostream>
#include <fstream>
#include <string>

struct queue
{    
    int beg = 0;
    int end = -1;
    int size = 100;
    int vals[100] = {};
};

void push(queue* q, int val) {
    if (q->end >= q->size - 1) return; 
    q->end++;
    q->vals[q->end] = val;
}

void pop(queue* q) {
    if (q->beg > q->end) return; 
    std::cout << q->vals[q->beg] << std::endl;
    q->beg++;
}

int main() {
    bool sign_flag = false;
    int num;

    queue* q = new queue();

    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::string temp_str;
    
    while (std::getline(file, temp_str)) {
        for (char elem : temp_str) {
            if (elem == ' ') continue;
            if (elem == '-') {
                sign_flag = true;
                continue;
            }
            if (elem == '0') {
                break;
            }
            if (std::isdigit(elem)) {
                num = elem - '0';
                if (sign_flag) {
                    num *= -1;
                    sign_flag = false;
                }
                push(q, num);
            }
        }

    }

    std::cout << "Отрицательные элементы:" << std::endl;
    for (int i = q->beg; i <= q->end; i++) {
        if (q->vals[i] < 0) {
            std::cout << q->vals[i] << std::endl;
        }
    }

    std::cout << "Положительные элементы:" << std::endl;
    for (int i = q->beg; i <= q->end; i++) {
        if (q->vals[i] >= 0) {
            std::cout << q->vals[i] << std::endl;
        }
    }
    delete q;

    return 0;
}