#include <stdio.h>
#define MX      1500005

int N;
int h[MX];
int dist[MX];

int s[MX];
int pos = 0;

void push(int x) {
    s[pos++] = x;
}

void pop() {
    pos--;
}

int top() {
    return s[pos - 1];
}

int isEmpty() {
    return pos == 0;
}

int isFull() {
    return pos == MX;
}

int main(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
        while (!isEmpty() && h[i] > h[top()]) {
            dist[top()] = i - top();
            pop();
        }
        push(i);
    }
    for (int i = 0; i < N; i++) {
        if (dist[i] == 0)
            dist[i] = N - i;
    }
    for (int i = 0; i < N; i++)
        printf("%d ", dist[i]);
    return 0;
}