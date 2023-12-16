#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./part-1.h"

int pound(char *record, sizes_struct sizes) {
        //printf("  Record: %s\n", record);

        int next_size = sizes.size_array[0];

        if (strlen(record) < (size_t)next_size) {
            return 0;
        }

        char *spring_slice = malloc((next_size + 1) * sizeof(char));
        strncpy(spring_slice, record, next_size);

        spring_slice[next_size] = '\0';

        if (strstr(spring_slice, ".")) {
            return 0;
        }

        //printf("  %d Substring %s\n",next_size, spring_slice);


        free(spring_slice);

        //printf("  String %s with length %ld\n", record, strlen(record));
        if (strlen(record) == (size_t)next_size) {
            if (sizes.num_of_sizes == 1) {
                puts("RETURN 2");
                return 1;
            } else {
                return 0;
            }
        }

        if (record[next_size] == '.' || record[next_size] == '?') {
            sizes_struct new_sizes;
            new_sizes.size_array = &(sizes.size_array[1]);
            new_sizes.num_of_sizes = sizes.num_of_sizes - 1;

            return calculate_combinations(&record[next_size + 1], new_sizes);
        }

        return 0;
    }

int calculate_combinations(char *record, sizes_struct sizes) {
    //printf("  Current char %c\n", record[0]);

    printf("-> %d\n", sizes.num_of_sizes);
    for (size_t i = 0; i < (size_t)sizes.num_of_sizes; i++) {
        printf("%d,", sizes.size_array[i]);
    }
    puts("");

    if (sizes.num_of_sizes == 0) {
        puts("NO SIZES");
        if (strstr(record, "#") == NULL) {
            puts("RETURN 1");
            return 1;
        } else {
            return 0;
        }
    }

    if (strcmp(record, "") == 0) {
        puts("WHAT");
        return 0;
    }

    char next_char = record[0];

    int out = 0;
    if (next_char == '.') {
        //puts("  Skipping");
        out = calculate_combinations(&record[1], sizes);
    } else if (next_char == '#') {
        out = pound(record, sizes);
    } else if (next_char == '?') {
        //puts("  with ? as #");
        int part_2 = calculate_combinations(&record[1], sizes);

        int part_1 = pound(record, sizes);

        //puts("  with ? as .");

        out = part_1 + part_2;
    }

    return out;
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

    int sum_of_all_combinations = 0;
    for (size_t i = 0; i < lines; i++) {
        char *record = strtok(input_lines[i], " ");
        char *sizes_string = strtok(NULL, "");

        int num_of_sizes = 1;
        for (size_t j = 0; j < strlen(sizes_string); j++) {
            if (sizes_string[j] == ',') {
                num_of_sizes++;
            }
        }

        sizes_struct sizes;
        sizes.size_array = malloc(num_of_sizes * sizeof(sizes_struct));
        sizes.num_of_sizes = num_of_sizes;

        char *size_buffer = strtok(sizes_string, ",");
        int size_index = 0;
        while(size_buffer != NULL) {
            sizes.size_array[size_index++] = strtol(size_buffer, NULL, 10);
            size_buffer = strtok(NULL, ",");
        }

        printf("Line %ld: %s\n", i+1 , input_lines[i]);

        int total = calculate_combinations(record, sizes);

        printf("Total %d\n", total);

        sum_of_all_combinations += total;

        free(sizes.size_array);
    }

    printf("Sum of all combinations: %d\n", sum_of_all_combinations);
}
