#include "biginteger.h"

int main(){
    int i, M, N;
    bigint ans(1);
    cin >> N >> M;
    //for(i = 1; i <= N; i++) ans = ans * (bigint(i));
    ans = bigint(N);
    ans.printB();
    cout << endl;
    (ans%bigint(M)).printB();
    cout << endl;
    return 0;
}