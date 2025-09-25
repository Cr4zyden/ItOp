def decimal_to_base_r(num, r):
    sign = '-' if num < 0 else ''
    num = abs(num)

    # Разделение на целую и дробную части
    integer_part = int(num)
    fractional_part = num - integer_part

    # Перевод целой части
    if integer_part == 0:
        integer_str = '0'
    else:
        digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        integer_str = ""
        while integer_part > 0:
            integer_str += digits[integer_part % r]
            integer_part //= r
    integer_str = integer_str[::-1]

    # Перевод дробной части (ограничиваем до 10 знаков после запятой)
    fractional_str = ""
    if fractional_part > 0:
        fractional_str = "."
        precision = 10  # Максимальное количество знаков после запятой
        for _ in range(precision):
            fractional_part *= r
            digit = int(fractional_part)
            fractional_str += digits[digit]
            fractional_part -= digit
            if fractional_part == 0:
                break

    return sign + integer_str + fractional_str


def base_r_to_decimal(s, r):
    # Обработка знака
    sign = -1 if s[0] == '-' else 1
    if s.startswith('-') or s.startswith('+'):
        s = s[1:]

    # Разделение на целую и дробную части
    parts = s.split('.', 1)
    integer_part = parts[0] if len(parts) > 0 else "0"
    fractional_part = parts[1] if len(parts) > 1 else ""

    # Проверка корректности символов
    valid_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[:r]
    for char in integer_part + fractional_part:
        if char not in valid_chars:
            raise ValueError(f"Недопустимый символ '{char}' для основания {r}")

    # Перевод целой части
    decimal_integer = 0
    for i, char in (zip(range(len(integer_part)-1, 0, -1), integer_part)):
        decimal_integer += valid_chars.index(char) * r ** i

    # Перевод дробной части
    decimal_fractional = 0.0
    power = 1
    for char in fractional_part:
        power *= r
        decimal_fractional += valid_chars.index(char) / power

    return sign * (decimal_integer + decimal_fractional)


# Пример использования
if __name__ == "__main__":
    print("=== Перевод из десятичной в r-ичную ===")
    num = float(input("Введите вещественное число в десятичной системе: "))
    r = int(input("Введите основание r (2-36): "))
    result = decimal_to_base_r(num, r)
    print(f"{num} в {r}-ичной системе: {result}")

    # print("\n=== Перевод из r-ичной в десятичную ===")
    # s = input("Введите число в r-ичной системе: ")
    # r_back = int(input("Введите основание r (2-36): "))
    # result_back = base_r_to_decimal(s, r_back)
    # print(f"{s} в {r_back}-ичной системе = {result_back} в десятичной")