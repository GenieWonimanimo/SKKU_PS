#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N;
int dif[13][32];
int acc;
int mx_m = 1, mx_d = 1;
int mx;

int main(void) {
    scanf(" %d", &N);
    for (int i = 0; i < N; i++) {
        int m, d, gf, ga;
        scanf(" %d %d %d %d", &m, &d, &gf, &ga);
        dif[m][d] += gf - ga;
    }

    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= 31; j++) {
            acc += dif[i][j];
            if (abs(acc) > abs(mx)) {
                mx = acc;
                mx_m = i;
                mx_d = j;
            }
        }
    }
    printf("%d %d %d", mx_m, mx_d, mx);
    return 0;
}