#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/c-hashmap/map.h"

#define UNUSED(var) (void)(var)

typedef struct {
    char *node_left;
    char *node_right;
} node;

void free_node(void *key, size_t key_size, uintptr_t value_ptr, void *user_ptr) {
    UNUSED(key);
    UNUSED(key_size);
    UNUSED(user_ptr);

    free((node *)value_ptr);
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

    hashmap* nodes = hashmap_create();

    for (size_t i = 2; i < lines; i++) {
        char node_value[] = {input_lines[i][0], input_lines[i][1], input_lines[i][2], '\0'};
        char node_left[] = {input_lines[i][7], input_lines[i][8], input_lines[i][9], '\0'};
        char node_right[] = {input_lines[i][12], input_lines[i][13], input_lines[i][14], '\0'};

        node *new_node = malloc(sizeof(node));

        new_node->node_left = strdup(node_left);
        new_node->node_right = strdup(node_right);

        hashmap_set(nodes, strdup(node_value), strlen(node_value), (uintptr_t)new_node);

        printf("New node %s = (%s, %s)\n", node_value, node_left, node_right);
    }

    int num_of_steps = 0;
    char *current_element = "AAA";

    while (strcmp(current_element, "ZZZ") != 0) {
        puts("Starting routing:");

        for (size_t i = 0; i < strlen(input_lines[0]); i++) {
            uintptr_t current_node_ptr;

            hashmap_get(nodes, current_element, strlen(current_element), &current_node_ptr);

            printf("Going to node %s\n", ((node *)current_node_ptr)->node_left);

            if (input_lines[0][i] == 'L') {
                current_element = ((node *)current_node_ptr)->node_left;
            } else {
                current_element = ((node *)current_node_ptr)->node_right;
            }

            num_of_steps++;
        }
    }

    printf("Number of steps: %d\n", num_of_steps);

    hashmap_iterate(nodes, free_node, NULL);
}
