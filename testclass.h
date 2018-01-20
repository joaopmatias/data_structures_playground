#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class myclass
{
public:
    int nr;
    char digit;

    myclass();

    void setnr(int n);
    myclass addone();
    void setdigit(char c);
    bool operator == ( myclass obj);
    bool match();
    void myprint();
};

myclass::myclass() {}

void myclass::setnr(int n){
    nr = n;
}

void myclass::setdigit(char c){
    digit = c;
}

bool myclass::operator== ( myclass obj){
    return nr == obj.nr && digit == obj.digit;
}

bool myclass::match(){
    return nr == int(digit) - int('0');
}

void myclass::myprint(){
    cout << nr << " " << digit << endl;
}

myclass myclass::addone(){
    myclass ans;
    ans.setnr(nr + 1);
    ans.setdigit(digit);
    return ans;
}