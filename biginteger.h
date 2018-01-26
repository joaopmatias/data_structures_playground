#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int BASE = 1024; //at  most 1250 (beacuse we may need to cube in division)

class bigint {

public:

vector<int> digits;
int sign;
int length;

bigint(void);
bigint(int nr);
bigint(const bigint & obj) ;
~bigint();

//in order to simplify printing, all operations should have base as an argument which is BASE by default OR
//define multiplication twice
//define sumabsB twice, in both of these use only vectors, not bigint
void operator= (bigint);
void printB(int);
bigint symmB(void) ;
bigint absB(void) ;
bool operator== ( bigint );
bool isbiggerabsB ( bigint) ;
bigint sumabsB ( bigint ) ;
bigint diffabsB ( bigint ) ;
bool operator< ( bigint );
bool operator> ( bigint );
bigint operator+ ( bigint );
bigint operator- ( bigint );
bigint operator* ( bigint );

//TURN int INTO bigint
//FIX printB for any base

//operations
//plusB 1
//multB 2
//divideB 3
//intB 4
//Bstr 5

//don't forget print

}; 

//zero function
bigint zeroB(){
	bigint ans;
	vector<int> write_nr (1, 0);
	ans.digits = write_nr;
	ans.length = 0;
	ans.sign = 1;
	return ans;
}

//int to vector with base
vector<int> inttobase(int nr, int base){
	vector<int> ans;
	int t;
	ans.push_back(nr % base);
	t = nr / base;
	while(t > 0){
		ans.push_back(t % base);
		t /= base;
	}
	return ans;
}

//sumabs vectors with base
vector<int> sumbase(vector<int> digits1, vector<int> digits2, int base){
	int i, l1 = digits1.size(), l2 = digits2.size(), l = max(l1, l2);
	vector<int> write_nr (l + 1, 0);
	for (i = 0; i < l1; i++) {
		write_nr[i] = digits1[i];
	}
	for (i = 0; i < l2; i++) {
		write_nr[i] += digits2[i];
		if (write_nr[i] >= base) {
			write_nr[i] -= base;
			write_nr[i + 1]++;
		}
	}
	if (write_nr.back() == 0 ) write_nr.pop_back();
	
	return write_nr;
}

//multiplication vectors with base
vector<int> prodbase(vector<int> digits1, vector<int> digits2, int base){
	int l1 = digits1.size(), l2 = digits2.size();
	vector<int> write_nr (l1 + l2 + 1, 0);
	int i, j, k, l;
	l = write_nr.size() - 1;
	for (i = 0; i < l1; i++) {
		for (j = 0; j < l2; j++) {
			write_nr[i + j] += digits1[i] * digits2[j];
		}
		for (j = i; j < l; j++) {
			write_nr[i + 1] += (write_nr[i]/base);
			write_nr[i] = write_nr[i]%base;
		}
	}
	write_nr.pop_back();
	if (write_nr.back() == 0) write_nr.pop_back();
	return write_nr;	
}

//constructor
bigint::bigint(void) {
	digits.resize(1);
	digits[0] = 0;
	sign = 1;
	length = 0;
}

bigint::bigint(int nr) {
	digits = inttobase(abs(nr), BASE);
	sign = 1 - 2 * (nr < 0);
	length = 1 - (nr == 0);
}

bigint::bigint(const bigint & obj)  {
	length = obj.length;
	sign = obj.sign;
	digits = obj.digits;
}

bigint::~bigint() {}

//more operations: symm and overloading of other operators



void bigint::operator= (bigint test){
	length = test.length;
	sign = test.sign;
	digits = test.digits;
}


//prints
void bigint::printB(int base = 1000) {
	if (length == 0) cout << 0;
	int i;
	if(sign == -1) cout << '-';
	if(base == BASE){
		cout << digits.back();
		for (i = length - 2; i > -1; i--) {
			cout << '|';
			cout << digits[i];
		}
		return ;
	}
	vector<int> old_base, npow, ans, ii;
	old_base = inttobase(BASE, base);
	npow.push_back(1);
	ans = inttobase(digits[0], base);
	for(i = 1; i < length; i++){
		npow = prodbase(npow, old_base, base);
		ii = prodbase(npow, inttobase(digits[i], base), base);
		ans = sumbase(ans, ii, base);
	}
	cout << ans.back();
	if(base == 1000){
		for (i = ans.size() - 2; i > -1; i--) {
			printf("%03d", ans[i]);
		}
		return ;
	}
	else {
		for (i = ans.size() - 2; i > -1; i--) {
			cout << '|';
			cout << ans[i];
		}
		return ;
	}
}

