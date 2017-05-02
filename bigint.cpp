#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

class BigInt {
	vector<unsigned int> s;
	public:
	BigInt() {};
	BigInt(unsigned long l) {
		unsigned int a=l>>32,b=l;
		if(a) s={b,a};
		else if(b) s={b};
		else s={};
	}
	BigInt(const BigInt& b){
		s=b.s;
	}
	BigInt(BigInt&& b){
		swap(s,b.s);
	}
	BigInt& operator=(const BigInt& b){
		if(this==&b) return *this;
		s=b.s;
		return *this;
	}
	BigInt& operator=(BigInt&& b){
		swap(s,b.s);
		return *this;
	}
	BigInt operator+(const BigInt& b) const{
		return BigInt(*this)+=b;
	}
	BigInt& operator+=(const BigInt& b){
		const int n=b.s.size();
		//cout << n <<endl;
		if(n>s.size()) s.resize(n,0);
		unsigned long carry=0;
		for(int i=0; i<n; i++)
			s[i]=(carry=((carry>>32)+s[i]+b.s[i]));
		for(int i=n; carry!=0 && i<s.size(); i++)
			s[i]=(carry=((carry>>32)+s[i]));
		
		if(carry>>=32){
			//cout << carry<<endl;
			s.push_back(carry);
		}
		return *this;
	}
	BigInt operator*(unsigned int a) const {
		return BigInt(*this)*=a;
	}
	BigInt& operator*=(unsigned int a){
		unsigned long aa=a;
		const int n=s.size();
		unsigned long carry=0;
		for(int i=0; i<n; i++)
			s[i]=(carry=(carry>>32)+s[i]*aa);
		
		if(carry>>=32) s.push_back(carry);
		return *this;
	}
	BigInt operator/(unsigned int a) const {
		return BigInt(*this)/=a;
	}
	BigInt& operator/=(unsigned int a){
		unsigned long carry=0;
		for(int i=s.size()-1; i>=0; i--){
			s[i]=(carry=((carry%a)<<32)+s[i])/a;
		}
		if(!s.empty() && s.back()==0) s.pop_back();
		return *this;
	}
	unsigned int operator%(unsigned int a) const{
		const unsigned long ttt=(1L<<32)%a;
		unsigned long r=0;
		for(int i=s.size()-1; i>=0; i--){
			r=(r*ttt+s[i])%a;
		}
		return r;
	}
	bool operator<(const BigInt& b) const{
		if(s.size()!=b.s.size()) return s.size()<b.s.size();
		for(int i=s.size()-1; i>=0; i--){
			if(s[i]<b.s[i]) return true;
		}
		return false;
	}
	bool operator>(const BigInt& b) const{
		return b<*this;
	}
	bool operator<=(const BigInt& b) const{
		return !(*this>b);
	}
	bool operator>=(const BigInt& b) const{
		return !(*this<b);
	}
	bool operator==(const BigInt& b) const{
		return s==b.s;
	}
	bool operator!=(const BigInt& b) const{
		return !operator==(b);
	}
	bool operator==(unsigned int a) const{
		return (a==0 && s.empty()) || (a && s[0]==a);
	}
	bool operator!=(unsigned int a) const{
		return !operator==(a);
	}
	explicit operator bool() const {
		return *this!=0;
	}
	friend istream& operator>>(istream& in, BigInt& b){
		string s; in>>s;
		b=0;
		for(char c:s){
			(b*=10);
			//cout << b << endl;
			b+=(c-'0');
			//cout << b << endl;
		}
		return in;
	}
	friend ostream& operator<<(ostream& out, const BigInt& b){
		BigInt c=b;
		vector<char> digits;
		do{
			digits.push_back(c%10+'0');
		}while(c/=10);
		for(int i=digits.size()-1;i>=0;i--){
			out << digits[i];
		}
		return out;
	}
};

BigInt factorial(int n){
	BigInt b=1;
	for(int i=2; i<=n; i++) b*=i;
	return b;
}

int main() {
	// your code goes here
	BigInt a,b; cin>>a>>b;
	cout <<(a<b);
	
	return 0;
}