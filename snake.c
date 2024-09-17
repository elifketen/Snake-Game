#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 5, y = 5;  // Snake head position
    int fx = 2, fy = 2;  // Food position
    int score = 0;
    char move;
    int tail_x[50] = {0}, tail_y[50] = {0};  // Snake tail
    int tail_length = 0;

    // Initialize random seed without time.h
    srand(1); // Using a fixed seed

    while (1) {
        // Clear screen (print newlines)
        int clear_lines = 0;
        while (clear_lines < 30) {
            printf("\n");
            clear_lines++;
        }

        // Draw map with a single frame outside
        int i_map = 0;
        while (i_map < 12) { // Including borders
            int j_map = 0;
            while (j_map < 12) {
                // Draw borders
                if (i_map == 0 || i_map == 11) {
                    printf("#");
                } else if (j_map == 0 || j_map == 11) {
                    printf("#");
                } else {
                    // Adjust indices for the game area (excluding borders)
                    int i = i_map - 1;
                    int j = j_map - 1;

                    if (i == y && j == x) {
                        printf("O"); // Snake head
                    } else if (i == fy && j == fx) {
                        printf("F"); // Food
                    } else {
                        // Check if this position is part of the tail
                        int is_tail = 0;
                        int k = 0;
                        while (k < tail_length) {
                            if (i == tail_y[k] && j == tail_x[k]) {
                                printf("o"); // Snake tail segment
                                is_tail = 1;
                                break;
                            }
                            k++;
                        }
                        if (!is_tail) {
                            printf(" "); // Empty space
                        }
                    }
                }
                j_map++;
            }
            printf("\n");
            i_map++;
        }

        // Get move
        printf("Score: %d\nMove (w/a/s/d): ", score);
        scanf(" %c", &move);

        // Update tail positions
        int i_tail = tail_length;
        while (i_tail > 0) {
            tail_x[i_tail] = tail_x[i_tail - 1];
            tail_y[i_tail] = tail_y[i_tail - 1];
            i_tail--;
        }
        tail_x[0] = x;
        tail_y[0] = y;

        // Move snake head
        if (move == 'w') y--;
        else if (move == 's') y++;
        else if (move == 'a') x--;
        else if (move == 'd') x++;

        // Check boundaries (game area is 0 to 9)
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            printf("Game Over! You hit the wall.\n");
            break;
        }

        // Check self-collision
        int i_collision = 0;
        int collision = 0;
        while (i_collision < tail_length) {
            if (x == tail_x[i_collision] && y == tail_y[i_collision]) {
                printf("Game Over! You hit yourself.\n");
                collision = 1;
                break;
            }
            i_collision++;
        }
        if (collision) break;

        // Check if food is eaten
        if (x == fx && y == fy) {
            score++;
            tail_length++;
            // Generate new food position within game area (0 to 9)
            fx = rand() % 10;
            fy = rand() % 10;
        }
    }

    return 0;
}
