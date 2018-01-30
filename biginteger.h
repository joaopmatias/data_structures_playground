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

void operator= (bigint);
void printB(int);
bigint symmB(void) ;
bigint absB(void) ;
bool operator== ( bigint );
bool isbiggerabsB ( bigint, int) ;
bigint sumabsB ( bigint ) ;
bigint diffabsB ( bigint, int ) ;
bool operator< ( bigint );
bool operator> ( bigint );
bigint operator+ ( bigint );
bigint operator- ( bigint );
bigint operator* ( bigint );
bigint operator/ ( bigint );
bigint operator% ( bigint );
}; 

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
	for (i = 0; i < l1; i++) write_nr[i] = digits1[i];
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
	vector<int> write_nr (l1 + l2, 0);
	int i, j, k, l;
	l = l1 + l2;
	for (i = 0; i < l1; i++) {
		for (j = 0; j < l2; j++) {
			write_nr[i + j] += digits1[i] * digits2[j];
		}
		for (j = i; j < l; j++) {
			write_nr[j + 1] += (write_nr[j]/base);
			write_nr[j] = write_nr[j]%base;
		}
	}
	if (write_nr.back() == 0) write_nr.pop_back();
	return write_nr;	
}

vector<int> basetobase(vector<int> digits, int obase, int nbase){
	vector<int> old_base, npow, ans, summand;
	int i, l;
	l = digits.size();
	old_base = inttobase(obase, nbase);
	npow.push_back(1);
	ans = inttobase(digits[0], nbase);
	for(i = 1; i < l; i++){
		npow = prodbase(npow, old_base, nbase);
		summand = prodbase(npow, inttobase(digits[i], nbase), nbase);
		ans = sumbase(ans, summand, nbase);
	}
	return ans;
}

//constructor
bigint::bigint(void) {
	digits.resize(1);
	digits[0] = 0;
	sign = 1;
	length = 0;
}

//zero function
bigint zeroB(){
	bigint ans(0);
	return ans;
}

//constructor int
bigint::bigint(int nr) {
	digits = inttobase( abs(nr), BASE );
	sign = 1 - 2 * (nr < 0);
	length = digits.size() - (nr == 0);
}

//constructor bigint
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
	if (length == 0){
		cout << 0;
		return ;
	}
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
	vector<int> ans;
	ans = basetobase(digits, BASE, base);
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
	if (length > 0) ans.length *= -1;
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
bool bigint::isbiggerabsB( bigint test, int adv = 0 )  {
	if (length == 0) return false;
	if (test.length == 0) return true;
	else if (length > test.length + adv) return true;
	else if (length < test.length + adv) return false;
	else {
		int i;
		for (i = test.length - 1; i >= 0; i--) {
			if ( digits[i + adv] > (test.digits)[i] ) return true;
			else if ( digits[i + adv] < (test.digits)[i] ) return false;
		}
		for (i = adv - 1; i >= 0; i--) {
			if ( digits[i] > 0 ) return true;
		}
	}
	return false;	
}

bool bigint::operator< ( bigint test) {
	if (sign < test.sign) return true;
	else if (sign > test.sign) return false;
	else if (sign == 1) return test.isbiggerabsB(*this);
	else return (*this).isbiggerabsB(test);
}

bool bigint::operator> ( bigint test) {
	if (sign > test.sign) return true;
	else if (sign < test.sign) return false;
	else if (sign == -1) return test.isbiggerabsB(*this);
	else return (*this).isbiggerabsB(test);
}


//next operator: sum 

bigint bigint::sumabsB( bigint test)  {
	if (length == 0) return test.absB();
	if (test.length == 0) return (*this).absB();
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

bigint bigint::diffabsB( bigint test, int adv = 0)  {//*this* is the largest in abs
	if (length == 0) return zeroB();
	if (test.length == 0) return *this;
	else {
		int i, l = max(length, test.length + adv); //it's length
		vector<int> write_nr (l, 0);
		write_nr = digits;
		for (i = 0; i < test.length; i++) {
			write_nr[i + adv] -= (test.digits)[i];
			if (write_nr[i + adv] < 0) {
				write_nr[i + adv] += BASE;
				write_nr[i + adv + 1]--;
			}
		}
		while (write_nr.back() == 0) write_nr.pop_back();
		if (write_nr.size() == 0) return zeroB();
		bigint ans;
		ans.sign = 1;
		ans.length = write_nr.size();
		ans.digits = write_nr;
		return ans;
	}
}



bigint bigint::operator+ ( bigint test) {
	if (length == 0) return test;
	if (test.length == 0) return *this;
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
		if(ans == zeroB()) ans.sign = 1;
		else ans.sign = test.sign;	
	}
	return ans;
}

