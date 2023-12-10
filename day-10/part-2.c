#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int *x_values;
    int last_index;
} line_x_values;

void add_to_coords(line_x_values *coors, int y, int x) {
    printf("Y: %d X: %d L: %d\n",y, x, coors[y].last_index);
    coors[y].x_values[coors[y].last_index] = x;
    coors[y].last_index++;
}

bool is_a_pipe(line_x_values coors, int x) {
    for (size_t i = 0; i < (size_t)coors.last_index; i++) {
        if (coors.x_values[i] == x) {
            return true;
        }
    }

    return false;
}

int main()
{
    FILE *input_file;

    if ((input_file = fopen("input.txt", "r")) == NULL)
    {
        // error_print("2", "1", "'input.txt' file could not be opened!");
        return 1;
    }

    char current_char = '\0';
    size_t lines = 0;

    while (current_char != EOF)
    {
        if (current_char == '\n')
        {
            lines++;
        }

        current_char = getc(input_file);
    }

    rewind(input_file);

    char *input_lines[lines];

    for (size_t i = 0; i < lines; i++)
    {
        input_lines[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&input_lines[i], &line_buffer_size, input_file);
        input_lines[i][strcspn(input_lines[i], "\r\n")] = 0;
    }

    puts("Searching starting pipe:");

    int current_y = -1;
    int current_x = -1;

    for (size_t i = 0; i < lines; i++) {
        if (current_y != -1) {
            break;
        }

        for (size_t j = 0; j < strlen(input_lines[i]); j++) {
            if (input_lines[i][j] == 'S') {
                current_y = i;
                current_x = j;
                break;
            }
        }
    }

    printf("Starting pipe found at [%d][%d]\n", current_y, current_x);

    puts("Searching contigious pipe:");

    int previous_y = current_y;
    int previous_x = current_x;

    // Find first valid next pipe
    if (current_y > 0 && (input_lines[current_y - 1][current_x] == '|' || input_lines[current_y - 1][current_x] == '7' || input_lines[current_y - 1][current_x] == 'F')) {
        current_y -= 1;
    } else if ((size_t)current_y < lines && (input_lines[current_y + 1][current_x] == '|' || input_lines[current_y + 1][current_x] == 'L' || input_lines[current_y + 1][current_x] == 'J')) {
        current_y += 1;
    } else if ((size_t)current_x < strlen(input_lines[current_y]) && (input_lines[current_y][current_x + 1] == '-' || input_lines[current_y][current_x + 1] == '7' || input_lines[current_y][current_x + 1] == 'J')) {
        current_x += 1;
    } else {
        current_x -= 1;
    }

    printf("Next pipe found at [%d][%d]\n", current_y, current_x);

    line_x_values *pipe_coors = malloc((lines - 1) * sizeof(line_x_values));

    for (size_t i = 0; i < lines; i++) {
        pipe_coors[i].x_values = malloc(300 * sizeof(int));
        pipe_coors[i].last_index = 0;
    }

    add_to_coords(pipe_coors, previous_y, previous_x);
    add_to_coords(pipe_coors, current_y, current_x);

    while (true) {
        char current_pipe_char = input_lines[current_y][current_x];

        if (current_pipe_char == 'S' || current_pipe_char == '.') {
            break;
        }

        int next_y_1 = 0;
        int next_x_1 = 0;

        int next_y_2 = 0;
        int next_x_2 = 0;

        switch (current_pipe_char)
        {
        case '|':
            next_y_1 = current_y + 1;
            next_x_1 = current_x;

            next_y_2 = current_y - 1;
            next_x_2 = current_x;
            break;
        case '-':
            next_y_1 = current_y;
            next_x_1 = current_x + 1;

            next_y_2 = current_y;
            next_x_2 = current_x - 1;
            break;
        case 'L':
            next_y_1 = current_y - 1;
            next_x_1 = current_x;

            next_y_2 = current_y;
            next_x_2 = current_x + 1;
            break;
        case 'J':
            next_y_1 = current_y - 1;
            next_x_1 = current_x;

            next_y_2 = current_y;
            next_x_2 = current_x - 1;
            break;
        case '7':
            next_y_1 = current_y;
            next_x_1 = current_x - 1;

            next_y_2 = current_y + 1;
            next_x_2 = current_x;
            break;
        case 'F':
            next_y_1 = current_y;
            next_x_1 = current_x + 1;

            next_y_2 = current_y + 1;
            next_x_2 = current_x;
            break;
        }

        //printf("NEXT 1: [%d, %d] NEXT 2: [%d, %d]\n", next_y_1, next_x_1, next_y_2, next_x_2);

        if (next_x_1 == previous_x && next_y_1 == previous_y) {
            previous_x = current_x;
            previous_y = current_y;

            current_x = next_x_2;
            current_y = next_y_2;
        } else {
            previous_x = current_x;
            previous_y = current_y;

            current_x = next_x_1;
            current_y = next_y_1;
        }

        //printf("Going to %c, in [%d, %d]\n", input_lines[current_y][current_x], current_y + 1, current_x + 1);
        add_to_coords(pipe_coors, current_y, current_x);
    }

    int num_of_grounds_inside_pipes = 0;

    for (size_t i = 0; i < lines; i++) {
        int x_lowest = pipe_coors[i].x_values[0];

        for (size_t j = 1; j < (size_t)pipe_coors[i].last_index; j++) {
            if (pipe_coors[i].x_values[j] < x_lowest) {
                x_lowest = pipe_coors[i].x_values[j];
            }
        }

        for (size_t j = 0; j < strlen(input_lines[i]); j++) {
            if (is_a_pipe(pipe_coors[i], j)) {
                printf("[%ld, %ld] is a pipe\n", i, j);
                continue;
            }

            printf("Cicle %c in [%ld, %ld]\n", input_lines[i][j], i, j);

            if (j < (size_t)x_lowest) {
                printf("Skipped because %ld < %d\n", j, x_lowest);
                continue;
            }

            int num_of_times_touch_pipes = 0;
            int num_of_halfs = 0;
            for (size_t k = j + 1; k < strlen(input_lines[i]); k++) {
                if (is_a_pipe(pipe_coors[i], k)) {
                    printf("Touch pipe %c in [%ld, %ld]\n", input_lines[i][k], i, k);
                    if (input_lines[i][k] == '-') {
                        continue;
                    }

                    if (input_lines[i][k] == 'S') {
                        num_of_halfs++;
                        continue;
                    }

                    if (input_lines[i][k] == 'L' || input_lines[i][k] == '7') {
                        num_of_halfs++;
                    } else if (input_lines[i][k] == 'J' || input_lines[i][k] == 'F') {
                        num_of_halfs--;
                    } else {
                        num_of_times_touch_pipes++;
                    }
                }
            }

            num_of_times_touch_pipes += num_of_halfs * 0.5;

            printf("Pipes touched: %d\n", num_of_times_touch_pipes);

            if ((int)num_of_times_touch_pipes % 2 != 0) {
                printf("Inside %c in [%ld, %ld] -------------------------\n", input_lines[i][j], i, j);

                num_of_grounds_inside_pipes++;
            }
        }
    }

    printf("Num of grounds inside pipes: %d\n", num_of_grounds_inside_pipes);

}
