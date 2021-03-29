#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int first;
    int second;
} Rec;

int N;
Rec record[2501][13][32];
int acc;
int mx_y = 1900, mx_m = 1, mx_d = 1;
int mx;

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void update(int y, int m, int d) {
    if (acc < 0)
        swap(&record[y][m][d].first, &record[y][m][d].second);
    acc += record[y][m][d].first;
    if (abs(acc) > mx) {
        mx = abs(acc);
        mx_y = y;
        mx_m = m;
        mx_d = d;
    }
    acc += record[y][m][d].second;
    if (abs(acc) > mx) {
        mx = abs(acc);
        mx_y = y;
        mx_m = m;
        mx_d = d;
    }
}

int main(void) {
    scanf(" %d", &N);
    int y, m, d, gf, ga;
    int dif;
    for (int i = 0; i < N; i++) {
        scanf(" %d %d %d %d %d", &y, &m, &d, &gf, &ga);
        dif = gf - ga;
        if (dif >= 0) 
            record[y][m][d].first += dif;
        else
            record[y][m][d].second += dif;
    }
    
    for (y = 1900; y <= 2500; y++) {
        for (m = 1; m <= 12; m++) {
            for (d = 1; d <= 31; d++) {
                update(y, m, d);
            }
        }
    }
    printf("%d %d %d %d", mx_y, mx_m, mx_d, mx);
    return 0;
}