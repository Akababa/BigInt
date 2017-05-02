#include <iostream>
#include "bigint.h"
using namespace std;
BigInt factorial(int n){
	BigInt b=1;
	for(int i=2; i<=n; i++) b*=i;
	return b;
}

int main() {
	// your code goes here
	int a; cin>>a;
	cout <<"factorial: "<<factorial(a)<<endl;

	
	return 0;
}