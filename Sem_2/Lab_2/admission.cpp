#include <iostream>
#include <fstream>
#include <string>

struct Stack
{    
    int top;
    char arr[100];
};

void push(Stack*& stack, char val){
    if(stack->top >= 100 - 1){
        //std::cout<<"Stack overflow"<<std::endl;
        return;
    }
    stack->top++;
    stack->arr[stack->top] = val;
}

void print(Stack* stack){
    while (stack->top >=0)
    {
        std::cout<<stack->arr[stack->top]<<std::endl;
        stack->top--;
    }
}

char pop(Stack*& stack) {
    if (stack->top < 0) {
        std::cout << "Stack is empty\n";
        // throw std::underflow_error("Stack is empty");
        return -1;  // Return -1 or handle underflow differently
    } else {
        stack->top--;
        return stack->arr[stack->top+1];  // Return the top item and decrement top
    }
}

int main(){
    Stack* f;
    f->top = -1;
    char last = NULL;
    std::ifstream file("data.txt");
    std::string temp_str;
    std::getline(file, temp_str);
    for(char elem: temp_str){
        if(elem == ' ') continue;
        if(elem == '&' or elem == '|'){ 
            last = pop(f);
            push(f, elem);
        }
        else{
        
        }
    }
    print(f);

}