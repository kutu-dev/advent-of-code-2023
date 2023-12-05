#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transform_source_to_destination(char **input_lines,
                                     int input_lines_length,
                                     int map_index,
                                     long long int *source_array,
                                     int num_of_elements_in_source_array)
{
    printf(input_lines[map_index]);
    printf(" %lld\n", source_array[0]);

    if (input_lines_length < 0)
    {
        return;
    }

    if (num_of_elements_in_source_array < 0)
    {
        return;
    }

    bool *indexes_already_transformed =
            malloc(num_of_elements_in_source_array * sizeof(bool));
        memset(indexes_already_transformed, false, num_of_elements_in_source_array);

    // If the line is not empty and it's not the last line
    for (size_t i = map_index + 1;
         i < (size_t)input_lines_length && strcmp(input_lines[i], "") != 0;
         i++)
    {
        long long int destination_range_start = strtol(strtok(input_lines[i], " "), NULL, 10);
        long long int source_range_start = strtol(strtok(NULL, " "), NULL, 10);
        long long int map_range_length = strtol(strtok(NULL, " "), NULL, 10);

        long long int source_range_end = source_range_start + map_range_length - 1;

        printf("LINE %ld\n", i+1);
        printf("D%lld S%lld R%lld\n",
               destination_range_start,
               source_range_start,
               map_range_length);
        
        for (size_t j = 0; j < (size_t)num_of_elements_in_source_array; j++)
        {
            //printf("%lld\n", source_array[j]);
            //printf("%d\n", indexes_already_transformed[j]);

            if (indexes_already_transformed[j] == true)
            {
                puts("ALREADY CHANGED!");
                continue;
            }

            if (source_array[j] < source_range_start ||
                source_array[j] > source_range_end)
            {
                printf("SKIPPED: %lld is bigger/smaller than %lld/%lld\n", source_array[j], source_range_end, source_range_start);
                continue;
            }

            printf("------------>>>>>> CHANGED %lld because it's in range %lld-%lld\n",source_array[j], source_range_start, source_range_end);

            printf("NEW VALUE %lld\n", source_array[j]);
            //printf("NEW VALUE %lld\n", source_range_start);
            source_array[j] = destination_range_start + (source_array[j] - source_range_start);
            //printf("NEW VALUE %lld\n", destination_range[source_array[j] - source_range_start]);
            printf("NEW VALUE %lld\n", source_array[j]);

            indexes_already_transformed[j] = true;
        }
    }

    free(indexes_already_transformed);
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

    // Start at 2 as the two first lines will never be a map
    for (size_t i = 2; i < lines; i++)
    {
        if (strstr(input_lines[i], "map") == NULL)
        {
            continue;
        }

        transform_source_to_destination(input_lines, lines, i, seeds, num_of_seeds);
    }

    for (size_t i = 0; i < num_of_seeds; i++) {
        printf("%ld - %lld\n",i+1, seeds[i]);
    }

    long long int lowest_number = seeds[0];

    for (size_t i = 1; i < num_of_seeds; i++) {
        if (seeds[i] < lowest_number) {
            lowest_number = seeds[i];
        }
    }

    printf("SOLUTION %lld", lowest_number);

    free(seeds);
}
