#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    FILE *input_file;

    if ((input_file = fopen("input.txt", "r")) == NULL) {
        printf("File could not be opened\n");
        return 1;
    }

    char current_char;
    int lines = 0;

    while ( current_char != EOF ) {
        if ( current_char == '\n' ) {
            lines++;
        }
        current_char = getc(input_file);
    }

    rewind(input_file);

    
    char *bad_calibration_values[lines];

    for (int i = 0; i < lines; i++) {
        bad_calibration_values[i] = NULL;
        size_t line_buffer_size = 0;
        
        getline(&bad_calibration_values[i], &line_buffer_size, input_file);
    }

    fclose(input_file);

    int final_calibration_value = 0;

    for (int i = 0; i < sizeof(bad_calibration_values)/sizeof(bad_calibration_values[0]); i++) {
        int value_length = strlen(bad_calibration_values[i]);
        char first_digit;
        char last_digit;

        for (int j = 0; j < value_length; j++) {
            if (isdigit(bad_calibration_values[i][j])) {
                first_digit = bad_calibration_values[i][j];
                break;
            }
        }

        for (int j = value_length; j >= 0; j--) {
            if (isdigit(bad_calibration_values[i][j])) {
                last_digit = bad_calibration_values[i][j];
                break;
            }
        }

        char fixed_calibration_value[] = {first_digit, last_digit, '\0'};
        final_calibration_value += strtol(fixed_calibration_value, NULL, 10);
    }

    printf("%d\n", final_calibration_value);

    return 0;
}
