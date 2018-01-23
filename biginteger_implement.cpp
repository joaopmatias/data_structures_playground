#include "biginteger.h"

int main(){
    int i, N;
    bigint ans(1);
    cin >> N;
    for(i = 1; i <= N; i++) ans = ans * (bigint(i));
    ans.printB();
    return 0;
}