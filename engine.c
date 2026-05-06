#include <stdio.h>
#include "baseball.h"

int is_pa_end(const char *outcome){
        if(strcmp(outcome,"Ball") == 0 || strcmp(outcome,"Swinging Strike") == 0 || strcmp(outcome,"Called Strike") == 0 ||strcmp(outcome,"Foul") == 0){
            return 0;
        }
        return 1;
}