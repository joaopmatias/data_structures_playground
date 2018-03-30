#include "testclass.h"

int main(){
    myclass example, another;
    example.setnr(7);
    example.setdigit('6');
    example.myprint();
    cout << example.match() << endl;
    another.setnr(7);
    another.setdigit('6');
    cout << (example == another.addone().addone()) << endl;
    another.addone().addone().myprint();
    return 0;
}