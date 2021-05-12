#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MX      1000005

typedef long long   ll;

typedef struct _Node {
    int dat;
    struct _Node* next;
} Node;

typedef struct {
    Node* head;
} List;

int N;
int s[MX];
ll sum;
List child[MX];
ll dp[MX];
int visited[MX];
ll mn = 0x7f7f7f7f7f7f7f7f;

void init() {
    for (int i = 0; i < MX; i++) {
        child[i].head = (Node*)malloc(sizeof(Node));
        child[i].head->next = NULL;
    }
}

void insert(List* l, int dat) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dat = dat;
    newNode->next = l->head->next;
    l->head->next = newNode;
}

void cal(int root) {
    ll subtree_sum = s[root];
    for (Node* c = child[root].head->next; c != NULL; c = c->next) {
        if (visited[c->dat])
            continue;
        visited[c->dat] = 1;
        cal(c->dat);
        subtree_sum += dp[c->dat];
    }
    dp[root] = subtree_sum;
}

int main(void) {
    init();
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &s[i]);
        sum += s[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        insert(&child[a], b);
        insert(&child[b], a);
    }
    visited[1] = 1;
    cal(1);
    for (int i = 2; i <= N; i++) {
        ll tmp = llabs(sum - dp[i] - dp[i]);
        mn = (tmp < mn) ? tmp : mn;
    }
    printf("%lld", mn);
    return 0;
}