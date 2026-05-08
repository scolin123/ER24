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

int parse_csv(const char *filename, struct pitch *pitches, int max_pitches);
int build_plate_appearance(struct pitch *pitches, int pitch_count, struct plateAppearance *pas, int max_pas);
int popcount(int runners);
void compute_re24(struct plateAppearance *pas, int pa_count, double re_totals[3][8], int re_counts[3][8]);
void write_re24(double re_totals[3][8], int re_counts[3][8], const char *filename);


#endif