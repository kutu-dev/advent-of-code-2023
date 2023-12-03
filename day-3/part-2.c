#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
// #include "../common/logger.h"

typedef struct EnginePart
{
    int part_id;
    int gear_id;
    bool already_used;
    int added_value;
} engine_part;

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

    int sum_of_powers_of_parts = 0;
    char buffer[strlen(schematic_lines[0])];
    bool valid_part;
    int gear_id = 0;
    engine_part engine_parts[10000];
    int num_of_registered_parts = 0;

    for (size_t i = 0; i < lines; i++)
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
                        bool found = false;

                        for (size_t k = 0; k < sizeof(engine_parts) / sizeof(engine_parts[1]); k++)
                        {
                            if (engine_parts[k].gear_id != gear_id)
                            {
                                continue;
                            }

                            if (engine_parts[k].already_used)
                            {
                                printf("COLISION DETECTED: %d %ld\n", engine_parts[k].part_id, strtol(buffer, NULL, 10));
                                printf("REMOVED %d\n", engine_parts[k].added_value);
                                sum_of_powers_of_parts -= engine_parts[k].added_value;
                                engine_parts[k].added_value = 0;
                                continue;
                            }

                            int num_to_add = engine_parts[k].part_id * strtol(buffer, NULL, 10);
                            sum_of_powers_of_parts += num_to_add;
                            engine_parts[k].added_value = num_to_add;
                            engine_parts[k].already_used = true;
                            printf("MATCH: %d %ld\n", engine_parts[k].part_id, strtol(buffer, NULL, 10));
                            found = true;
                        }

                        if (found)
                        {
                            continue;
                        }

                        printf("%s\n", buffer);
                        engine_parts[num_of_registered_parts].part_id = strtol(buffer, NULL, 10);
                        engine_parts[num_of_registered_parts].gear_id = gear_id;
                        engine_parts[num_of_registered_parts].already_used = false;
                        engine_parts[num_of_registered_parts].added_value = 0;
                        num_of_registered_parts++;
                    }
                }
            }

            if (!isdigit(schematic_lines[i][j]) && isdigit(schematic_lines[i][j - 1]))
            {
                if (valid_part)
                {
                    bool found = false;

                    for (size_t k = 0; k < sizeof(engine_parts) / sizeof(engine_parts[1]); k++)
                    {
                        if (engine_parts[k].gear_id != gear_id)
                        {
                            continue;
                        }

                        if (engine_parts[k].already_used)
                        {
                            printf("COLISION DETECTED: %d %ld\n", engine_parts[k].part_id, strtol(buffer, NULL, 10));
                            printf("REMOVED %d\n", engine_parts[k].added_value);
                            sum_of_powers_of_parts -= engine_parts[k].added_value;
                            engine_parts[k].added_value = 0;

                            continue;
                        }

                        int num_to_add = engine_parts[k].part_id * strtol(buffer, NULL, 10);
                        sum_of_powers_of_parts += num_to_add;
                        engine_parts[k].added_value = num_to_add;
                        engine_parts[k].already_used = true;
                        printf("MATCH: %d %ld\n", engine_parts[k].part_id, strtol(buffer, NULL, 10));
                        found = true;
                    }

                    if (found)
                    {
                        continue;
                    }

                    printf("%s\n", buffer);
                    engine_parts[num_of_registered_parts].part_id = strtol(buffer, NULL, 10);
                    engine_parts[num_of_registered_parts].gear_id = gear_id;
                    engine_parts[num_of_registered_parts].already_used = false;
                    engine_parts[num_of_registered_parts].added_value = 0;
                    num_of_registered_parts++;
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
                gear_id = 0;
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

                    if (schematic_lines[i + k][j + l] == '*')
                    {
                        valid_part = true;

                        gear_id = (i + k) * pow(10, (floor(log10(j + l)) + 1)) + (j + l);
                    }
                }
            }
        }
    }

    printf("SOLUTION: %d\n", sum_of_powers_of_parts);
}
