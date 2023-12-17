#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./part-2.h"
#include "../common/c-hashmap/map.h"

long long pound(hashmap *memory, char *record, sizes_struct sizes) {
        //printf("  Record: %s\n", record);

        long long next_size = sizes.size_array[0];

        if (strlen(record) < (size_t)next_size) {
            return 0;
        }

        char *spring_slice = malloc((next_size + 1) * sizeof(char));
        strncpy(spring_slice, record, next_size);

        spring_slice[next_size] = '\0';

        if (strstr(spring_slice, ".")) {
            return 0;
        }

        //printf("  %d Substring %s\n",next_size, spring_slice);


        free(spring_slice);

        //printf("  String %s with length %ld\n", record, strlen(record));
        if (strlen(record) == (size_t)next_size) {
            if (sizes.num_of_sizes == 1) {
                //puts("RETURN 2");
                return 1;
            } else {
                return 0;
            }
        }

        if (record[next_size] == '.' || record[next_size] == '?') {
            sizes_struct new_sizes;
            new_sizes.size_array = &(sizes.size_array[1]);
            new_sizes.num_of_sizes = sizes.num_of_sizes - 1;

            return calculate_combinations(memory, &record[next_size + 1], new_sizes);
        }

        return 0;
    }

char *hash_calculate_combinations_parameters(char *record, sizes_struct sizes) {
    char *string_sizes = malloc((sizes.num_of_sizes * 10 + 1) * sizeof(char));
    string_sizes[0] = '\0';

    for (size_t i = 0; i < (size_t)sizes.num_of_sizes; i++) {
        char *new_char = malloc(10 * sizeof(char));
        new_char[0] = '\0';

        sprintf(new_char, "%d", sizes.size_array[i]);

        strcat(string_sizes, new_char);
        free(new_char);
    }

    //printf("Allocating %ld\n", strlen(record) + strlen(string_sizes) + 2);

    //printf("%s%s\n", record, string_sizes);
    char *hashed_parameters = malloc((strlen(record) + strlen(string_sizes) + 2) * sizeof(char));
    hashed_parameters[0] = '\0';

    strcat(hashed_parameters, record);
    strcat(hashed_parameters, string_sizes);
    free(string_sizes);

    return hashed_parameters;
}

long long calculate_combinations(hashmap *memory ,char *record, sizes_struct sizes) {
    char *hashed_parameters = hash_calculate_combinations_parameters(record, sizes);

    //printf("%s\n", hashed_parameters);

    uintptr_t precalculated_value;
    if (hashmap_get(memory, strdup(hashed_parameters), strlen(hashed_parameters), &precalculated_value))
    {
        //puts("CACHED");
	    return (long long)precalculated_value;
    }

    //printf("  Current char %c\n", record[0]);

    //printf("-> %d\n", sizes.num_of_sizes);
    for (size_t i = 0; i < (size_t)sizes.num_of_sizes; i++) {
        //printf("%d,", sizes.size_array[i]);
    }
    //puts("");

    if (sizes.num_of_sizes == 0) {
        //puts("NO SIZES");
        if (strstr(record, "#") == NULL) {
            //puts("RETURN 1");
            hashmap_set(memory, strdup(hashed_parameters), strlen(hashed_parameters), 1);
            return 1;
        } else {
            hashmap_set(memory, strdup(hashed_parameters), strlen(hashed_parameters), 0);
            return 0;
        }
    }

    if (strcmp(record, "") == 0) {
        //puts("WHAT");
        hashmap_set(memory, strdup(hashed_parameters), strlen(hashed_parameters), 0);
        return 0;
    }

    char next_char = record[0];

    long long out = 0;
    if (next_char == '.') {
        //puts("  Skipping");
        out = calculate_combinations(memory, &record[1], sizes);
    } else if (next_char == '#') {
        out = pound(memory, record, sizes);
    } else if (next_char == '?') {
        //puts("  with ? as #");
        long long part_2 = calculate_combinations(memory, &record[1], sizes);

        long long part_1 = pound(memory, record, sizes);

        //puts("  with ? as .");

        out = part_1 + part_2;
    }

    hashmap_set(memory, strdup(hashed_parameters), strlen(hashed_parameters), out);
    //printf("%lld\n", out);
    return out;
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


    long long sum_of_all_combinations = 0;
    for (size_t i = 0; i < lines; i++) {
        char *record_once = strtok(input_lines[i], " ");
        char *record = malloc((5 * strlen(record_once) + 5) * sizeof(char));
        record[0] = '\0';

        for (size_t j = 0; j < 5; j++) {
            strcat(record, record_once);

            if (j != 4) {
                strcat(record, "?");
            }
        }

        char *sizes_string = strtok(NULL, "");

        long long num_of_sizes = 1;
        for (size_t j = 0; j < strlen(sizes_string); j++) {
            if (sizes_string[j] == ',') {
                num_of_sizes++;
            }
        }

        sizes_struct sizes;
        sizes.size_array = malloc(5 * num_of_sizes * sizeof(int));
        sizes.num_of_sizes = 5 * num_of_sizes;

        char *size_buffer = strtok(sizes_string, ",");
        long long size_index = 0;
        while(size_buffer != NULL) {
            sizes.size_array[size_index++] = strtol(size_buffer, NULL, 10);
            size_buffer = strtok(NULL, ",");
        }

        long long size_array_offset = num_of_sizes;
        for (size_t j = 0; j < 4; j++) {
            for (size_t k = 0; k < (size_t)num_of_sizes; k++) {
                sizes.size_array[k + size_array_offset] = sizes.size_array[k];
            }

            size_array_offset += num_of_sizes;
        }

        printf("%ld\n", i+1);
        //printf("%s\n", record);

        for (size_t j = 0; j < (size_t)sizes.num_of_sizes; j++) {
            //printf("%d,", sizes.size_array[j]);
        }

        //puts("");

        hashmap* memory = hashmap_create();

        long long total = calculate_combinations(memory, record, sizes);

        hashmap_free(memory);

        printf("Total %lld\n", total);

        sum_of_all_combinations += total;

        printf("Accumulative %lld\n", sum_of_all_combinations);

        free(sizes.size_array);
        free(record);
    }

    printf("Sum of all combinations: %lld\n", sum_of_all_combinations);
}
