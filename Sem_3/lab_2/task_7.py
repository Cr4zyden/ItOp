def ieee754_hex_to_float():
    print("=== Преобразование hex → float по IEEE 754 (вручную) ===")
    print("Введите шестнадцатеричный код:")
    print("  • 8 символов — для 32-битного числа (float)")
    print("  • 16 символов — для 64-битного числа (double)")
    
    # Ввод от пользователя
    hex_str = input("\nВвод: ").strip().lower()

    # Удаляем префикс 0x, если есть
    if hex_str.startswith('0x'):
        hex_str = hex_str[2:]

    # Проверка длины
    if len(hex_str) not in [8, 16]:
        print(f"❌ Ошибка: ожидалось 8 или 16 шестнадцатеричных символов, получено {len(hex_str)}.")
        return

    # Определяем формат
    if len(hex_str) == 8:
        n_bits = 32
        exp_bits_count = 8
        mantissa_bits_count = 23
        bias = 127
        fmt_name = "IEEE 754 single precision (32-bit)"
    else:  # len == 16
        n_bits = 64
        exp_bits_count = 11
        mantissa_bits_count = 52
        bias = 1023
        fmt_name = "IEEE 754 double precision (64-bit)"

    print(f"\n✅ Формат: {fmt_name}")
    print(f"Введённый hex: {hex_str.upper()}")

    # Проверка: все символы — допустимые hex-цифры
    if not all(c in '0123456789abcdef' for c in hex_str):
        print("Ошибка: некорректные символы в шестнадцатеричном коде.")
        return

    # Переводим hex → int → binary (с ведущими нулями)
    try:
        num = int(hex_str, 16)
    except Exception:
        print("Ошибка при преобразовании hex в число.")
        return

    binary = bin(num)[2:].zfill(n_bits)
    print(f"Двоичное представление: {binary}")

    # Разбиваем на поля
    sign_bit = binary[0]
    exponent_bits = binary[1:1+exp_bits_count]
    mantissa_bits = binary[1+exp_bits_count:]

    print(f"S (знак): {sign_bit}")
    print(f"E (экспонента): {exponent_bits}")
    print(f"M (мантисса): {mantissa_bits}")

    # Знак
    sign = -1 if sign_bit == '1' else 1
    print(f"Знак: {'отрицательное' if sign == -1 else 'положительное'}")

    # Экспонента
    exponent_decimal = int(exponent_bits, 2)
    real_exponent = exponent_decimal - bias
    print(f"Смещённая экспонента (E): {exponent_decimal}")
    print(f"Реальная экспонента: {real_exponent} ({exponent_decimal} - {bias})")

    # Мантисса: 1.M (неявная единица)
    mantissa_binary = "1." + mantissa_bits
    print(f"Полная мантисса (двоичная): {mantissa_binary}")

    # Перевод дробной части мантиссы в десятичную систему
    integer_part = int(mantissa_binary.split('.')[0], 2)  # всегда 1
    fractional_str = mantissa_binary.split('.')[1]

    fractional_value = 0.0
    for i, bit in enumerate(fractional_str):
        if bit == '1':
            fractional_value += 2 ** -(i + 1)

    mantissa_decimal = integer_part + fractional_value
    print(f"Мантисса (десятичная): {mantissa_decimal:.10f}")

    # Итоговое значение
    result = sign * mantissa_decimal * (2 ** real_exponent)
    print(f"\n Результат: {sign} × {mantissa_decimal} × 2^{real_exponent} = {result}")

    # Форматированный вывод
    print(f"\n ИТОГО: {result}")


# === Запуск программы ===
if __name__ == "__main__":
    while True:
        ieee754_hex_to_float()
        
        print("\n" + "-"*50)
        again = input("Хотите ввести другое число? (да/нет): ").strip().lower()
        if again not in ['да', 'yes', 'y', 'д']:
            print("Завершение работы.")
            break
        print("\n")