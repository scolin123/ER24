#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "baseball.h"

int main(void){
    struct pitch pitches[20000];


    DIR *d = opendir("data/");
    if(d == NULL){
        return -1;
    }
    int pitch_count = 0;
    struct dirent *entry;
    while((entry = readdir(d)) != NULL){
        if(entry->d_name[0] =='.'){
            continue;
        }
        char filepath[512];
        snprintf(filepath,sizeof(filepath),"data/%s",entry->d_name);
        int n = parse_csv(filepath,pitches + pitch_count, 20000 - pitch_count);
        if(n > 0){
            pitch_count += n;
        }
    }
    closedir(d);
    printf("Total pitches: %d\n",pitch_count);

    struct plateAppearance pas[2000];
    build_plate_appearance(pitches,pitch_count,pas,2000);

    for(int i = 0; i < 5; i++){
        printf("%s\n",pas[i].batter);
        printf("%d\n",pas[i].runs_scored);
    }

    return 0;
}