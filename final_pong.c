#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 21

/* Координаты и направление движения мяча. */
int ball_x;
int ball_y;
int ball_dx;
int ball_dy;

/* Вертикальные координаты центров ракеток. */
int left_racket_y;
int right_racket_y;

/* Счет и общее состояние игры. */
int left_score;
int right_score;
char command;
int goal;
int winner;

void draw_field(void);
char read_command(void);
void move_left_racket(void);
void move_right_racket(void);
void move_ball(void);
void check_collision(void);
void check_goal(void);
void check_winner(void);

void print_score(int left, int right) {
    printf("Player 1: %d                                      Player 2: %d\n",
           left, right);
}

void print_cell(int row, int col) {
    int half_racket = RACKET_SIZE / 2;

    if (row == 0 || row == HEIGHT - 1) {
        printf("-");
    } else if (col == 0 || col == WIDTH - 1) {
        printf("|");
    } else if (col == WIDTH / 2 && row % 2 == 0) {
        printf("|");
    } else if (col == 2 &&
               row >= left_racket_y - half_racket &&
               row <= left_racket_y + half_racket) {
        printf("|");
    } else if (col == WIDTH - 3 &&
               row >= right_racket_y - half_racket &&
               row <= right_racket_y + half_racket) {
        printf("|");
    } else if (col == ball_x && row == ball_y) {
        printf("O");
    } else {
        printf(" ");
    }
}

void draw_field(void) {
    int row;
    int col;

    printf("\033[H\033[J");
    print_score(left_score, right_score);

    for (row = 0; row < HEIGHT; row++) {
        for (col = 0; col < WIDTH; col++) {
            print_cell(row, col);
        }
        printf("\n");
    }
}

char read_command(void) {
    int input;

    while (1) {
        input = getchar();

        if (input == 'A' || input == 'a' ||
            input == 'Z' || input == 'z' ||
            input == 'K' || input == 'k' ||
            input == 'M' || input == 'm' ||
            input == ' ') {
            return (char)input;
        }
    }
}

void move_left_racket(void) {
    if ((command == 'A' || command == 'a') && left_racket_y > 2) {
        left_racket_y--;
    } else if ((command == 'Z' || command == 'z') &&
               left_racket_y < HEIGHT - 3) {
        left_racket_y++;
    }
}

void move_right_racket(void) {
    if ((command == 'K' || command == 'k') && right_racket_y > 2) {
        right_racket_y--;
    } else if ((command == 'M' || command == 'm') &&
               right_racket_y < HEIGHT - 3) {
        right_racket_y++;
    }
}

void move_ball(void) {
    ball_x += ball_dx;
    ball_y += ball_dy;
}

void check_collision(void) {
    if (ball_y <= 1) {
        ball_y = 1;
        ball_dy = 1;
    } else if (ball_y >= HEIGHT - 2) {
        ball_y = HEIGHT - 2;
        ball_dy = -1;
    }

    if (ball_x == 2 && ball_dx < 0 &&
        ball_y >= left_racket_y - RACKET_SIZE / 2 &&
        ball_y <= left_racket_y + RACKET_SIZE / 2) {
        ball_dx = 1;
    } else if (ball_x == WIDTH - 3 && ball_dx > 0 &&
               ball_y >= right_racket_y - RACKET_SIZE / 2 &&
               ball_y <= right_racket_y + RACKET_SIZE / 2) {
        ball_dx = -1;
    }
}

void check_goal(void) {
    goal = 0;

    if (ball_x <= 0) {
        right_score++;
        goal = 1;
    } else if (ball_x >= WIDTH - 1) {
        left_score++;
        goal = 2;
    }

    if (goal != 0) {
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dy = -ball_dy;
        ball_dx = (goal == 1) ? 1 : -1;
    }
}

void check_winner(void) {
    if (left_score >= WIN_SCORE) {
        winner = 1;
    } else if (right_score >= WIN_SCORE) {
        winner = 2;
    } else {
        winner = 0;
    }
}

int main(void) {
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = 1;
    ball_dy = 1;

    left_racket_y = HEIGHT / 2;
    right_racket_y = HEIGHT / 2;

    left_score = 0;
    right_score = 0;
    command = ' ';
    goal = 0;
    winner = 0;

    while (winner == 0) {
        draw_field();
        command = read_command();
        move_left_racket();
        move_right_racket();
        move_ball();
        check_collision();
        check_goal();
        check_winner();
    }

    draw_field();

    if (winner == 1) {
        printf("Left player wins!\n");
    } else {
        printf("Right player wins!\n");
    }

    return 0;
}
