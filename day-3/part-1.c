#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
// #include "../common/logger.h"

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

    char *schematic_lines[lines];

    for (size_t i = 0; i < lines; i++)
    {
        schematic_lines[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&schematic_lines[i], &line_buffer_size, input_file);
        schematic_lines[i][strcspn(schematic_lines[i], "\r\n")] = 0;
    }

    int sum_of_valid_parts = 0;
    char buffer[strlen(schematic_lines[0])];
    bool valid_part;

    for (size_t i = 0; i < lines + 1; i++)
    {
        printf("LINE: %zu\n", i + 1);

        for (size_t j = 0; j < strlen(schematic_lines[i]); j++)
        {
            if (i != 0 && j == 0)
            {
                if (isdigit(schematic_lines[i - 1][strlen(schematic_lines[i - 1]) - 1]))
                {
                    if (valid_part)
                    {
                        printf("LINE BEFORE: %s\n", buffer);
                        sum_of_valid_parts += strtol(buffer, NULL, 10);
                    }
                }
            }

            if (!isdigit(schematic_lines[i][j]) && isdigit(schematic_lines[i][j - 1]))
            {
                if (valid_part)
                {
                    printf("%s\n", buffer);
                    sum_of_valid_parts += strtol(buffer, NULL, 10);
                }
            }

            if (!isdigit(schematic_lines[i][j]))
            {
                continue;
            }

            if (isdigit(schematic_lines[i][j - 1]))
            {
                buffer[strlen(buffer)] = schematic_lines[i][j];
            }
            else
            {
                memset(buffer, 0, sizeof(buffer));
                valid_part = false;
                buffer[0] = schematic_lines[i][j];
            }

            // Look around the digit
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > lines - 1 || j + l < 0 || j + l > strlen(schematic_lines[i]) - 1)
                    {
                        continue;
                    }

                    if (!isdigit(schematic_lines[i + k][j + l]) && schematic_lines[i + k][j + l] != '.')
                    {
                        valid_part = true;
                    }
                }
            }
        }
    }

    printf("%d\n", sum_of_valid_parts);
}
