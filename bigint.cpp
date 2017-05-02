#include <cmath>
#include "bigint.h"
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;

BigInt::BigInt(ull l) {
	ui a=l>>32,b=l;
	if(a) s={b,a};
	else if(b) s={b};
	else s={};
}

BigInt::BigInt(const BigInt& b){
	s=b.s;
}

BigInt::BigInt(BigInt&& b){
	swap(s,b.s);
}

BigInt& BigInt::operator=(const BigInt& b){
	if(this==&b) return *this;
	s=b.s;
	return *this;
}

BigInt& BigInt::operator=(BigInt&& b){
	swap(s,b.s);
	return *this;
}

BigInt BigInt::operator+(const BigInt& b) const{
	return BigInt(*this)+=b;
}

BigInt& BigInt::operator+=(const BigInt& b){
	const ui n=b.s.size();
	//cout << n <<endl;
	if(n>s.size()) s.resize(n,0);
	ull carry=0;
	for(ui i=0; i<n; i++)
		s[i]=(carry=((carry>>32)+s[i]+b.s[i]));
	for(ui i=n; carry!=0 && i<s.size(); i++)
		s[i]=(carry=((carry>>32)+s[i]));
	
	if(carry>>=32){
		//cout << carry<<endl;
		s.push_back(carry);
	}
	return *this;
}

BigInt BigInt::operator*(ui a) const {
	return BigInt(*this)*=a;
}

BigInt& BigInt::operator*=(ui a){
	ull aa=a;
	const ui n=s.size();
	ull carry=0;
	for(ui i=0; i<n; i++)
		s[i]=(carry=(carry>>32)+s[i]*aa);
	
	if(carry>>=32) s.push_back(carry);
	return *this;
}

BigInt BigInt::operator/(ui a) const {
	return BigInt(*this)/=a;
}

BigInt& BigInt::operator/=(ui a){
	ull carry=0;
	for(ui i=s.size();i--;){
		s[i]=(carry=((carry%a)<<32)+s[i])/a;
	}
	if(!s.empty() && s.back()==0) s.pop_back();
	return *this;
}

ui BigInt::operator%(ui a) const{
	const ull ttt=(1L<<32)%a;
	ull r=0;
	for(ui i=s.size(); i--;){
		r=(r*ttt+s[i])%a;
	}
	return r;
}

bool BigInt::operator<(const BigInt& b) const{
	if(s.size()!=b.s.size()) return s.size()<b.s.size();
	for(ui i=s.size(); i--;){
		if(s[i]<b.s[i]) return true;
	}
	return false;
}

bool BigInt::operator>(const BigInt& b) const{
	return b<*this;
}

bool BigInt::operator<=(const BigInt& b) const{
	return !(*this>b);
}

bool BigInt::operator>=(const BigInt& b) const{
	return !(*this<b);
}

bool BigInt::operator==(const BigInt& b) const{
	return s==b.s;
}

bool BigInt::operator!=(const BigInt& b) const{
	return !operator==(b);
}

bool BigInt::operator==(ui a) const{
	return (a==0 && s.empty()) || (a && s[0]==a);
}

bool BigInt::operator!=(ui a) const{
	return !operator==(a);
}

BigInt::operator bool() const {
	return *this!=0;
}

istream& operator>>(istream& in, BigInt& b){
	string s; in>>s;
	b=0;
	for(char c:s){
		(b*=10)+=(c-'0');
	}
	return in;
}

ostream& operator<<(ostream& out, const BigInt& b){
	BigInt c=b;
	vector<char> digits;
	do{
		digits.push_back(c%10+'0');
	}while(c/=10);
	for(ui i=digits.size();i--;){
		out << digits[i];
	}
	return out;
}