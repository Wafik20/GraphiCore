/*
 * Created by Wafik Tawfik on Jan 20 2023
 *
 * file contains the function definitions and structs and macros for the graphics library.
 *
 * */

#ifndef GRAPHICSLIBRARY_LIBRARY_H
#define GRAPHICSLIBRARY_LIBRARY_H

#include <termios.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

// Frame buffer path
#define FB_PATH ((char*)"/dev/fb0")
// Define PI in double precision
#define PI 3.14159265358979323846


// Struct to store the RGB values of a color
typedef struct {
    unsigned int blue: 5;
    unsigned int green: 6;
    unsigned int red: 5;
} color_t;

typedef struct {
    void *buffer;
    int width;
    int height;
    int line_len;
    int bytes_per_pixel;
    int frame_size;
    int file_descriptor;
    struct termios old_terminal_state;
} frame_t;

/*
 * Function:  init_graphics
 * --------------------
 * Initializes the graphics library by opening a file descriptor to the frame buffer and mapping it to user memory.
 * Saves the current terminal settings and changes the terminal settings to disable ICANON and ECHO flags.
 * Initializes the frame object.
 *
 *  returns: void
 */
void init_graphics();

/*
 * Function:  exit_graphics
 * --------------------
 * Exits the graphics library by restoring the terminal settings and unmapping the frame buffer from user memory.
 *
 *  returns: void
 */
void exit_graphics();

/*
 * Function:  get_key
 * --------------------
 * Returns the key pressed by the user.
 *
 *  returns: char
 *
 */
char get_key();

/*
 * Function:  sleep_ms
 * --------------------
 * Sleeps for the specified number of milliseconds.
 *
 *  returns: on success, returns char read. On failure, returns -1.
 *
 */
void sleep_ms(int ms);

/*
 * Function:  draw_pixel
 * --------------------
 * Draws a pixel at the specified location with the specified color.
 * The location is specified by the x and y coordinates.
 * The color is specified by the color_t struct.
 *
 * x: x coordinate of the pixel
 * y: y coordinate of the pixel
 * color: color of the pixel in RGB format
 *
 * returns: void
 */
void draw_pixel(int x, int y, color_t color);

/*
 * Function:  draw_rect
 * --------------------
 * Draws a rectangle at the specified location with the specified color.
 * The location is specified by the x and y coordinates.
 * The color is specified by the color_t struct.
 *
 * x1: x coordinate of the top left corner of the rectangle
 * y1: y coordinate of the top left corner of the rectangle
 * height: height of the rectangle
 * width: width of the rectangle
 * color: color of the rectangle in RGB format
 *
 * returns: void
 */
void draw_rect(int x1, int y1, int height, int width, color_t color);

/*
 * Function:  draw_char
 * --------------------
 * Draws a char at the specified location with the specified color.
 * The location is specified by the x and y coordinates.
 * The color is specified by the color_t struct.
 *
 * x: x coordinate of the starting point of the char
 * y: y coordinate of the starting point of the char
 * c: char to be drawn
 * color: color of the char in RGB format
 *
 *
 * returns: void
 */
void draw_char(int x, int y, char c, color_t color);

/*
 * Function:  draw_text
 * --------------------
 * Draws text starting at the specified location with the specified color.
 * The location is specified by the x and y coordinates.
 * The color is specified by the color_t struct.
 *
 * x: x coordinate of the starting point of the string
 * y: y coordinate of the starting point of the string
 * str: string to be drawn
 * color: color of the char in RGB format
 *
 *
 * returns: void
 */
void draw_text(int x, int y, char *string, color_t color);

/*
 * Function: rgb
 * --------------------
 * Converts the RGB values to a color_t struct.
 *
 * r: red value
 * g: green value
 * b: blue value
 *
 * returns: color_t struct
 */
color_t rgb(int r, int g, int b);

/*
 * Function:  draw_circle
 * --------------------
 * Draws a circle at the specified location with the specified color using the mid-point algorithm.
 *
 * x: x coordinate of the center of the circle
 * y: y coordinate of the center of the circle
 * radius: radius of the circle
 *
 * returns: void
 *
 * Reference: https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
 */
void draw_circle(int x, int y, int r, color_t color);

/*
 * Function: draw_filled_circle
 * --------------------
 *
 * Draws a filled circle at the specified location with the specified color using the mid-point algorithm.
 *
 * x: x coordinate of the center of the circle
 * y: y coordinate of the center of the circle
 * radius: radius of the circle
 * color: color of the circle in RGB format
 *
 * returns: void
 *
 */
void draw_filled_circle(int x_center, int y_center, int r, color_t color);

/*
 * Function: clear_screen
 * --------------------
 * Clears the screen by drawing a black rectangle over the entire screen.
 * The rectangle is drawn using the draw_rect function.
 *
 * returns: void
 */
void clear_screen();


#endif //GRAPHICSLIBRARY_LIBRARY_H
