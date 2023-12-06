#include <stdio.h>
#include <string.h>
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

    size_t num_of_races = 0;

    int length_input_line = strlen(input_lines[0]) * sizeof(char);
    char *cloned_input_line = malloc(length_input_line);
    strncpy(cloned_input_line, input_lines[0], length_input_line);

    strtok(cloned_input_line, ":");
    char *buffered_number = strtok(NULL, " ");

    while (buffered_number != NULL)
    {
        num_of_races++;
        buffered_number = strtok(NULL, " ");
    }

    free(cloned_input_line);

    int *time_values = malloc(num_of_races * sizeof(int));
    int *distance_values = malloc(num_of_races * sizeof(int));

    strtok(input_lines[0], ":");
    for (size_t i = 0; i < num_of_races; i++) {
        time_values[i] = strtol(strtok(NULL, " "), NULL, 10);
    }

    strtok(input_lines[1], ":");
    for (size_t i = 0; i < num_of_races; i++) {
        distance_values[i] = strtol(strtok(NULL, " "), NULL, 10);
    }

    int margin_error = 0;

    for (size_t i = 0; i < num_of_races; i++) {
        int max_time_hold = floor((time_values[i] + sqrt(pow(time_values[i], 2) - 4 * (distance_values[i] + 1))) / 2);
        int min_time_hold = ceil((time_values[i] - sqrt(pow(time_values[i], 2) - 4 * (distance_values[i] + 1))) / 2);

        if (margin_error == 0) {
            margin_error = max_time_hold - min_time_hold + 1;
        } else {
            margin_error *= max_time_hold - min_time_hold + 1;
        }
    }

    printf("Total margin error: %d\n", margin_error);

    free(time_values);
    free(distance_values);
}
