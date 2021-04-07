#include <stdio.h>

typedef struct {
    int st;
    int en;
} Time;

int N;
Time t[500005];
Time tmp[500005];

void merge(int l, int m, int r) {
    int idx = l;
    int i1 = l, i2 = m + 1;
    while (idx <= r) {
        // 둘중 하나를 모두 배치했을 때, 남은 하나를 마저 배치해줘야 한다.
        if (i1 > m) // l ~ m 배열을 모두 배치했다면
            tmp[idx++] = t[i2++];
        else if (i2 > r) // m + 1 ~ r 배열을 모두 배치했다면
            tmp[idx++] = t[i1++];
        // 둘 다 배치가 아직 안됐을 경우
        else if (t[i1].en == t[i2].en) {
            if (t[i1].st <= t[i2].st)
                tmp[idx++] = t[i1++];
            else
                tmp[idx++] = t[i2++];
        }
        else if (t[i1].en < t[i2].en) // l ~ m 배열의 다음 원소가 더 작다면 먼저 배치
            tmp[idx++] = t[i1++];
        else // m + 1 ~ r 배열의 다음 원소가 더 작다면 먼저 배치
            tmp[idx++] = t[i2++];
    }
    for (int i = l; i <= r; i++)
        t[i] = tmp[i];
}

void mergeSort(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) / 2;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int getCheckCnt() {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        // 더 늦게 나가는 사람이 더 먼저 왔으면 겹침.
        int j = i;
        while (j < N && t[j].st <= t[i].en)
            j++;
        i = j - 1;
        cnt++;
    }
    return cnt;
}

int main(void) {
    scanf(" %d", &N);
    for (int i = 0; i < N; i++)
        scanf(" %d %d", &t[i].st, &t[i].en);
    mergeSort(0, N - 1);
    printf("%d", getCheckCnt());
    return 0;
}