bigint bigint::operator- ( bigint test) {
	return (*this) + test.symmB();
}

bigint bigint::operator* ( bigint test) {
	if (length == 0 || test.length == 0) return zeroB();
	bigint ans;
	int i, j, l;
	vector<int> write_nr;
	write_nr = prodbase(digits, test.digits, BASE);
	if (write_nr.back() == 0) write_nr.pop_back();
	ans.digits = write_nr;
	ans.sign = sign * (test.sign);
	ans.length = write_nr.size();
	return ans;	
}

bigint bigint::operator/ (bigint test) {
	if(test.isbiggerabsB(*this)) return zeroB();
	if(test.length == 0) {
		cout << "Don't divide by zero!" << endl;
		return zeroB();
	}
	int i, k, l, Divi, divi;
	bigint temp;
	l = length - test.length;
	vector<int> write_nr (l + 1);
	temp = (*this).absB();
	if(test.length == 1) {
		divi = test.digits[0];
		for( ; l > -1; l--){
			if(temp.length == test.length + l + 1) 
				Divi = BASE * temp.digits.back() 
					+ temp.digits[temp.length - 2];
			else if(temp.length == test.length + l)
				Divi = temp.digits.back();
			else Divi = 0;
			k = Divi/divi;
			temp = temp.diffabsB( test * bigint(k), l );
			write_nr[l] = k;
		}
	}
	else {
		divi = BASE * test.digits.back() + test.digits[test.length - 2] + 1;
		for( ; l > -1; l--){
			if(temp.length == test.length + l + 1) 
				Divi = BASE * BASE * temp.digits.back() 
					+ BASE * temp.digits[temp.length - 2]
					+ temp.digits[temp.length - 3];
			else if(temp.length == test.length + l)
				Divi = BASE * temp.digits.back() 
					+ temp.digits[temp.length - 2];
			else Divi = 0;
			k = Divi/divi;
			temp = temp.diffabsB( test * bigint(k), l );
			if( (temp + bigint(1)).isbiggerabsB(test, l) ) {
				write_nr[l] = k + 1;
				temp = temp.diffabsB( test, l);
			}
			else write_nr[l] = k;
		}
	}
	bigint ans;
	if(write_nr.back() == 0) write_nr.pop_back();
	ans.digits = write_nr;
	ans.sign = sign * test.sign;
	ans.length = write_nr.size();
	return ans;
}

bigint bigint::operator% (bigint test) {
	if(test.isbiggerabsB(*this)) return zeroB();
	if(test.length == 0) {
		cout << "Don't divide by zero!" << endl;
		return zeroB();
	}
	int i, k, l, Divi, divi;
	bigint temp;
	l = length - test.length;
	vector<int> write_nr (l + 1);
	temp = (*this).absB();
	if(test.length == 1) {
		divi = test.digits[0];
		for( ; l > -1; l--){
			if(temp.length == test.length + l + 1) 
				Divi = BASE * temp.digits.back() 
					+ temp.digits[temp.length - 2];
			else if(temp.length == test.length + l)
				Divi = temp.digits.back();
			else Divi = 0;
			k = Divi/divi;
			temp = temp.diffabsB( test * bigint(k), l );
			write_nr[l] = k;
		}
	}
	else {
		divi = BASE * test.digits.back() + test.digits[test.length - 2] + 1;
		for( ; l > -1; l--){
			if(temp.length == test.length + l + 1) 
				Divi = BASE * BASE * temp.digits.back() 
					+ BASE * temp.digits[temp.length - 2]
					+ temp.digits[temp.length - 3];
			else if(temp.length == test.length + l)
				Divi = BASE * temp.digits.back() 
					+ temp.digits[temp.length - 2];
			else Divi = 0;
			k = Divi/divi;
			temp = temp.diffabsB( test * bigint(k), l );
			if( (temp + bigint(1)).isbiggerabsB(test, l) ) {
				write_nr[l] = k + 1;
				temp = temp.diffabsB( test, l);
			}
			else write_nr[l] = k;
		}
	}
	temp.sign = sign;
	return temp;
}

//YOU CAN IMPLEMENT KARATSUBA ALGORITHM although I don't know if there would be advantages for my implementation

