#include "../common/c-hashmap/map.h"

typedef struct {
    int *size_array;
    int num_of_sizes;
} sizes_struct;

long long calculate_combinations(hashmap *memory ,char *record, sizes_struct sizes);
