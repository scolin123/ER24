#ifndef BASEBALL_H
#define BASEBALL_H

struct pitch{
    char half[4];
    int inning;
    int outs;
    int runners;
    char batter[50];
    char outcome[50];
};

struct plateAppearance{
    char half[4];
    int innings;
    int outs_before;
    int runners_before;
    int outs_after;
    int runners_after;
    int runs_scored;
    char batter[50];
};



#endif