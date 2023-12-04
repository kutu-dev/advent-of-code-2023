#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main() {
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

    char *scratchpads[lines];

    for (size_t i = 0; i < lines; i++)
    {
        scratchpads[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&scratchpads[i], &line_buffer_size, input_file);
        scratchpads[i][strcspn(scratchpads[i], "\r\n")] = 0;
    }

    int sum_of_matched_numbers = 0;

    for (size_t i = 0; i < sizeof scratchpads / sizeof scratchpads[0]; i++) {
        puts(scratchpads[i]);
        strtok(scratchpads[i], ":");

        char *scratchpad_winning_numbers_raw = strtok(NULL, "|");
        char *scratchpad_real_numbers_raw = strtok(NULL, "");
        char *buffered_number;
        char *cloned_number;
        size_t index_of_number;

        // Get the array of winning numbers
        int num_of_winning_numbers = 0;
        cloned_number = malloc(strlen(scratchpad_winning_numbers_raw) * sizeof(char));
        strncpy(cloned_number, scratchpad_winning_numbers_raw, strlen(scratchpad_winning_numbers_raw) * sizeof(char));

        buffered_number = strtok(cloned_number, " ");
        while (buffered_number != NULL) {
            buffered_number = strtok(NULL, " ");
            num_of_winning_numbers++;
        }

        free(cloned_number);

        int scratchpad_winning_numbers_size = num_of_winning_numbers * sizeof(int);
        int *scratchpad_winning_numbers = malloc(scratchpad_winning_numbers_size);

        buffered_number = strtok(scratchpad_winning_numbers_raw, " ");
        index_of_number = 0;
        while (buffered_number != NULL) {
            scratchpad_winning_numbers[index_of_number] = strtol(buffered_number, NULL, 10);
            buffered_number = strtok(NULL, " ");
            index_of_number++;
        }

        // Get the array of real numbers
        int num_of_real_numbers = 0;
        cloned_number = malloc(strlen(scratchpad_real_numbers_raw) * sizeof(char));
        strncpy(cloned_number, scratchpad_real_numbers_raw, strlen(scratchpad_real_numbers_raw) * sizeof(char));

        buffered_number = strtok(cloned_number, " ");
        while (buffered_number != NULL) {
            buffered_number = strtok(NULL, " ");
            num_of_real_numbers++;
        }

        free(cloned_number);

        int scratchpad_real_numbers_size = num_of_real_numbers * sizeof(int);
        int *scratchpad_real_numbers = malloc(scratchpad_real_numbers_size);

        buffered_number = strtok(scratchpad_real_numbers_raw, " ");
        index_of_number = 0;
        while (buffered_number != NULL) {
            scratchpad_real_numbers[index_of_number] = strtol(buffered_number, NULL, 10);
            buffered_number = strtok(NULL, " ");
            index_of_number++;
        }

        // Search matches
        int num_of_matched_numbers = 0;
        
        for (size_t j = 0; j < scratchpad_winning_numbers_size / sizeof(scratchpad_winning_numbers[0]); j++) {
            for (size_t k = 0; k < scratchpad_real_numbers_size / sizeof(scratchpad_real_numbers[0]); k++) {
                printf("%d %d\n", scratchpad_winning_numbers[j], scratchpad_real_numbers[k]);
                if (scratchpad_winning_numbers[j] == scratchpad_real_numbers[k]) {
                    num_of_matched_numbers++;
                }
            }
        }

        free(scratchpad_winning_numbers);
        free(scratchpad_real_numbers);

        if (num_of_matched_numbers > 0) {
            sum_of_matched_numbers += 1 * pow(2, num_of_matched_numbers - 1);
        }

    }

    printf("%d\n", sum_of_matched_numbers);

}
