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

    int size_of_the_empty_space = 1000000;
    long long sum_of_distances = 0;

    puts("Calculating length between galaxies");
    int foo = 0;
    for (size_t i = 0; i < lines; i++) {
        for (size_t j = 0; j < strlen(input_lines[i]); j++) {

            if (input_lines[i][j] == '#') {
                foo++;
                printf("Galaxy %d [%ld, %ld] found:\n", foo, i, j);

                int bar = foo;
                for (size_t k = i; k < lines; k++) {
                        size_t char_index = 0;
                        if (k == i) {
                            char_index = j + 1;
                        }

                    for (size_t l = char_index; l < strlen(input_lines[k]); l++) {
                        //printf("Trying [%ld, %ld]\n", k, l);
                        if (input_lines[k][l] == '#') {
                            bar++;
                            printf("  Pair galaxy %d [%ld, %ld] found, calculating distance:\n", bar, k, l);

                            long long extra_horizontal_empty_lines = 0;

                            for (size_t m = 0; m < num_new_horizontal_lines; m++) {
                                long long low = 0;
                                long long high = 0;

                                if (i < k) {
                                    low = i;
                                    high = k;
                                } else {
                                    low = k;
                                    high = i;
                                }

                                if (new_horizontal_lines[m] > low && new_horizontal_lines[m] < high) {
                                    extra_horizontal_empty_lines += (size_of_the_empty_space - 1);
                                }
                            }

                            long long extra_vertical_empty_lines = 0;

                            for (size_t m = 0; m < num_new_vertical_lines; m++) {
                                long long low = 0;
                                long long high = 0;

                                if (j < l) {
                                    low = j;
                                    high = l;
                                } else {
                                    low = l;
                                    high = j;
                                }
                                
                                if (new_vertical_lines[m] > low && new_vertical_lines[m] < high) {
                                    extra_vertical_empty_lines += (size_of_the_empty_space - 1);
                                }
                            }

                            long long distance = 0;

                            distance = abs((int)k - (int)i) + abs((int)l - (int)j) + extra_horizontal_empty_lines + extra_vertical_empty_lines;

                            sum_of_distances += distance;
                            printf("    Galaxies [%ld, %ld] - [%ld, %ld] distance %lld\n", i, j, k, l, distance);
                        }
                    }
                }
            }
        }
    }

    printf("Sum of distances %lld\n", sum_of_distances);

    free(new_horizontal_lines);
    free(new_vertical_lines);
}
