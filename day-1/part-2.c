#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../common/logger.h"

int main()
{
    FILE *input_file;

    if ((input_file = fopen("input.txt", "r")) == NULL)
    {
        error_print("2", "1", "'input.txt' file could not be opened!");
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

    char *bad_calibration_values[lines];

    for (size_t i = 0; i < lines; i++)
    {
        bad_calibration_values[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&bad_calibration_values[i], &line_buffer_size, input_file);
    }

    fclose(input_file);

    int final_calibration_value = 0;

    for (size_t i = 0; i < sizeof(bad_calibration_values) / sizeof(bad_calibration_values[0]); i++)
    {
        int value_length = strlen(bad_calibration_values[i]);
        char first_digit = '\0';
        char last_digit = '\0';

        for (int j = 0; j < value_length; j++)
        {
            if (isdigit(bad_calibration_values[i][j]))
            {
                if (first_digit == '\0')
                {
                    first_digit = bad_calibration_values[i][j];
                }
                last_digit = bad_calibration_values[i][j];
                continue;
            }

            char three_chars[4], four_chars[5], five_chars[6];

            strncpy(three_chars, bad_calibration_values[i] + j, 3);
            three_chars[3] = '\0';

            strncpy(four_chars, bad_calibration_values[i] + j, 4);
            four_chars[4] = '\0';

            strncpy(five_chars, bad_calibration_values[i] + j, 5);
            five_chars[5] = '\0';

            if (strcmp(three_chars, "one") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '1';
                }
                last_digit = '1';
            }
            else if (strcmp(three_chars, "two") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '2';
                }
                last_digit = '2';
            }
            else if (strcmp(five_chars, "three") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '3';
                }
                last_digit = '3';
            }
            else if (strcmp(four_chars, "four") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '4';
                }
                last_digit = '4';
            }
            else if (strcmp(four_chars, "five") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '5';
                }
                last_digit = '5';
            }
            else if (strcmp(three_chars, "six") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '6';
                }
                last_digit = '6';
            }
            else if (strcmp(five_chars, "seven") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '7';
                }
                last_digit = '7';
            }
            else if (strcmp(five_chars, "eight") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '8';
                }
                last_digit = '8';
            }
            else if (strcmp(four_chars, "nine") == 0)
            {
                if (first_digit == '\0')
                {
                    first_digit = '9';
                }
                last_digit = '9';
            }
        }

        char fixed_calibration_value[] = {first_digit, last_digit, '\0'};
        final_calibration_value += strtol(fixed_calibration_value, NULL, 10);
    }

    char answer_format[] = "Answer: %d";
    size_t length_valid_calibration_value = snprintf(NULL, 0, answer_format, final_calibration_value) + 1;
    char *valid_calibration_value_converted = malloc(length_valid_calibration_value);
    snprintf(valid_calibration_value_converted, length_valid_calibration_value, answer_format, final_calibration_value);

    info_print("1", "2", valid_calibration_value_converted);
    free(valid_calibration_value_converted);

    return 0;
}
