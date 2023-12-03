#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../common/logger.h"

int main()
{
    FILE *input_file;

    if ((input_file = fopen("input.txt", "r")) == NULL)
    {
        error_print("2", "2", "'input.txt' file could not be opened!");
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

    char *games[lines];

    for (size_t i = 0; i < lines; i++)
    {
        games[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&games[i], &line_buffer_size, input_file);
        games[i][strcspn(games[i], "\r\n")] = 0;
    }

    int sum_of_power_of_min_cubes = 0;

    for (size_t i = 0; i < lines; i++)
    {
        // Get the data of the game
        strtok(games[i], ":");
        char *game_data = strtok(NULL, "");

        int min_red_cubes = 0;
        int min_green_cubes = 0;
        int min_blue_cubes = 0;

        size_t number_of_sets = 1;
        for (size_t j = 0; j < strlen(game_data); j++)
        {
            if (game_data[j] == ';')
            {
                number_of_sets++;
            }
        }

        char *sets[number_of_sets];
        sets[0] = strtok(game_data, ";");

        for (size_t j = 1; j < number_of_sets; j++)
        {
            sets[j] = strtok(NULL, ";");
        }

        for (size_t j = 0; j < sizeof(sets) / sizeof(sets[0]); j++)
        {
            size_t num_cube_colors = 1;
            for (size_t k = 0; k < strlen(sets[j]); k++)
            {
                if (sets[j][k] == ',')
                {
                    num_cube_colors++;
                }
            }

            char *cube_colors[num_cube_colors];
            cube_colors[0] = strtok(sets[j], ",");

            for (size_t k = 1; k < num_cube_colors; k++)
            {
                cube_colors[k] = strtok(NULL, ",");
            }

            for (size_t k = 0; k < sizeof(cube_colors) / sizeof(cube_colors[0]); k++)
            {
                int num_of_cubes = strtol(strtok(cube_colors[k], " "), NULL, 10);
                char *cube_color = strtok(NULL, "");

                if ((strcmp(cube_color, "red")) == 0 && num_of_cubes > min_red_cubes)
                {
                    min_red_cubes = num_of_cubes;
                }

                if ((strcmp(cube_color, "blue")) == 0 && num_of_cubes > min_green_cubes)
                {
                    min_green_cubes = num_of_cubes;
                }

                if ((strcmp(cube_color, "green")) == 0 && num_of_cubes > min_blue_cubes)
                {
                    min_blue_cubes = num_of_cubes;
                }
            }
        }

        sum_of_power_of_min_cubes += min_red_cubes * min_green_cubes * min_blue_cubes;
    }

    char answer_format[] = "Answer: %d";
    size_t length_of_sum_of_valid_ids = snprintf(NULL, 0, answer_format, sum_of_power_of_min_cubes) + 1;
    char *sum_of_valid_ids_converted = malloc(length_of_sum_of_valid_ids);
    snprintf(sum_of_valid_ids_converted, length_of_sum_of_valid_ids, answer_format, sum_of_power_of_min_cubes);

    info_print("2","2",sum_of_valid_ids_converted);
    free(sum_of_valid_ids_converted);

    return 0;
}
