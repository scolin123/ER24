#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseball.h"

int main(void){
    struct pitch pitches[500];

    int count = parse_csv("data/2025 Guelph Royals Analytics - May 11 - Kitchener vs. Toronto.csv", pitches, 500);
    printf("%s\n",pitches[21].batter);
    printf("%d\n",pitches[21].runners);

    struct plateAppearance pas[200];
    build_plate_appearance(pitches,count,pas,200);

    for(int i = 0; i < 5; i++){
        printf("%s\n",pas[i].batter);
        printf("%d\n",pas[i].runs_scored);
    }

    return 0;
}