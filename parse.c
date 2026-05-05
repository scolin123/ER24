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
            fields[count] = &line[i + 1];
            count++;
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
    }



}

