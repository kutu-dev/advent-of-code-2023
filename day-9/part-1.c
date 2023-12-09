#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

    int sum_of_extrapolated_values = 0;

    for (size_t i = 0; i < lines; i++) {
        printf("Dataset: %s\n", input_lines[i]);

        int last_sum = 0;

        int *data = malloc(100 * sizeof(int)); 
        int data_index = 0;

        char *buffer = strtok(input_lines[i], " ");
        while(buffer != NULL) {
            data[data_index] = strtol(buffer, NULL, 10);
            printf("Data: %d\n", data[data_index]);
            buffer = strtok(NULL, " ");
            data_index++;
        }

        last_sum += data[data_index - 1];
        printf("Last number set to %d adding number %d\n", last_sum, data[data_index - 1]);

        bool all_zeros = false;
        while(all_zeros == false) {
            all_zeros = true;
            for (size_t j = 0; j < (size_t)data_index; j++) {
                if (data[j] != 0) {
                    all_zeros = false;
                }
            }

            if (all_zeros) {
                break;
            }

            int old_data_index = data_index;
            data_index = 0;

            for (size_t j = 0; j < (size_t)old_data_index - 1; j++) {
                data[data_index] = data[j + 1] - data[j];
                data_index++;
            }

            last_sum += data[data_index - 1];
            printf("Last number set to %d adding number %d\n", last_sum, data[data_index - 1]);
        }

        printf("Extrapolated value: %d\n", last_sum);
        sum_of_extrapolated_values += last_sum;

        free(data);
    }

    printf("Sum of all extrapolated values: %d\n", sum_of_extrapolated_values);

}
