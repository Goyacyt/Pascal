#include<stdio.h>

int display(int chess2[16]) {
    int chessplate[4][4];
    int i2 = 0, j2 = 0;
    while (i2 < 4) {
        j2 = 0;
        while (j2 < 4) {
            chessplate[i2][j2] = chess2[i2 * 4 + j2];
            j2 = j2 + 1;
        }
        i2 = i2 + 1;
    }
    i2 = 0;
    j2 = 0;
    while (i2 < 4) {
        j2 = 0;
        while (j2 < 4) {
            if (chessplate[i2][j2] == 1) printf("%d\n",j2);
            j2 = j2 + 1;
        }
        i2 = i2 + 1;
    }
    return 0;
}
int PutQueen(int chess[16], int a[4], int b[7], int c[7], int n, int sum) {
    int col, i, j;
    col = 0;
    while (col < 4) {
        if (a[col] && b[n + col] && c[n - col + 3]) {
            chess[n * 4 + col] = 1;
            a[col] = 0;
            b[n + col] = 0;
            c[n - col + 3] = 0;
            if (n == 3) {
                sum = sum + 1;
                display(chess);
            } else
                sum = PutQueen(chess, a, b, c, n + 1, sum);
            chess[n * 4 + col] = 0;
            b[n + col] = 1;
            c[n - col + 3] = 1;
            a[col] = 1;
        }
        col = col + 1;
    }
    return sum;
}

int main() {
    int chess1[16];
    int a1[4], b1[7], c1[7];
    int sum1 = 0;
    int i1;
    i1 = 0;
    while (i1 < 16) {
        chess1[i1] = 0;
        i1 = i1 + 1;
    }
    i1 = 0;
    while (i1 < 4) {
        a1[i1] = 1;
        i1 = i1 + 1;
    }
    i1 = 0;
    while (i1 < 7) {
        b1[i1] = 1;
        c1[i1] = 1;
        i1 = i1 + 1;
    }
    sum1 = PutQueen(chess1, a1, b1, c1, 0, sum1);
    printf("%d\n",sum1);
    return 0;
}