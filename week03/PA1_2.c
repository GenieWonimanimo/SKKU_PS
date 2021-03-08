#include <stdio.h>
#include <stdlib.h>
#define max(a, b)	a > b ? a : b;
#define MAXN (700000)

int N;
int brick_idx[MAXN + 1];
int visit[MAXN + 1];

int getSorted() {
	int sorted = 0;
	for (int i = 1; i <= N; i++) {
		if (visit[i] == 0) {
			int cnt = 1;
			int next = i + 1;
			visit[i] = 1;
			while (brick_idx[next] > brick_idx[next - 1]) {
				visit[next++] = 1;
				cnt++;
			}
			sorted = max(sorted, cnt);
		}
	}
	return sorted;
}

int main(void) {
	scanf(" %d", &N);
	for (int i = 1; i <= N; i++) {
		int brick_num;
		scanf(" %d", &brick_num);
		brick_idx[brick_num] = i;
	}
	printf("%d", N - getSorted());
	return 0;
}