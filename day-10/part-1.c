#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

    //printf("Next pipe found at [%d][%d]\n", current_y, current_x);

    int num_of_steps = 0;

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

        printf("Going to %c, in [%d, %d]\n", input_lines[current_y][current_x], current_y + 1, current_x + 1);
        num_of_steps++;
    }

    printf("Steps to starting pipe: %d\n", num_of_steps);
    printf("Steps to farthest pipe: %d\n", (int)(floor(num_of_steps / 2) + 1));
}
