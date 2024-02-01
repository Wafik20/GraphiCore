/*
 * Created by Wafik Tawfik on Jan 20 2023
 *
 * file contains function implementations.
 *
 * */
#include "library.h"
#include "iso_font.h"

static frame_t frame;

void init_graphics() {
    // Open the framebuffer device file
    int file_descriptor = open(FB_PATH, O_RDWR);

    //TESTING:
    //    if (file_descriptor == -1) {
    //        perror("Error opening framebuffer device\n");
    //    }
    // for testing purposes:
    //    else {
    //        printf("Frame buffer opened\nFile descriptor with value %d\n", file_descriptor);
    //    }

    // Get variable screen information
    struct fb_var_screeninfo v_info;
    struct fb_fix_screeninfo f_info;

    ioctl(file_descriptor, FBIOGET_VSCREENINFO, &v_info);

    //TESTING:
    //    if (ioctl(file_descriptor, FBIOGET_VSCREENINFO, &v_info)) {
    //        perror("Error reading variable screen information\n");
    //        close(file_descriptor);
    //    }

    ioctl(file_descriptor, FBIOGET_FSCREENINFO, &f_info);

    //TESTING:
    //    if (ioctl(file_descriptor, FBIOGET_FSCREENINFO, &f_info)) {
    //        perror("Error reading fixed screen information\n");
    //        close(file_descriptor);
    //    }

    // Calculate the size of the screen in bytes
    int screensize = v_info.yres_virtual * f_info.line_length;

    // TESTING:
    //printf("Screen dimensions are %d x %d x %d\n", v_info.yres_virtual, v_info.xres_virtual, v_info.bits_per_pixel);

    // Map framebuffer to user memory
    color_t *mem_space = mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);

    //TESTING:
    //    if (mem_space == MAP_FAILED) {
    //        perror("Error mapping framebuffer device to memory\n");
    //        close(file_descriptor);
    //    }
    //    else {
    //        printf("Frame buffer allocated at %#08x\n", &mem_space);
    //    }

    // Get the terminal changes settings before changing the ICANON, ECHO flags
    struct termios old_terminal_state, new_terminal_state;

    // for testing purposes:
    //errno = 0;



    // Save the current state of the terminal before changing its state
    ioctl(STDIN_FILENO, TCGETS, &old_terminal_state);


    //TESTING
    //    if (ioctl(STDIN_FILENO, TCGETS, &old_terminal_state) == -1) {
    //
    //
    //        int errsv = errno;
    //        fprintf(stderr, "err no#: %d\n", errsv);
    //
    //        perror("Error saving terminal state");
    //        close(file_descriptor);
    //    }

    //    for testing purposes:
    //    else {
    //        printf("Saved old terminal changes\n");
    //    }

    // Set the terminal changes
    new_terminal_state.c_lflag &= ~(ICANON | ECHO);

    // Apply changes
    ioctl(STDIN_FILENO, TCSETS, &new_terminal_state);

    //TESTING:
    //    if (ioctl(STDIN_FILENO, TCSETS, &new_terminal_state) == -1) {
    //        perror("Error applying terminal changes");
    //        close(file_descriptor);
    //    }

    //  for testing purposes:
    //    else {
    //        printf("Altered flags ICANON, ECHO\n");
    //    }

    // clear the screen
    clear_screen();

    // Create the frame object
    frame.buffer = mem_space;
    frame.width = v_info.xres;
    frame.height = v_info.yres;
    frame.line_len = f_info.line_length;
    frame.bytes_per_pixel = v_info.bits_per_pixel / 8;
    frame.frame_size = screensize;
    frame.file_descriptor = file_descriptor;
    frame.old_terminal_state = old_terminal_state;


    // FOR TESTING PURPOSES:
    // printf("Successfully initialized frame buffer\n");
}


void exit_graphics() {
    // Free the mem space allocated and close the frame buffers
    munmap(frame.buffer, frame.frame_size);

    // TESTING:
    // printf("Attempting to unmap memory at address: %p with size: %d\n", frame.buffer, frame.frame_size);
    //    errno = 0;
    //    if (munmap(frame.buffer, frame.frame_size) == -1) {
    //        fprintf(stderr, "errno: %d", errno);
    //        perror("Error deallocating framebuffer");
    //        close(frame.file_descriptor);
    //        exit(3);
    //    } else {
    //        printf("Successfully deallocated frame buffer\n");
    //    }

    close(frame.file_descriptor);

    // TESTING:
    //    if (close(frame.file_descriptor) == -1) {
    //        printf("Failed to close file");
    //    }
    //    else {
    //        printf("Successfully closed file\n");
    //    }

    // Restore old terminal changes
    ioctl(STDIN_FILENO, TCSETS, &frame.old_terminal_state);

    //TESTING:
    //    if (ioctl(STDIN_FILENO, TCSETS, &frame.old_terminal_state) == -1) {
    //        perror("Failed to restore original terminal settings");
    //        exit(1); }
    //    else {
    //        printf("Restored old terminal changes\n");
    //    }
    //    printf("Exiting!!\n");
}

