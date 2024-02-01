/*
 * Created by Wafik Tawfik on Jan 20 2023
 *
 * file contains function implementations.
 *
 * */
#include "library.h"

// Macros to define screen dimensions and letter sizes
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define LETTER_WIDTH 8
#define LETTER_HEIGHT 16

// Macro to convert RGB values to a color_t
#define PINK rgb(31, 31, 31)
#define WHITE rgb(31, 63, 31)
#define BLACK rgb(0, 0, 0)
#define RED rgb(31, 0, 0)
#define GREEN rgb(0, 63, 0)
#define BLUE rgb(0, 0, 31)
#define MAGENTA rgb(31, 0, 31)
#define CYAN rgb(0, 63, 31)
#define YELLOW rgb(31, 63, 0)

// some restrictions on the size of the shapes and colors
#define MAX_WIDTH 100
#define MIN_WIDTH 25

#define MAX_HEIGHT 100
#define MIN_HEIGHT 25

#define MAX_RADIUS 75
#define MIN_RADIUS 25

#define MAX_RED 32
#define MAX_GREEN 64
#define MAX_BLUE 32

void hello_world_in_rainbow();

void draw_rand_circle();

void draw_rand_filled_circle();

void draw_rand_rect();

void draw_rand_hello_world();

void print_starting_msg();

void print_goodbye_msg();

int main() {
    init_graphics();
    print_starting_msg();
    char current_key = 0;
    while (current_key != 'q') {
        if (current_key == 'h') {
            draw_rand_hello_world();
        } else if (current_key == 'c') {
            //draw_rand_circle();
            draw_rand_filled_circle();
        } else if (current_key == 'r') {
            draw_rand_rect();
        } else if (current_key == 'w') {
            clear_screen();
            print_starting_msg();
        }
        current_key = get_key();
    }
    clear_screen();
    sleep_ms(500);
    print_goodbye_msg();
    exit_graphics();
    return 0;
}

void hello_world_in_rainbow(int x, int y) {
    draw_char(x, y, 'H', RED);
    draw_char(x + LETTER_WIDTH, y, 'e', GREEN);
    draw_char(x + (2 * LETTER_WIDTH), y, 'l', BLUE);
    draw_char(x + (3 * LETTER_WIDTH), y, 'l', MAGENTA);
    draw_char(x + (4 * LETTER_WIDTH), y, 'o', CYAN);
    draw_char(x + (5 * LETTER_WIDTH), y, ' ', YELLOW);
    draw_char(x + (6 * LETTER_WIDTH), y, 'W', RED);
    draw_char(x + (7 * LETTER_WIDTH), y, 'o', GREEN);
    draw_char(x + (8 * LETTER_WIDTH), y, 'r', BLUE);
    draw_char(x + (9 * LETTER_WIDTH), y, 'l', MAGENTA);
    draw_char(x + (10 * LETTER_WIDTH), y, 'd', CYAN);
}

void draw_rand_hello_world() {
    // modulo to avoid drawing offscreen
    // subtracting by the size of the word "Hello World!" width which is the size of the letter * 11
    hello_world_in_rainbow(rand() % (SCREEN_WIDTH - (11 * LETTER_WIDTH)), rand() % SCREEN_HEIGHT);
}

void draw_rand_circle() {
    draw_circle(rand() % (SCREEN_WIDTH - MAX_RADIUS),
                rand() % (SCREEN_HEIGHT - MAX_RADIUS), /* modulo to enforce the restrictions on the sizes */
                (rand() % (MAX_RADIUS - MIN_RADIUS)) + MIN_RADIUS,
                rgb(rand() % MAX_RED, rand() % MAX_GREEN, rand() % MAX_BLUE));

}

void draw_rand_filled_circle() {
    draw_filled_circle(rand() % (SCREEN_WIDTH - MAX_RADIUS),
                       rand() % (SCREEN_HEIGHT - MAX_RADIUS), /* modulo to enforce the restrictions on the sizes */
                       (rand() % (MAX_RADIUS - MIN_RADIUS)) + MIN_RADIUS,
                       rgb(rand() % MAX_RED, rand() % MAX_GREEN, rand() % MAX_BLUE));
}

void print_starting_msg() {
    draw_text(0, 0, "Created by Wafik Tawfik @ Jan 20 2023", PINK);
    draw_text(0, 32, "Press 'h' to draw Hello World!", PINK);
    draw_text(0, 48, "Press 'c' to draw a circle!", PINK);
    draw_text(0, 64, "Press 'r' to draw a rectangle!", PINK);
    draw_text(0, 80, "Press 'w' to clear the screen!", PINK);
    draw_text(0, 96, "Press 'q' to quit!", PINK);
}

void draw_rand_rect() {
    draw_rect(rand() % (SCREEN_WIDTH - MAX_WIDTH),
              rand() % (SCREEN_HEIGHT - MAX_HEIGHT), /* modulo to enforce the restrictions on the sizes */
              (rand() % (MAX_WIDTH - MIN_WIDTH)) + MIN_WIDTH,
              (rand() % (MAX_HEIGHT - MIN_HEIGHT)) + MIN_HEIGHT,
              rgb(rand() % MAX_RED, rand() % MAX_GREEN, rand() % MAX_BLUE));
}

void print_goodbye_msg() {
    draw_text(0, 0, "Goodbye!", PINK);
}