#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long transform_source_to_destination(char **input_lines, int input_lines_length, long long int source_number, char *buffered_line)
{
    for (size_t i = 2; i < (size_t)input_lines_length; i++)
    {
        if (strstr(input_lines[i], "map") == NULL)
        {
            continue;
        }

        //printf("NEW MAP %s\n", input_lines[i]);
        bool already_changed = false;

        for (size_t j = i + 1;
         j < (size_t)input_lines_length && strcmp(input_lines[j], "") != 0;
         j++)
        {
            if (already_changed) {
                //printf("ALREADY CHANGED");
                break;
            }

            strcpy(buffered_line, input_lines[j]);

            long long int destination_range_start = strtol(strtok(buffered_line, " "), NULL, 10);
            long long int source_range_start = strtol(strtok(NULL, " "), NULL, 10);
            long long int map_range_length = strtol(strtok(NULL, " "), NULL, 10);

            long long int source_range_end = source_range_start + map_range_length - 1;

            //printf("LINE %ld\n", j+1);
            //printf("D%lld S%lld R%lld\n",
            //   destination_range_start,
            //   source_range_start,
            //   map_range_length);
        
            //printf("%lld\n", source_number);
            //printf("%lld\n", source_range_end);


            if (source_number < source_range_start ||
                source_number > source_range_end)
            {
                //printf("SKIPPED: %lld is bigger/smaller than %lld/%lld\n", source_number, source_range_end, source_range_start);
                continue;
            }

            
            source_number = destination_range_start + (source_number - source_range_start);
            already_changed = true;
            //printf("NUMBER CHANGED TO %lld\n", source_number);
        }
    }
    return source_number;
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

    // Clone the first line and get the number of seeds
    size_t num_of_seeds = 0;
    int length_seed_line = strlen(input_lines[0]) * sizeof(char);
    char *cloned_seeds_line = malloc(length_seed_line);
    strncpy(cloned_seeds_line, input_lines[0], length_seed_line);

    strtok(cloned_seeds_line, ":");
    char *buffered_number = strtok(NULL, " ");

    while (buffered_number != NULL)
    {
        num_of_seeds++;
        buffered_number = strtok(NULL, " ");
    }

    free(cloned_seeds_line);

    int length_seed_num_array = num_of_seeds * sizeof(long long int);
    long long int *seeds = malloc(length_seed_num_array);

    strtok(input_lines[0], ":");
    // Avoid uninitialized array
    seeds[0] = strtol(strtok(NULL, " "), NULL, 10);
    for (size_t i = 1; i < num_of_seeds; i++)
    {
        seeds[i] = strtol(strtok(NULL, " "), NULL, 10);
    }

    //long long int lowest_number = NULL;

    long long int lowest_number = 0;

    char *buffered_line = malloc(50);

    for (size_t i = 0; i < num_of_seeds; i +=2) {
        for (long long int j = seeds[i]; j < seeds[i] + seeds[i+1]; j++) {
            
            printf("PABAJO %lld ----------------------------------------\n", j);
            long long int new_transformed_number = transform_source_to_destination(input_lines, lines, j, buffered_line);
            printf("TRANSFORMADO A %lld\n", new_transformed_number);

            if (lowest_number == 0 || new_transformed_number < lowest_number) {
                lowest_number = new_transformed_number;
                printf(">>>>>>>>>>>>>>>>>>> NUEVO MIN %lld\n", lowest_number);
            }

            //long long int transformed_number = 
            //printf("%lld\n", transformed_number);
        }
    }

    free(seeds);
    free(buffered_line);
    printf("SOLUCION %lld\n", lowest_number);
}
