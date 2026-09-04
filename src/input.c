#include <stdio.h>  /* Подключаем getchar(), printf() и значение EOF. */

#define HEIGHT 25  /* Полная высота игрового поля вместе с границами. */

/* Эти обычные переменные создаются в pong.c и используются здесь. */
extern char command;         /* Последняя корректная команда игрока. */
extern int left_racket_y;    /* Координата центра левой ракетки. */
extern int right_racket_y;   /* Координата центра правой ракетки. */

char read_command(void)  /* Читает ввод, пока не получит разрешённую команду. */
{
    char current_command;  /* Здесь будет храниться проверенная команда. */
    int input;             /* Тип int нужен, чтобы можно было распознать EOF. */

    current_command = '\0';  /* Нулевой символ означает отсутствие команды. */
    while (current_command == '\0')  /* Повторяем ввод до корректной команды. */
    {
        printf("A/Z - left, K/M - right, SPACE - skip: ");  /* Печатаем подсказку. */
        input = getchar();  /* Читаем первый символ введённой строки. */

        if (input == 'A' || input == 'a')  /* A перемещает левую ракетку вверх. */
        {
            current_command = 'A';  /* Приводим команду к верхнему регистру. */
        }
        else if (input == 'Z' || input == 'z')  /* Z двигает левую ракетку вниз. */
        {
            current_command = 'Z';  /* Приводим команду к верхнему регистру. */
        }
        else if (input == 'K' || input == 'k')  /* K двигает правую ракетку вверх. */
        {
            current_command = 'K';  /* Приводим команду к верхнему регистру. */
        }
        else if (input == 'M' || input == 'm')  /* M двигает правую ракетку вниз. */
        {
            current_command = 'M';  /* Приводим команду к верхнему регистру. */
        }
        else if (input == ' ')  /* Пробел означает ход без движения ракеток. */
        {
            current_command = ' ';  /* Сохраняем пробел как корректную команду. */
        }

        while (input != '\n' && input != EOF)  /* Удаляем остаток введённой строки. */
        {
            input = getchar();  /* Читаем символы до Enter или конца ввода. */
        }
    }

    return current_command;  /* Передаём проверенную команду функции main(). */
}

void move_left_racket(void)  /* Изменяет положение только левой ракетки. */
{
    if (command == 'A' && left_racket_y > 2)  /* Сверху остаётся место для ракетки. */
    {
        left_racket_y = left_racket_y - 1;  /* Поднимаем ракетку на одну строку. */
    }
    else if (command == 'Z' && left_racket_y < HEIGHT - 3)  /* Снизу есть место. */
    {
        left_racket_y = left_racket_y + 1;  /* Опускаем ракетку на одну строку. */
    }
}

void move_right_racket(void)  /* Изменяет положение только правой ракетки. */
{
    if (command == 'K' && right_racket_y > 2)  /* Сверху остаётся место для ракетки. */
    {
        right_racket_y = right_racket_y - 1;  /* Поднимаем ракетку на одну строку. */
    }
    else if (command == 'M' && right_racket_y < HEIGHT - 3)  /* Снизу есть место. */
    {
        right_racket_y = right_racket_y + 1;  /* Опускаем ракетку на одну строку. */
    }
}
