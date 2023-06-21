#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 319
#define HEIGHT 78

char state[] = " #";
bool surface[HEIGHT][WIDTH];
bool surface_diff[HEIGHT][WIDTH];

bool random_bool() {
  return rand() & 1;
}

void random_surface(void) {
  size_t w = WIDTH;
  size_t h = HEIGHT;
  for(size_t i = 0; i < h; ++i) {
    for(size_t j = 0; j < w; ++j) {
      surface[i][j] = random_bool();
    }
  }
}

void compute_surface(void) {
  for(int h = 0; h < HEIGHT; ++h) {
    for(int w = 0; w < WIDTH; ++w) {
      int cells_alive = 0;
      for (int h1 = h - 1; h1 <= h + 1; h1++)
			  for (int w1 = w - 1; w1 <= w + 1; w1++)
				  if (surface[(h1 + HEIGHT) % HEIGHT][(w1 + WIDTH) % WIDTH])
					  cells_alive++;

      if (surface[h][w]) {
        cells_alive--;
      }

      surface_diff[h][w] = (cells_alive == 3 || (cells_alive == 2 && surface[h][w]));
    }
  }
}

void apply_surface_diff(void)
{
  memcpy(surface, surface_diff, HEIGHT*WIDTH);
}

void display_surface(bool surface[HEIGHT][WIDTH]) {
  system("clear");
  printf("\034[1;31m");
  for (size_t y = 0; y < HEIGHT; ++y) {
        for (size_t x = 0; x < WIDTH; ++x) {
            char c = state[(int)(surface[y][x])];
            printf("\033[1;31m");
            fputc(c, stdout);
        }
    fputc('\n', stdout);
  }
  printf("\034[0m");
}

int main(void) {
  srand(time(0));
  random_surface();
  for(;;) {
    display_surface(surface);
    compute_surface();
    apply_surface_diff();
  }

  return 0;
}