char get_key() {
    char c;
    fd_set read_fds;

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    // Using select, check if there is any key presses
    int key_found = select(1, &read_fds, NULL, NULL, NULL);

    // If you find any, read from stdin
    if (key_found == 1) {
        if (read(STDIN_FILENO, &c, 1) == -1) {
            return '\0'; /* on failure, return null terminator */
        } else {
            return c;
        }
    } else {
        return '\0'; /* on failure, return null terminator */
    }
}

void sleep_ms(int ms) {
    struct timespec sleep_time;
    sleep_time.tv_sec = 0;
    sleep_time.tv_nsec = ms * 1000000;
    nanosleep(&sleep_time, NULL);
}

void draw_pixel(int x, int y, color_t color) {
    // Check if the pixel is within the frame
    if (x < 0 || x > frame.width || y < 0 || y > frame.height) {
        return;
    }

    /*
     * find a pointer to the start of the appropriate row by calculating y * line_len
     * find the start of the appropriate pixel in the chosen row by scaling x by the number of bytes per pixel
     * -> (x * bytes_per_pixel)
     */
    int offset = (y * frame.line_len) + (x * frame.bytes_per_pixel);

    // Set the pixel
    *((color_t *) (frame.buffer +
                   offset)) = color; /* place to put the pixel is buffer[offset] but type cast to *color_t */
}


void draw_rect(int x1, int y1, int height, int width, color_t color) {

    // Check if the rectangle is within the frame
    if (x1 + width > frame.width || y1 + height > frame.height) {
        return;
    }


    // Set the pixel
    int i, j;
    for (i = x1; i < x1 + width; i++) {
        for (j = y1; j < y1 + height; j++) {
            draw_pixel(i, j, color);
        }
    }
}

void draw_char(int x, int y, char c, color_t color) {

    // Check if the character is within the frame
    int char_max_x = x + 8; /* char_max_x is defined is max reach of the char in the x-direction + 1 */
    int char_max_y = y + 16; /* char_max_y is defined is max reach of the char in the y-direction + 1 */

    if (char_max_x > frame.width || char_max_y > frame.height) {
        return;
    }

    // Set the pixel
    int i, j;
    for (i = x; i < char_max_x; i++) {
        for (j = y; j < char_max_y; j++) {
            int char_index = c * 16 + (j - y);
            if (iso_font[char_index] &
                (1 << (i - x))) { /* take only bit i - x to check whether to draw pixel or not at position i, j */
                draw_pixel(i, j, color);
            }
        }
    }
}

void draw_text(int x, int y, char *string, color_t color) {
    // Initialize starting char, and x, y positions
    int i = 0;
    int x_start = x;

    // Iterate until encountering null terminator
    while (string[i] != '\0') {
        draw_char(x_start, y, string[i], color);

        // Update char, and x starting position
        i++;
        x_start = x_start + 8;
    }
}

/* Wanted to use Macros to define all colors in terms of the struct without the need of a function.
 * However, they miss up the bit pattern for some reason. */
color_t rgb(int r, int g, int b) {
    color_t color;
    color.red = r;
    color.green = g;
    color.blue = b;
    return color;
}

// Reference: https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
void draw_circle(int x_center, int y_center, int r, color_t color) {
    int x = r, y = 0;

    draw_pixel(x + x_center, y_center, color);

    if (r > 0) {
        draw_pixel(x + x_center, -y + y_center, color);
        draw_pixel(y + x_center, x + y_center, color);
        draw_pixel(-y + x_center, x + y_center, color);
    }

    int P = 1 - r;
    while (x > y) {
        y++;
        if (P <= 0) {
            P = P + 2 * y + 1;
        } else {
            x--;
            P = P + 2 * y - 2 * x + 1;
        }
        if (x < y) {
            break;
        }

        draw_pixel(x + x_center, y + y_center, color);
        draw_pixel(-x + x_center, y + y_center, color);
        draw_pixel(x + x_center, -y + y_center, color);
        draw_pixel(-x + x_center, -y + y_center, color);

        if (x != y) {
            draw_pixel(y + x_center, x + y_center, color);
            draw_pixel(-y + x_center, x + y_center, color);
            draw_pixel(y + x_center, -x + y_center, color);
            draw_pixel(-y + x_center, -x + y_center, color);
        }
    }
}

void clear_screen() {
    // clear the screen
    write(1, "\033[2J", 5);
}

void draw_filled_circle(int x_center, int y_center, int r, color_t color) {
    draw_circle(x_center, y_center, r, color);
    int i, j;
    for (i = -r; i <= r; i++) {
        for (j = -r; j <= r; j++) {
            if (i * i + j * j <= r * r) {
                draw_pixel(x_center + j, y_center + i, color);
            }
        }
    }
}


