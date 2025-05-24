#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

// Глобальные переменные
string expr1, expr2;
set<char> variables;

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ 

// Проверяет, является ли символ операцией или скобкой
bool isOperatorOrBracket(char c) {
    return c == '!' || c == '&' || c == '|' || c == '(' || c == ')';
}

// Извлекает все переменные из строки
void extractVariables(const string& expr) {
    for (char c : expr) {
        if (isupper(c)) {
            variables.insert(c);
        }
    }
}

// Проверка корректности ввода выражения
bool isValidExpression(const string& expr) {
    int openParentheses = 0, closeParentheses = 0;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // Пропускаем пробелы
        if (isspace(c)) continue;

        // Проверка допустимых символов
        if (!isupper(c) && !isOperatorOrBracket(c)) {
            cout << "Ошибка: Недопустимый символ '" << c << "' в выражении." << endl;
            return false;
        }

        // Подсчет скобок
        if (c == '(') openParentheses++;
        if (c == ')') closeParentheses++;

        // Проверка на недопустимые комбинации символов
        if (i > 0) {
            char prev = expr[i - 1];
            if (isOperatorOrBracket(prev) && isOperatorOrBracket(c)) {
                // Разрешаем комбинации '(', ')', '|', '&' только в определённых случаях
                if (!((prev == '(' && c == '!') ||  // Отрицание после открывающей скобки
                      (prev == ')' && c == '|') ||  // Дизъюнкция после закрывающей скобки
                      (prev == ')' && c == '&') ||  // Конъюнкция после закрывающей скобки
                      (prev == '!' && isupper(c)) || // Переменная после отрицания
                      (prev == '&' && isupper(c)) || // Переменная после конъюнкции
                      (prev == '|' && isupper(c)) ||
                      (prev == '&' && c == '(') ||
                      (prev == '|' && c == '('))) { // Переменная после дизъюнкции
                    cout << "Ошибка: Недопустимая комбинация символов '" << prev << "' и '" << c << "'." << endl;
                    return false;
                }
            }
        }
    }

    // Проверка баланса скобок
    if (openParentheses != closeParentheses) {
        cout << "Ошибка: Несбалансированные скобки." << endl;
        return false;
    }

    return true;
}

// Проверка, является ли выражение ДНФ

bool isDNF(const string& expr) {
    int bracketDepth = 0;
    bool inConjunction = false;

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];

        // Пропускаем пробелы
        if (isspace(c)) continue;

        // Отслеживаем глубину скобок
        if (c == '(') bracketDepth++;
        if (c == ')') bracketDepth--;

        // Проверяем структуру ДНФ
        if (bracketDepth == 0 && c == '|') {
            // Вне скобок может быть только дизъюнкция
            continue;
        } else if (bracketDepth > 0 && c == '&') {
            // Внутри скобок может быть только конъюнкция
            inConjunction = true;
        } else if (bracketDepth > 0 && c == '|') {
            // Конъюнкция внутри скобок не должна содержать дизъюнкции
            cout << "Ошибка: Внутри скобок обнаружена недопустимая дизъюнкция." << endl;
            return false;
        }

        // Проверка наличия скобок вокруг конъюнкции
        if (c == '&' && bracketDepth == 0) {
            cout << "Ошибка: Недопустимая структура ДНФ. Конъюнкция должна быть в скобках." << endl;
            return false;
        }
    }

    // Если есть хотя бы одна конъюнкция внутри скобок, это ДНФ
    return inConjunction;
}

// Вычисляет значение подвыражения в скобках
int findClosingParenthesis(const string& expr, int openPos) {
    int depth = 0;
    for (int i = openPos; i < expr.size(); ++i) {
        if (expr[i] == '(') depth++;
        else if (expr[i] == ')') {
            depth--;
            if (depth == 0) return i;
        }
    }
    return -1;
}

// Рекурсивно вычисляет значение выражения
bool evaluate(const string& expr, const vector<bool>& values) {
    // Если это одна переменная
    if (expr.size() == 1 && isupper(expr[0])) {
        int idx = expr[0] - 'A';
        return values[idx];
    }

    // Если начинается с NOT
    if (expr[0] == '!') {
        string sub = expr.substr(1);
        return !evaluate(sub, values);
    }

    // Если в скобках
    if (expr[0] == '(') {
        int closing = findClosingParenthesis(expr, 0);
        if (closing == expr.size() - 1) {
            return evaluate(expr.substr(1, closing - 1), values);
        }
    }

    // Поиск последней операции по приоритету: & > | (слева направо)
    int bracketDepth = 0;
    int lastAnd = -1, lastOr = -1;

    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (c == '(') bracketDepth++;
        else if (c == ')') bracketDepth--;
        else if (bracketDepth == 0) {
            if (c == '&') lastAnd = i;
            else if (c == '|') lastOr = i;
        }
    }

    if (lastAnd != -1) {
        string left = expr.substr(0, lastAnd);
        string right = expr.substr(lastAnd + 1);
        return evaluate(left, values) && evaluate(right, values);
    }

    if (lastOr != -1) {
        string left = expr.substr(0, lastOr);
        string right = expr.substr(lastOr + 1);
        return evaluate(left, values) || evaluate(right, values);
    }

    return false; // ошибка
}

// Генерация таблицы истинности
vector<bool> generateTruthTable(const string& expr, int varCount) {
    int rows = pow(2, varCount);
    vector<bool> table(rows);

    for (int i = 0; i < rows; ++i) {
        vector<bool> values(varCount);
        for (int j = 0; j < varCount; ++j) {
            values[j] = (i >> (varCount - j - 1)) & 1;
        }

        table[i] = evaluate(expr, values);
    }

    return table;
}

// Сравнение таблиц истинности
bool compareTruthTables(const vector<bool>& table1, const vector<bool>& table2) {
    for (size_t i = 0; i < table1.size(); ++i) {
        if (table1[i] != table2[i]) {
            return false;
        }
    }
    return true;
}

// === ОСНОВНАЯ ПРОГРАММА ===

int main() {
    setlocale(LC_ALL, "ru");

    // Ввод первой формулы (ДНФ)
    while (true) {
        cout << "Введите первую формулу (например: (A&B)|(C&D)): ";
        getline(cin, expr1);

        if (isValidExpression(expr1) && isDNF(expr1)) {
            break;
        } else {
            cout << "Пожалуйста, исправьте ошибки во вводе или убедитесь, что это ДНФ." << endl;
        }
    }

    // Ввод второй формулы (расширенная формула)
    while (true) {
        cout << "Введите вторую формулу (например: A&(B|C)): ";
        getline(cin, expr2);

        if (isValidExpression(expr2)) {
            break;
        } else {
            cout << "Пожалуйста, исправьте ошибки во вводе и попробуйте снова." << endl;
        }
    }

    // Извлечение переменных
    extractVariables(expr1);
    extractVariables(expr2);

    vector<char> varList(variables.begin(), variables.end());
    int varCount = varList.size();

    if (varCount > 10) {
        cout << "Слишком много переменных (>10). Программа не может обработать." << endl;
        return 1;
    }

    // Построение таблиц истинности
    vector<bool> table1 = generateTruthTable(expr1, varCount);
    vector<bool> table2 = generateTruthTable(expr2, varCount);

    // Сравнение таблиц
    if (compareTruthTables(table1, table2)) {
        cout << "Формулы эквивалентны." << endl;
    } else {
        cout << "Формулы не эквивалентны." << endl;
    }

    return 0;
}