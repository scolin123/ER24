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

int find_col(char **fields, int count, const char *name){
    for(int i = 0; i <= count; i++){
        if(fields[i] != NULL && strcmp(fields[i], name) == 0) return i;
    }
    return -1;
}

int parse_csv(const char *filename, struct pitch *pitches, int max_pitches){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        return -1;
    }

    char header[1024];
    char buffer[1024];
    int pitch_count = 0;

    if(!fgets(header, sizeof(header), fp)){
        fclose(fp);
        return -1;
    }

    char *hfields[30];
    int hcount = split_csv_line(header, hfields, 30);

    /* strip trailing newline from last header field */
    for(int i = 0; i <= hcount; i++){
        if(hfields[i]){
            int len = strlen(hfields[i]);
            while(len > 0 && (hfields[i][len-1] == '\n' || hfields[i][len-1] == '\r'))
                hfields[i][--len] = '\0';
        }
    }

    int col_batter  = find_col(hfields, hcount, "Batter");
    int col_outcome = find_col(hfields, hcount, "Outcome");
    int col_runners = find_col(hfields, hcount, "Runners");

    if(col_batter < 0 || col_outcome < 0 || col_runners < 0){
        fclose(fp);
        return -1;
    }

    int min_fields = col_batter;
    if(col_outcome > min_fields) min_fields = col_outcome;
    if(col_runners > min_fields) min_fields = col_runners;

    while(fgets(buffer,sizeof(buffer),fp) != NULL){
        if(pitch_count >= max_pitches){
            break;
        }

        char *fields[30];

        int field_count = split_csv_line(buffer, fields, 30);
        if(field_count < min_fields){
            continue;
        }

        char *r = fields[col_runners];
        if(r == NULL || strlen(r) < 3) continue;
        if((r[0] != '0' && r[0] != '1') || (r[1] != '0' && r[1] != '1') || (r[2] != '0' && r[2] != '1')) continue;

        strncpy(pitches[pitch_count].half,fields[0],3);
        pitches[pitch_count].half[3] = '\0';
        pitches[pitch_count].inning = atoi(fields[1]);
        pitches[pitch_count].outs = atoi(fields[2]);
        strncpy(pitches[pitch_count].batter,fields[col_batter],49);
        pitches[pitch_count].batter[49] = '\0';
        strncpy(pitches[pitch_count].outcome,fields[col_outcome],49);
        pitches[pitch_count].outcome[49] = '\0';
        pitches[pitch_count].runners = ((r[0] - '0') * 4) + ((r[1] - '0') * 2) + ((r[2] - '0') * 1);

        pitch_count++;
    }

    fclose(fp);
    return pitch_count;
}

