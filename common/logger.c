#include <stdio.h>

#define FMT(STYLE) ANSI_ESC "[" STYLE "m"
#define WITH ";"
#define ANSI_ESC "\x1b"
#define RESET "0"
#define BOLD "1"
#define FG "3"
#define GREEN "2"
#define YELLOW "3"
#define BLUE "4"
#define RED "1"

void info_print(char day[], char part[],char message[]) {
    printf("[ " FMT(BOLD WITH FG GREEN) "INFO" FMT(RESET) " ] [ DAY: " FMT(BOLD WITH FG YELLOW) "%s" FMT(RESET) " ] [ PART: " FMT(BOLD WITH FG BLUE) "%s" FMT(RESET) " ] %s\n", day, part, message);
}

void error_print(char day[], char part[],char message[]) {
    printf("[ " FMT(BOLD WITH FG RED) "ERROR" FMT(RESET) " ] [ DAY: " FMT(BOLD WITH FG YELLOW) "%s" FMT(RESET) " ] [ PART: " FMT(BOLD WITH FG BLUE) "%s" FMT(RESET) " ] %s\n", day, part, message);
}