bigint bigint::symmB()  {
	bigint ans(*this);
	if (length > 0) {
		ans.length *= -1;
	}
	return ans;
}

bigint bigint::absB()  {
	bigint ans(*this);
	ans.sign = 1;
	return ans;
}

bool bigint::operator== ( bigint test) {
	if (sign != test.sign) return false;
	else if (length	!= test.length) return false;
	else {
		int i;
		for (i = 0; i < length; i++) {
			if ( digits[i] != (test.digits)[i] ) return false;
		}
	}
	return true;	
}

// YOU MIGHT WANT TO REPLACE THE INTS IN THE "FOR LOOPS" BY ITERATORS
bool bigint::isbiggerabsB( bigint test)  {
	if (length == 0) return false;
	else if (length > test.length) return true;
	else if (length < test.length) return false;
	else {
		int i;
		for (i = length - 1; i >= 0; i--) {
			if ( digits[i] > (test.digits)[i] ) return true;
			else if ( digits[i] < (test.digits)[i] ) return false;
		}
	}
	return false;	
}

bool bigint::operator< ( bigint test) {
	if (sign < test.sign) return true;
	else if (sign > test.sign) return false;
	else return test.isbiggerabsB(*this);
}

bool bigint::operator> ( bigint test) {
	if (sign > test.sign) return true;
	else if (sign < test.sign) return false;
	else return (*this).isbiggerabsB(test);
}


//next operator: sum 

bigint bigint::sumabsB( bigint test)  {
	if (length == 0) return test.absB();
	else { //maybe use iterators
		int i, l = max(length, test.length);
		vector<int> write_nr (l + 1, 0);
		for (i = 0; i < length; i++) {
			write_nr[i] = digits[i];
		}
		for (i = 0; i < test.length; i++) {
			write_nr[i] += (test.digits)[i];
			if (write_nr[i] >= BASE) {
				write_nr[i] -= BASE;
				write_nr[i + 1]++;
			}
		}
		if (write_nr.back() == 0 ) write_nr.pop_back();
		
		bigint ans;
		ans.digits = write_nr;
		ans.sign = 1;
		ans.length = write_nr.size();
		return ans;
	}
}

bigint bigint::diffabsB( bigint test)  {//*this* is the largest in abs
	if (length == 0) return zeroB();
	else {
		int i, l = max(length, test.length); //it's length
		vector<int> write_nr (l, 0);
		for (i = 0; i < length; i++) {
			write_nr[i] = digits[i];
		}
		for (i = 0; i < test.length; i++) {
			write_nr[i] -= (test.digits)[i];
			if (write_nr[i] < 0) {
				write_nr[i] += BASE;
				write_nr[i + 1]--;
			}
		}
		i = l - 1;
		while (i > -1 && write_nr[i] == 0) write_nr.pop_back();
		
		if (i == -1) return zeroB();
		
		bigint ans;
		ans.sign = 1;
		ans.length = write_nr.size();
		ans.digits = write_nr;
		return ans;
	}
}



bigint bigint::operator+ ( bigint test) {
	if (length == 0) return test;
	
	bigint ans;
	if (sign * (test.sign) == 1){
		ans = (*this).sumabsB(test);
		ans.sign = sign;	
	}
	else if( (*this).isbiggerabsB(test) ){
		ans = (*this).diffabsB(test);
		ans.sign = sign;
	}
	else {
		ans = test.diffabsB(*this);
		ans.sign = test.sign;	
	}
	return ans;
}

bigint bigint::operator- ( bigint test) {
	return (*this) + test.symmB();
}

bigint bigint::operator* ( bigint test) {
	if (length == 0 || test.length == 0) return zeroB();

	bigint ans;
	vector<int> write_nr (length + test.length + 1, 0);
	int i, j, k, l;
	l = write_nr.size() - 1;
	for (i = 0; i < length; i++) {
		for (j = 0; j < test.length; j++) {
			write_nr[i + j] += digits[i] * (test.digits)[j];
		}
		for (j = i; j < l; j++) {
			write_nr[i + 1] += (write_nr[i]/BASE);
			write_nr[i] = write_nr[i]%BASE;
		}
	}
	
	write_nr.pop_back();
	if (write_nr.back() == 0) write_nr.pop_back();
	
	ans.digits = write_nr;
	ans.sign = sign * (test.sign);
	ans.length = write_nr.size();
	return ans;	
}



//YOU CAN IMPLEMENT KARATSUBA ALGORITHM although I don't know if there would be advantages for my implementation

//TESTING REQUIRED
