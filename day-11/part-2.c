#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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

    puts("Calculating horizontal space expansion...");

    int *new_horizontal_lines = malloc(lines * sizeof(int));
    size_t num_new_horizontal_lines = 0;
    for (size_t i = 0; i < lines; i++) {
        bool row_empty = true;

        for (size_t j = 0; j < lines; j++) {
            if (input_lines[i][j] != '.') {
                row_empty = false;
                break;
            }
        }

        if (row_empty) {
            new_horizontal_lines[num_new_horizontal_lines] = i;
            num_new_horizontal_lines++;
        }

    }

    printf("Found %ld horizontal lines to add\n", num_new_horizontal_lines);

    puts("Calculating vertical space expansion...");

    int *new_vertical_lines = malloc(strlen(input_lines[0]) * sizeof(int));;
    size_t num_new_vertical_lines = 0;
    for (size_t i = 0; i < strlen(input_lines[0]); i++) {
        bool column_empty = true;

        for (size_t j = 0; j < lines; j++) {
            if (input_lines[j][i] != '.') {
                column_empty = false;
                break;
            }
        }

        if (column_empty) {
            new_vertical_lines[num_new_vertical_lines] = i;
            num_new_vertical_lines++;
        }

    }

    printf("Found %ld vertical lines to add\n", num_new_vertical_lines);

    for (size_t i = 0; i < (size_t)(lines); i++) {
        printf("%s\n",input_lines[i]);
    }
      
    puts("");

    char **resized_input = malloc((lines + num_new_horizontal_lines) * sizeof(char *));

    for (size_t i = 0; i < lines + num_new_horizontal_lines; i++) {
        resized_input[i] = malloc((strlen(input_lines[0]) + num_new_vertical_lines) * sizeof(char));
    }

    bool next_line_empty = false;
    int horizontal_offset = 0;
    for (size_t i = 0; i < lines + num_new_horizontal_lines; i++) {
        if (next_line_empty) {
            for (size_t j = 0; j < strlen(input_lines[0]) + num_new_vertical_lines; j++) {
                resized_input[i][j] = 'H';
            }
            next_line_empty = false;
            horizontal_offset++;
            continue;
        }

        for (size_t j = 0; j < num_new_horizontal_lines; j++) {
            if (i - horizontal_offset == (size_t)(new_horizontal_lines[j])) {
                next_line_empty = true;
            }
        }

        bool next_char_empty = false;
        int vertical_offset = 0;
        for (size_t j = 0; j < strlen(input_lines[0]) + num_new_vertical_lines; j++) {
            if (next_char_empty) {
                resized_input[i][j] = '.';
                next_char_empty = false;
                vertical_offset++;
                continue;
            }

            for (size_t k = 0; k < num_new_vertical_lines; k++) {
                if (j - vertical_offset == (size_t)(new_vertical_lines[k])) {
                    next_char_empty = true;
                }
            }

            resized_input[i][j] = input_lines[i - horizontal_offset][j - vertical_offset];
        }

    }

    for (size_t i = 0; i < (size_t)(lines + num_new_horizontal_lines); i++) {
        printf("%s\n", resized_input[i]);
    }

    int sum_of_distances = 0;

    puts("Calculating length between galaxies");
    int foo = 0;
    for (size_t i = 0; i < (size_t)(lines + num_new_horizontal_lines); i++) {
        for (size_t j = 0; j < strlen(resized_input[i]); j++) {

            if (resized_input[i][j] == '#') {
                foo++;
                printf("Galaxy %d [%ld, %ld] found:\n", foo, i, j);

                int bar = foo;
                for (size_t k = i; k < (size_t)(lines + num_new_horizontal_lines); k++) {
                        size_t char_index = 0;
                        if (k == i) {
                            char_index = j + 1;
                        }

                    for (size_t l = char_index; l < strlen(resized_input[k]); l++) {
                        //printf("Trying [%ld, %ld]\n", k, l);
                        if (resized_input[k][l] == '#') {
                            bar++;
                            printf("  Pair galaxy %d [%ld, %ld] found, calculating distance:\n", bar, k, l);
                            int distance = 0;

                            distance = abs((int)k - (int)i)  + abs((int)l - (int)j);

                            sum_of_distances += distance;
                            printf("    Galaxies [%ld, %ld] - [%ld, %ld] distance %d\n", i, j, k, l, distance);
                        }
                    }
                }
            }
        }
    }

    printf("Sum of distances %d\n", sum_of_distances);

    free(new_horizontal_lines);
    free(new_vertical_lines);

    for (size_t i = 0; i < lines + num_new_horizontal_lines; i++) {
        free(resized_input[i]);
    }

    free(resized_input);
}
