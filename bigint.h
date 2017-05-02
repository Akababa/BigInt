#include <iostream>
#include <vector>

class BigInt {
	std::vector<unsigned int> s;

	public:
		BigInt() {};
		BigInt(unsigned long long l);
		BigInt(const BigInt& b);
		BigInt(BigInt&& b);

		BigInt& operator=(const BigInt& b);
		BigInt& operator=(BigInt&& b);
		BigInt operator+(const BigInt& b) const;
		BigInt& operator+=(const BigInt& b);
		BigInt operator*(unsigned int a) const ;
		BigInt& operator*=(unsigned int a);
		BigInt operator/(unsigned int a) const ;
		BigInt& operator/=(unsigned int a);
		unsigned int operator%(unsigned int a) const;

		bool operator<(const BigInt& b) const;
		bool operator>(const BigInt& b) const;
		bool operator<=(const BigInt& b) const;
		bool operator>=(const BigInt& b) const;
		bool operator==(const BigInt& b) const;
		bool operator!=(const BigInt& b) const;
		bool operator==(unsigned int a) const;
		bool operator!=(unsigned int a) const;

		explicit operator bool() const;

		friend std::istream& operator>>(std::istream& in, BigInt& b);
		friend std::ostream& operator<<(std::ostream& out, const BigInt& b);
};