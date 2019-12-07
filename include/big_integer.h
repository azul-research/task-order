#pragma once 

#include <vector>
#include <string>

class big_integer {
public:
	big_integer();
	big_integer(std::string str);
	big_integer(int num);
	void remove_leading_zeros();

	bool operator==(const big_integer& other) const;
	bool operator<(const big_integer& other) const;
	bool operator!=(const big_integer& other) const;
	bool operator<=(const big_integer& other) const;
	bool operator>=(const big_integer& other) const;
	bool operator>(const big_integer& other) const;

	const big_integer operator+(const big_integer& other);
	const big_integer operator-(const big_integer& other);
	const big_integer operator*(const big_integer& other) const;
	const big_integer operator%(const big_integer& other);
	const big_integer operator/(const big_integer& other) const;
	void shift_other();

	big_integer& operator+=(const big_integer& value);
	big_integer& operator*=(const big_integer& value);
	big_integer& operator/=(const big_integer& value);
	big_integer& operator-=(const big_integer& value);
	const big_integer operator++();
	const big_integer operator--();
	const big_integer operator++(int);
	const big_integer operator--(int);

	friend std::ostream& operator<<(std::ostream& os, const big_integer& bi);
private:
	std::vector<int> _digits;
	static const int BASE = 1000000000;
};