#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {FIND = 1, HIGHER, LOWER};

typedef struct {
    char q;
    char major;
    char semester;
    char credits;
    char grad_req;
    int tsa;
    int idx;
} Query;

int N, M;
char* major;
char* semester;
char* credits;
char* grad_req;
int* tsa;
Query* query;
int* res;
int cnt1[7][11][19][3];
int cnt2[7][11][19][3];

int compare(const void* a, const void* b) {
    Query s1 = *(Query*)a;
    Query s2 = *(Query*)b;

    if (s1.tsa < s2.tsa) return -1;
    if (s1.tsa > s2.tsa) return 1;
    // 같은 tsa라면 HIGHER먼저
    if (s1.q == HIGHER) return -1;
    if (s2.q == HIGHER) return 1;
    return 0;
}

void counting(int cnt[7][11][19][3], char a, char b, char c, char d) {
    cnt[0][0][0][0]++; // 0000
    cnt[0][0][0][d]++; // 0001
    cnt[0][0][c][0]++; // 0010
    cnt[0][0][c][d]++; // 0011
    cnt[0][b][0][0]++; // 0100
    cnt[0][b][0][d]++; // 0101
    cnt[0][b][c][0]++; // 0110
    cnt[0][b][c][d]++; // 0111
    cnt[a][0][0][0]++; // 1000
    cnt[a][0][0][d]++; // 1001
    cnt[a][0][c][0]++; // 1010
    cnt[a][0][c][d]++; // 1011
    cnt[a][b][0][0]++; // 1100
    cnt[a][b][0][d]++; // 1101
    cnt[a][b][c][0]++; // 1110
    cnt[a][b][c][d]++; // 1111
}

void print() {
    for (int i = 0; i < M; i++)
        printf("%d\n", res[i]);
}

int main(void) {
    scanf("%d", &N);
    major = (char*)malloc(sizeof(char) * N);
    semester = (char*)malloc(sizeof(char) * N);
    credits = (char*)malloc(sizeof(char) * N);
    grad_req = (char*)malloc(sizeof(char) * N);
    tsa = (int*)malloc(sizeof(int) * N); // 입력이 오름차순이므로 정렬 필요없다

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &major[i], &semester[i], &credits[i], &grad_req[i], &tsa[i]);
        grad_req[i] = (grad_req[i] >= 3) ? 1 : 2;
        counting(cnt1, major[i], semester[i], credits[i], grad_req[i]);
    }
    scanf("%d", &M);
    query = (Query*)malloc(sizeof(Query) * M);
    res = (int*)malloc(sizeof(int) * M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d %d %d", &query[i].q, &query[i].major, &query[i].semester, &query[i].credits, &query[i].grad_req, &query[i].tsa);
        query[i].idx = i;
    }
    qsort(query, M, sizeof(Query), compare); // 쿼리를 tsa 기준 오름차순으로 정렬
    
    int idx = 0;
    int before, is_found;
    for (int idx_q = 0; idx_q < M; idx_q++) {
        // 이번 쿼리의 tsa보다 더 tsa가 작은 학생까지 카운팅
        while (idx < N && tsa[idx] < query[idx_q].tsa) {
            counting(cnt2, major[idx], semester[idx], credits[idx], grad_req[idx]);
            idx++;
        }
        if (query[idx_q].q == HIGHER) {
            res[query[idx_q].idx] = cnt1[query[idx_q].major][query[idx_q].semester][query[idx_q].credits][query[idx_q].grad_req]
                                    - cnt2[query[idx_q].major][query[idx_q].semester][query[idx_q].credits][query[idx_q].grad_req];
            continue;
        }
        before = cnt2[query[idx_q].major][query[idx_q].semester][query[idx_q].credits][query[idx_q].grad_req];
        is_found = 0;
        // FIND나 LOWER라면 같은경우까지 카운팅
        while (idx < N && tsa[idx] == query[idx_q].tsa) {
            counting(cnt2, major[idx], semester[idx], credits[idx], grad_req[idx]);
            if (cnt2[query[idx_q].major][query[idx_q].semester][query[idx_q].credits][query[idx_q].grad_req] != before)
                is_found = 1;
            idx++;
        }
        switch (query[idx_q].q) {
        case FIND:
            res[query[idx_q].idx] = is_found;
            break;
        case LOWER:
            res[query[idx_q].idx] = cnt2[query[idx_q].major][query[idx_q].semester][query[idx_q].credits][query[idx_q].grad_req];
        }
    }

    print();
    return 0;
}