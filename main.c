#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseball.h"

int main(void){
    struct pitch pitches[500];

    parse_csv("data/2025 Guelph Royals Analytics - May 11 - Kitchener vs. Toronto.csv", pitches, 500);
    printf("%s\n",pitches[21].batter);
    printf("%d\n",pitches[21].runners);
    return 0;
}