#include <windows.h> // подключение библиотеки aeyrwbb MultiByteToWideChar
#include <stdio.h>
#include <locale.h> //  подкючение библиотеки для функции setlocale "понимание керилицы"
#include <wchar.h> // библиотека для "широких символов"

int main() {
    // Настройка для работы с русским языком
    setlocale(LC_ALL, "Russian");

    // Открываем файл со списком имен
    FILE *file = fopen("list.txt", "r"); // создание переменной file структуры FILE и загрузка данных из файла  list.txt
    if (!file) {
        printf("Ошибка: Создай файл list.txt и положи его рядом с программой!\n");
        system("pause");
        return 1;
    }

    char line[512];// создание массива  для обычной строки
    wchar_t w_line[512];// массив для "широкой строки"

    printf("Начинаю создание папок из файла list.txt...\n\n");

    while (fgets(line, sizeof(line), file)) {  // считывание строки из file пока есть не считанные строки 
        // Убираем лишние пробелы и символы переноса строки
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) < 2) continue; // Пропускаем пустые строки

        // Конвертируем строку в формат Unicode для Windows
        MultiByteToWideChar(CP_UTF8, 0, line, -1, w_line, 512);// перевод текста из CP_UTF8 в Unicode

        // Создаем папку
        if (_wmkdir(w_line) == 0) {
            wprintf(L"[OK] Создана: %s\n", w_line);
        } else {
            wprintf(L"[!] Пропущена (уже есть): %s\n", w_line);
        }
    }

    fclose(file);
    printf("\nГотово! Все папки из списка обработаны.\n");
    system("pause");

    return 0;
}