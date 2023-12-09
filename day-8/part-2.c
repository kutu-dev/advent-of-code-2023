#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/c-hashmap/map.h"

#define UNUSED(var) (void)(var)

typedef struct {
    char *node_left;
    char *node_right;
} node;

long long gcd(long long int num_1, long long int num_2){        
    if(num_2==0)
        return num_1;
    return gcd(num_2,num_1%num_2);
}


long long lcm(long long num_1,long long num_2){     
    if(num_1>num_2)
        return (num_1/gcd(num_1,num_2))*num_2;
    else
        return (num_2/gcd(num_1,num_2))*num_1;    
} 

int calculate_steps(hashmap *nodes, char *starting_node, char *instructions) {
    int num_of_steps = 0;
    char *current_element = starting_node;

    while (strstr(current_element, "Z") == NULL) {
        puts("Starting routing:");

        for (size_t i = 0; i < strlen(instructions); i++) {
            uintptr_t current_node_ptr;

            hashmap_get(nodes, current_element, strlen(current_element), &current_node_ptr);

            printf("Going to node %s\n", ((node *)current_node_ptr)->node_left);

            if (instructions[i] == 'L') {
                current_element = ((node *)current_node_ptr)->node_left;
            } else {
                current_element = ((node *)current_node_ptr)->node_right;
            }

            num_of_steps++;
        }
    }

    return num_of_steps;
}

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

    int num_of_a_nodes = 0;

    for (size_t i = 0; i < lines; i++)
    {
        input_lines[i] = NULL;
        size_t line_buffer_size = 0;

        getline(&input_lines[i], &line_buffer_size, input_file);

        if (strstr(input_lines[i], "A") == 0) {
            num_of_a_nodes++;
        }

        input_lines[i][strcspn(input_lines[i], "\r\n")] = 0;
    }

    hashmap* nodes = hashmap_create();

    char **a_nodes = malloc(num_of_a_nodes * sizeof(char));
    int a_index = 0;

    for (size_t i = 2; i < lines; i++) {
        char node_value[] = {input_lines[i][0], input_lines[i][1], input_lines[i][2], '\0'};
        char node_left[] = {input_lines[i][7], input_lines[i][8], input_lines[i][9], '\0'};
        char node_right[] = {input_lines[i][12], input_lines[i][13], input_lines[i][14], '\0'};

        if (strstr(node_value, "A") != NULL) {
            a_nodes[a_index] = strdup(node_value);
            a_index++;
        }

        node *new_node = malloc(sizeof(node));

        new_node->node_left = strdup(node_left);
        new_node->node_right = strdup(node_right);

        hashmap_set(nodes, strdup(node_value), strlen(node_value), (uintptr_t)new_node);

        printf("New node %s = (%s, %s)\n", node_value, node_left, node_right);
    }

    int *step_array = malloc(num_of_a_nodes * sizeof(int));
    int step_array_index = 0;

    for (size_t i = 0; i < (size_t)a_index; i++) {
        printf("Calculating steps for node %s:\n", a_nodes[i]);

        int num_of_steps = calculate_steps(nodes, a_nodes[i], input_lines[0]);

        step_array[step_array_index] = num_of_steps;
        step_array_index++;
        printf("Steps for node: %d\n", num_of_steps);
    }

    puts("Calculating LCM:");

    long long lcm_number = lcm(step_array[0], step_array[1]);

    for (size_t i = 2; i < (size_t)step_array_index; i++) {
        lcm_number = lcm(lcm_number, step_array[i]);
    }

    printf("Number of steps: %lld\n", lcm_number);

    hashmap_iterate(nodes, free_node, NULL);
    free(a_nodes);
    free(step_array);
}
