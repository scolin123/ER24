#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "baseball.h"

int main(void){
    static struct pitch pitches[20000];


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

    static struct plateAppearance pas[3000];
    int pa_count = build_plate_appearance(pitches, pitch_count, pas, 3000);

    



    double re_totals[3][8];
    int re_counts[3][8];

    compute_re24(pas, pa_count, re_totals, re_counts);
    write_re24(re_totals, re_counts, "outputs/re24.csv");

    write_pas(pas, pa_count, "outputs/pas.csv");

    return 0;
}