#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    long long int start;
    long long int end;
} interval;

typedef struct
{
    interval *reallocated_interval_array;
    size_t reallocated_interval_array_size;
} new_interval_array;

new_interval_array
transform_source_to_destination(char **input_lines,
                                int input_lines_length,
                                int map_index,
                                interval *source_intervals_array,
                                int num_of_intervals_in_source_array)
{
    if (num_of_intervals_in_source_array < 0)
    {
        exit(1);
    }

    printf("Calculating: %s\n", input_lines[map_index]);

    interval *queued_intervals = malloc(num_of_intervals_in_source_array * 3 * sizeof(interval));

    bool *already_transformed_interval = malloc(num_of_intervals_in_source_array * 3 * sizeof(bool));
    memset(already_transformed_interval, false, num_of_intervals_in_source_array * 3);

    size_t elements_in_queued_intervals = num_of_intervals_in_source_array;
    for (size_t i = 0; i < (size_t)num_of_intervals_in_source_array; i++)
    {
        queued_intervals[i].start = source_intervals_array[i].start;
        queued_intervals[i].end = source_intervals_array[i].end;
    }

    // If the line is not empty and it's not the last line
    for (size_t i = map_index + 1;
         i < (size_t)input_lines_length && strcmp(input_lines[i], "") != 0;
         i++)
    {
        long long int destination_range_start = strtol(strtok(input_lines[i], " "), NULL, 10);
        long long int source_range_start = strtol(strtok(NULL, " "), NULL, 10);
        long long int map_range_length = strtol(strtok(NULL, " "), NULL, 10);

        long long int source_range_end = source_range_start + map_range_length - 1;
        long long int destination_range_end = destination_range_start + map_range_length - 1;

        printf("  ┗ Rule (line %ld) for range [%lld, %lld] to [%lld, %lld]\n", i, source_range_start, source_range_end, destination_range_start, destination_range_end);

        for (size_t j = 0; j < elements_in_queued_intervals; j++)
        {
            printf("      ┗ Transforming: [%lld, %lld]\n", queued_intervals[j].start, queued_intervals[j].end);

            if (already_transformed_interval[j])
            {
                printf("           ┗ Skipping: already transformed\n");
                continue;
            }

            if (queued_intervals[j].end < source_range_start)
            {
                printf("           ┗ Skipping: too small\n");
                continue;
            }

            if (queued_intervals[j].start > source_range_end)
            {
                printf("           ┗ Skipping: too large\n");
                continue;
            }

            interval intersection;
            interval rest_before = {.start = -1, .end = -1};
            interval rest_after = {.start = -1, .end = -1};

            if (queued_intervals[j].start >= source_range_start)
            {
                intersection.start = queued_intervals[j].start;
            }
            else
            {
                intersection.start = source_range_start;
                rest_before.start = queued_intervals[j].start;
                rest_before.end = source_range_start - 1;
            }

            if (queued_intervals[j].end <= source_range_end)
            {
                intersection.end = queued_intervals[j].end;
            }
            else
            {
                intersection.end = source_range_end;
                rest_after.start = source_range_end + 1;
                rest_after.end = queued_intervals[j].end;
            }

            printf("           ┗ Intersection [%lld, %lld]\n", intersection.start, intersection.end);

            interval transformed = {.start = destination_range_start + (intersection.start - source_range_start), .end = destination_range_end - (source_range_end - intersection.end)};

            queued_intervals[j] = transformed;
            already_transformed_interval[j] = true;

            if (rest_before.start != -1 && rest_before.end != -1)
            {
                printf("              ┗ With rest (before): [%lld, %lld]\n", rest_before.start, rest_before.end);
                queued_intervals[elements_in_queued_intervals] = rest_before;
                elements_in_queued_intervals++;
            }

            if (rest_after.start != -1 && rest_after.end != -1)
            {
                printf("              ┗ With rest (after): [%lld, %lld]\n", rest_after.start, rest_after.end);
                queued_intervals[elements_in_queued_intervals] = rest_after;
                elements_in_queued_intervals++;
            }
        }
    }

    free(already_transformed_interval);

    printf("  ┗ Transformed intervals in %s\n", input_lines[map_index]);
    for (size_t i = 0; i < elements_in_queued_intervals; i++)
    {
        printf("     ┗ [%lld, %lld]\n", queued_intervals[i].start, queued_intervals[i].end);
    }

    interval *reallocated_source = realloc(source_intervals_array, elements_in_queued_intervals * sizeof(interval));
    if (reallocated_source == NULL)
    {
        exit(1);
    }

    memcpy(reallocated_source, queued_intervals, elements_in_queued_intervals * sizeof(interval));

    free(queued_intervals);

    new_interval_array new_array = {.reallocated_interval_array = reallocated_source, .reallocated_interval_array_size = elements_in_queued_intervals};

    return new_array;
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

    interval *seeds_interval = malloc(num_of_seeds / 2 * sizeof(interval));

    for (size_t i = 0; i < num_of_seeds; i += 2)
    {
        printf("Starting seed interval: [%lld, %lld]\n", seeds[i], seeds[i] + seeds[i + 1] - 1);
        seeds_interval[i / 2].start = seeds[i];
        seeds_interval[i / 2].end = seeds[i] + seeds[i + 1] - 1;
    }

    // Start at 2 as the two first lines will never be a map
    num_of_seeds = num_of_seeds / 2;
    for (size_t i = 2; i < lines; i++)
    {
        if (strstr(input_lines[i], "map") == NULL)
        {
            continue;
        }

        new_interval_array new_array = transform_source_to_destination(input_lines, lines, i, seeds_interval, num_of_seeds);
        seeds_interval = new_array.reallocated_interval_array;
        num_of_seeds = new_array.reallocated_interval_array_size;
        puts("");
    }

    printf("Searching lowest:\n");
    long long int lowest_number = seeds_interval[0].start;
    printf("  ┗ Starting with %lld\n", seeds_interval[0].start);

    for (size_t i = 1; i < num_of_seeds; i++)
    {
        if (seeds_interval[i].start < lowest_number)
        {
            printf("  ┗ %lld < %lld\n", seeds_interval[i].start, lowest_number);
            lowest_number = seeds_interval[i].start;
        }
        else
        {
            printf("  ┗ %lld > %lld\n", seeds_interval[i].start, lowest_number);
        }
    }

    printf("Lowest number: %lld\n", lowest_number);

    free(seeds);
    free(seeds_interval);
}
