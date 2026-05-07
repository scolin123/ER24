#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseball.h"

int split_csv_line(char *line, char **fields, int max_fields){
    int count = 0;
    int in_quotes = 0;
    fields[0] = line;
    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] == '"'){
            in_quotes = !in_quotes;
        }else if(line[i] == ',' && in_quotes == 0){
            line[i] = '\0';
            count++;
            fields[count] = &line[i + 1];
            
        }
    }
    return count;

}

int parse_csv(const char *filename, struct pitch *pitches, int max_pitches){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        return -1;
    }

    char buffer[1024];
    int pitch_count = 0;
    
    fgets(buffer,sizeof(buffer),fp);

    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        if(pitch_count >= max_pitches){
            break;
        }

        char *fields[30];
        split_csv_line(buffer,fields,30);
        
        strncpy(pitches[pitch_count].half,fields[0],3);
        pitches[pitch_count].half[3] = '\0';
        pitches[pitch_count].inning = atoi(fields[1]);
        pitches[pitch_count].outs = atoi(fields[2]);
        strncpy(pitches[pitch_count].batter,fields[13],49);
        pitches[pitch_count].batter[49] = '\0';
        strncpy(pitches[pitch_count].outcome,fields[18],49);
        pitches[pitch_count].outcome[49] = '\0';

        char *r = fields[21];
        pitches[pitch_count].runners = ((r[0] - '0') * 4) + ((r[1] - '0') * 2) + ((r[2] - '0') * 1);


        pitch_count++;
    }

    fclose(fp);
    return pitch_count;


}

