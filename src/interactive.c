#include <ncurses.h>

#define WIDTH 80
#define HEIGHT 25
#define WIN_SCORE 21

int ball_x;
int ball_y;
int ball_dx;
int ball_dy;

int left_y;
int right_y;

int left_score;
int right_score;

char command;

void draw(void) {
  int y;
  int x;

  clear();

  mvprintw(0, 0, "Player 1: %d                              Player 2: %d",
           left_score, right_score);

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      if (y == 0 || y == HEIGHT - 1) {
        mvaddch(y + 1, x, '-');
      } else if (x == 0 || x == WIDTH - 1) {
        mvaddch(y + 1, x, '|');
      } else if (x == ball_x && y == ball_y) {
        mvaddch(y + 1, x, 'O');
      } else if (x == WIDTH / 2 && y % 2 == 0) {
        mvaddch(y + 1, x, '|');
      } else if (x == 2 && y >= left_y - 1 && y <= left_y + 1) {
        mvaddch(y + 1, x, '|');
      } else if (x == WIDTH - 3 && y >= right_y - 1 &&
                 y <= right_y + 1) {
        mvaddch(y + 1, x, '|');
      }
    }
  }

  refresh();
}

void move_rackets(void) {
  if ((command == 'A' || command == 'a') && left_y > 2) {
    left_y--;
  }

  if ((command == 'Z' || command == 'z') && left_y < HEIGHT - 3) {
    left_y++;
  }

  if ((command == 'K' || command == 'k') && right_y > 2) {
    right_y--;
  }

  if ((command == 'M' || command == 'm') && right_y < HEIGHT - 3) {
    right_y++;
  }
}

void move_ball(void) {
  ball_x += ball_dx;
  ball_y += ball_dy;

  if (ball_y <= 1) {
    ball_y = 1;
    ball_dy = 1;
  }

  if (ball_y >= HEIGHT - 2) {
    ball_y = HEIGHT - 2;
    ball_dy = -1;
  }

  if (ball_x == 2 && ball_dx < 0 &&
      ball_y >= left_y - 1 && ball_y <= left_y + 1) {
    ball_dx = 1;
  }

  if (ball_x == WIDTH - 3 && ball_dx > 0 &&
      ball_y >= right_y - 1 && ball_y <= right_y + 1) {
    ball_dx = -1;
  }
}

void check_goal(void) {
  if (ball_x <= 0) {
    right_score++;
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = 1;
  }

  if (ball_x >= WIDTH - 1) {
    left_score++;
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    ball_dx = -1;
  }
}

int main(void) {
  int input;

  ball_x = WIDTH / 2;
  ball_y = HEIGHT / 2;
  ball_dx = 1;
  ball_dy = 1;

  left_y = HEIGHT / 2;
  right_y = HEIGHT / 2;

  left_score = 0;
  right_score = 0;

  command = ' ';

  initscr();
  cbreak();
  noecho();
  curs_set(0);
  timeout(50);

  while (left_score < WIN_SCORE && right_score < WIN_SCORE) {
    input = getch();

    if (input != ERR) {
      command = (char)input;
    } else {
      command = ' ';
    }

    move_rackets();
    move_ball();
    check_goal();
    draw();
  }

  if (left_score == WIN_SCORE) {
    mvprintw(HEIGHT + 2, 0, "Player 1 wins!");
  } else {
    mvprintw(HEIGHT + 2, 0, "Player 2 wins!");
  }

  refresh();
  getch();
  endwin();

  return 0;
}
