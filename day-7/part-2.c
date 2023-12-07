#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    char *cards;
    int type;
    int bid;
} hand;

hand create_hand(char *input_line)
{
    hand new_hand;

    new_hand.cards = strtok(input_line, " ");
    new_hand.bid = strtol(strtok(NULL, ""), NULL, 10);
    new_hand.type = 0;

    if (strcmp(new_hand.cards, "JJJJJ") == 0) {
        new_hand.type = 6;
        return new_hand;
    }

    int num_of_times_first_char = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (new_hand.cards[i] == new_hand.cards[0] || new_hand.cards[i] == 'J')
        {
            num_of_times_first_char++;
        }
    }

    if (new_hand.cards[0] == 'J') {
        num_of_times_first_char = 1;
    }

    int num_of_times_second_char = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (new_hand.cards[i] == new_hand.cards[1] || new_hand.cards[i] == 'J')
        {
            num_of_times_second_char++;
        }
    }

    if (new_hand.cards[1] == 'J') {
        num_of_times_second_char = 1;
    }

    int num_of_times_third_char = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (new_hand.cards[i] == new_hand.cards[2] || new_hand.cards[i] == 'J')
        {
            num_of_times_third_char++;
        }
    }

    if (new_hand.cards[2] == 'J') {
        num_of_times_third_char = 1;
    }

    int num_of_times_fourth_char = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (new_hand.cards[i] == new_hand.cards[3] || new_hand.cards[i] == 'J')
        {
            num_of_times_fourth_char++;
        }
    }

    if (new_hand.cards[3] == 'J') {
        num_of_times_fourth_char = 1;
    }

    int num_of_times_fifth_char = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (new_hand.cards[i] == new_hand.cards[4] || new_hand.cards[i] == 'J')
        {
            num_of_times_fifth_char++;
        }
    }

    if (new_hand.cards[4] == 'J') {
        num_of_times_fifth_char = 1;
    }

    if (num_of_times_first_char == 5 || num_of_times_second_char == 5 || num_of_times_third_char == 5 || num_of_times_fourth_char == 5 || num_of_times_fifth_char == 5)
    {
        new_hand.type = 6;
        return new_hand;
    }
    else if (num_of_times_first_char == 4 || num_of_times_second_char == 4 || num_of_times_third_char == 4 || num_of_times_fourth_char == 4 || num_of_times_fifth_char == 4)
    {
        new_hand.type = 5;
        return new_hand;
    }

    int sum_of_first_four_chars = num_of_times_first_char + num_of_times_second_char + num_of_times_third_char + num_of_times_fourth_char + num_of_times_fifth_char;

    if (sum_of_first_four_chars == 13 || sum_of_first_four_chars == 15)
    {
        new_hand.type = 4;
        return new_hand;
    }
    else if (sum_of_first_four_chars == 11 || sum_of_first_four_chars == 19)
    {
        new_hand.type = 3;
        return new_hand;
    }
    else if (sum_of_first_four_chars == 12) {
        new_hand.type = 2;
        return new_hand;
    }
    else if (sum_of_first_four_chars == 9 && !strstr(new_hand.cards, "J")) {
        new_hand.type = 2;
        return new_hand;
    }
    else if (sum_of_first_four_chars == 7) {
        new_hand.type = 1;
        return new_hand;
    } else if (sum_of_first_four_chars == 9) {
        new_hand.type = 1;
        return new_hand;
    }

    return new_hand;
}

int get_card_value(char card)
{
    if (isdigit(card))
    {
        return strtol(&card, NULL, 10);
    }

    switch (card)
    {
    case 'A':
        return 14;
        break;

    case 'K':
        return 13;
        break;

    case 'Q':
        return 12;
        break;

    case 'T':
        return 10;
        break;

    case 'J':
        return 1;
        break;
    }

    return 0;
}

int compare_hands(const void *hand_1_pointer, const void *hand_2_pointer)
{
    hand hand_1 = *(hand *)hand_1_pointer;
    hand hand_2 = *(hand *)hand_2_pointer;

    if (hand_1.type < hand_2.type)
    {
        return -1;
    }

    if (hand_1.type == hand_2.type)
    {
        for (size_t i = 0; i < 5; i++)
        {
            if (hand_1.cards[i] == hand_2.cards[i])
            {
                continue;
            }

            int current_card_value_1 = get_card_value(hand_1.cards[i]);
            int current_card_value_2 = get_card_value(hand_2.cards[i]);

            if (current_card_value_1 < current_card_value_2)
            {
                return -1;
            } else {
                return 1;
            }
        }
    }

    return 1;
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

    hand *hands = malloc(lines * sizeof(hand));

    for (size_t i = 0; i < lines; i++)
    {
        hands[i] = create_hand(input_lines[i]);
    }

    qsort(hands, lines, sizeof(hand), compare_hands);

    int total_winnings = 0;

    for (size_t i = 0; i < lines; i++)
    {
        printf("Hand: %s with bid %d, rank %ld and type %i\n", hands[i].cards, hands[i].bid, i + 1, hands[i].type);
        total_winnings += hands[i].bid * (i + 1);
    }

    printf("Total winnings: %d", total_winnings);

    free(hands);
    return 0;
}
