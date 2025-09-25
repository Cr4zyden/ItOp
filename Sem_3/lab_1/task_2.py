nums_to_val = {0: '0',
        1: '1',
        2: '2',
        3: '3',
        4: '4',
        5: '5',
        6: '6',
        7: '7',
        8: '8',
        9: '9',
        10: 'A',
        11: 'B',
        12: 'C',
        13: 'D',
        14: 'E',
        15: 'F'}

val_to_nums = {'0': 0,
        '1': 1,
        '2': 2,
        '3': 3,
        '4': 4,
        '5': 5,
        '6': 6,
        '7': 7,
        '8': 8,
        '9': 9,
        'A': 10,
        'B': 11,
        'C': 12,
        'D': 13,
        'E': 14,
        'F': 15}

print("Введите два числа и их системы счисления")
n = input("a: ")
m = input("b: ")
r = int(input("Система счисления: "))
operation = int(input("Выберите арифметическую операцию: \n1 - сложение\n2 - умножение\n"))

def transform(n, m):
    
    #добавляем незначащие нули в конец нецелой части числа, чтобы длина была одинаковой
    nf, mf = n.find('.'), m.find('.')
    past_n, past_m = 0, 0 #количество знаков после запятой у n и m
    flag = False #истина - число нецелое (есть точка), иначе - число целое
    if nf != -1:
        past_n = len(n[nf+1::]) #колиество символов после точки
        n = n.replace('.', '')
        flag = True
    if mf != -1:
        past_m = len(m[mf+1::]) #колиество символов после точки
        m = m.replace('.', '')
        flag = True
    dot = max(past_n, past_m) #куда потом вернуть точку в числе

    if past_n < past_m: n += '0'*(past_m-past_n)
    if past_n > past_m: m += '0'*(past_n-past_m)

    #добавляем незначащие нули в начало, чтобы длина чисел была одинаковой
    add = max(len(n), len(m)) #число максимальной длины (чтобы добавить в остальные нули)
    n, m = n.zfill(add), m.zfill(add)

    return [n, m, add, dot, flag]

def to_val(n):
    return nums_to_val[n]
def to_num(n):
    return val_to_nums[n]

#операция сложения
def summa(n, m, r): #n, m - числа в r-й системе счисления

    transformed_nm = transform(n, m)
    n, m, add, dot, flag = transformed_nm[0][::-1], transformed_nm[1][::-1], transformed_nm[2], transformed_nm[3], transformed_nm[4]

    carry = 0 #остаток, который переносим на след. разряд
    result = ""
    for i in range(add):
        a = to_num(n[i])+to_num(m[i])+carry

        if carry != 0: carry -= 1
        if a >= r:
            carry += 1
            a = a-r
        result += to_val(a)
    result = (result + to_val(carry))[::-1]

    if flag:
        result = result[:len(result)-dot] + '.' + result[len(result)-dot::]
        return(result.strip('0').rstrip('.')) #удаляем через lstrip все незначащие нули, добавленные в начале
    
    return(result.lstrip('0')) #удаляем через lstrip все незначащие нули, добавленные в начале

#операция умножения
def multiplication(n, m, r):
    dot = 0
    len_dot_n = len(n[n.find('.')+1::])
    len_dot_m = len(m[m.find('.')+1::])
    if n.find('.') != -1 and dot < len_dot_n: dot = len_dot_n
    if m.find('.') != -1 and dot < len_dot_m: dot = len_dot_m

    transformed_nm = transform(n, m)
    n, m, flag = transformed_nm[0][::-1], transformed_nm[1][::-1], transformed_nm[4]

    for_summa = [] #список чисел, которые будем складывать после поразрядного умножения
    carry = 0 #остаток, который переносим на след. разряд
    counter = -1 #будем добавлять '0'*counter к каждому слагаемому, чтобы сдвинуть разряд для итогового вычисления

    for i_m in m:
        res = ""
        counter += 1
        for i_n in n:

            mult = (to_num(i_m)*to_num(i_n))+carry
            carry = 0 #после прибавки обнуляем
            if mult >= r:
                carry = mult//r
                mult = mult%r
            res += to_val(mult)

        if carry != 0:
            if mult >= r:
                carry = mult//r
                mult = mult%r
                res += to_val(mult)
            res += to_val(carry)
            carry = 0 #после прибавки обнуляем

        for_summa.append(res[::-1]+'0'*counter)

    answer = for_summa[0]
    for elem in for_summa[1::]:
        answer = summa(answer, elem, r)

    if flag:
        answer = answer[:len(answer)-dot*2:]+ "." + answer[len(answer)-dot*2::]
        return(answer.strip('0').rstrip('.'))
    return(answer)

if operation == 1: print("Сумма a и b:", summa(n, m, r))
else: print("Произведение a и b:", multiplication(n, m, r))