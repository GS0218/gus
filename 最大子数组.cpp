#include <iostream>
#include<vector>
#include<stdio.h>
using namespace std;
int Maxarry() {
    vector<int> a;
    int i = 0, k, sum, maxa, b;
    while (1) {
        cin >> b;
        a.push_back(b);
        i++;
        if (getchar() == '\n') {
            break;
        }
    }
    k = i - 1;
    sum = maxa = 0;
    for (i = 0; i <= k; i++) {
        sum += a[i];
        if (sum < 0)               //小于0，拖累，丢弃
            sum = 0;              //相当于设置起点
        if (sum > maxa)
            maxa = sum;
    }
    printf("%d\n", maxa);
    return 1;
}
int main()
{
    Maxarry();
    return 0;
}