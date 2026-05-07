#include <stdio.h>
#include <string.h>
#include "baseball.h"

int is_pa_end(const char *outcome){
        if(strcmp(outcome,"Ball") == 0 || strcmp(outcome,"Swinging Strike") == 0 || strcmp(outcome,"Called Strike") == 0 ||strcmp(outcome,"Foul") == 0){
            return 0;
        }
        return 1;
}

int popcount(int runners){
    return ((runners >> 2) & 1) + ((runners >> 1) & 1) + (runners & 1);
}

int build_plate_appearance(struct pitch *pitches, int pitch_count, struct plateAppearance *pas, int max_pas){
    int pa_count = 0;

    int pa_runners = pitches[0].runners;
    int pa_outs = pitches[0].outs;
    int pa_innings = pitches[0].inning;
    char pa_batter[50];
    strncpy(pa_batter,pitches[0].batter,49);

    for(int i = 0; i < pitch_count; i++){
        if(is_pa_end(pitches[i].outcome)){
            if(pa_count >= max_pas){
                break;
            }
            int outs_after = 0;
            int runners_after = 0;

            if(i + 1 < pitch_count){
                outs_after = pitches[i + 1].outs;
                runners_after = pitches[i + 1].runners;
            }

            int delta_outs = (i + 1 < pitch_count && outs_after >= pa_outs)
                            ? outs_after - pa_outs
                            : 3 - pa_outs;
            int runs_scored = popcount(pa_runners) + 1 - popcount(runners_after) - delta_outs;
            pas[pa_count].outs_before = pa_outs;
            pas[pa_count].runners_before = pa_runners;
            pas[pa_count].outs_after = outs_after;
            pas[pa_count].runners_after = runners_after;
            pas[pa_count].runs_scored = runs_scored;
            strncpy(pas[pa_count].batter, pa_batter,49);

            if(i + 1 < pitch_count){
                pa_runners = pitches[i + 1].runners;
                pa_outs = pitches[i + 1].outs;
                pa_innings = pitches[i + 1].inning;
                strncpy(pa_batter,pitches[i + 1].batter,49);
            }
            pa_count++;

            
        }

    }
    return pa_count;
}