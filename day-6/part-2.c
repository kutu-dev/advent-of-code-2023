#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

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

    // Get time value
    int num_of_digits_in_time = 0;
    for (size_t i = 0; i < strlen(input_lines[0]); i++) {
        if (isdigit(input_lines[0][i])) {
            num_of_digits_in_time++;
        }
    }

    char *array_of_digits_in_time = malloc((num_of_digits_in_time + 1) * sizeof(char));

    for (size_t i = 0, index_of_digits = 0; i < strlen(input_lines[0]); i++) {
        if (isdigit(input_lines[0][i])) {
            array_of_digits_in_time[index_of_digits] = input_lines[0][i];
            index_of_digits++;
        }
    }

    array_of_digits_in_time[num_of_digits_in_time + 1] = '\0';

    int time_value = strtol(array_of_digits_in_time, NULL, 10);
    free(array_of_digits_in_time);

    // Get distance value
    int num_of_digits_in_distance = 0;
    for (size_t i = 0; i < strlen(input_lines[1]); i++) {
        if (isdigit(input_lines[1][i])) {
            num_of_digits_in_distance++;
        }
    }

    char *array_of_digits_in_distance = malloc((num_of_digits_in_distance + 1) * sizeof(char));

    for (size_t i = 0, index_of_digits = 0; i < strlen(input_lines[1]); i++) {
        if (isdigit(input_lines[1][i])) {
            array_of_digits_in_distance[index_of_digits] = input_lines[1][i];
            index_of_digits++;
        }
    }

    array_of_digits_in_distance[num_of_digits_in_distance + 1] = '\0';

    long int distance_value = strtol(array_of_digits_in_distance, NULL, 10);
    free(array_of_digits_in_distance);

    // Calculate the margin error

    int max_time_hold = floor((time_value + sqrt(pow(time_value, 2) - 4 * (distance_value + 1))) / 2);
    int min_time_hold = ceil((time_value - sqrt(pow(time_value, 2) - 4 * (distance_value + 1))) / 2);

    printf("Margin error: %d\n", max_time_hold - min_time_hold + 1);
}
