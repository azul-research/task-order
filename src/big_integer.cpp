#include <vector>
#include <big_integer.h>
#include <string>
#include <iomanip>
#include <iostream>

big_integer::big_integer() : big_integer(0){}

big_integer::big_integer(std::string str) {
	for (long long i = str.length(); i > 0; i -= 9) {
    	if (i < 9) {
            _digits.push_back(atoi(str.substr(0, i).c_str()));
        } else {
            _digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }
        remove_leading_zeros();
    }
}

big_integer::big_integer(int num) {
    do {
        _digits.push_back(num % big_integer::BASE);
        num /= big_integer::BASE;
    } while (num != 0);
}

void big_integer::remove_leading_zeros() {
	while (_digits.size() > 1 && _digits.back() == 0) {
        _digits.pop_back();
    }
}

bool big_integer::operator==(const big_integer& other) const{
	if (_digits.empty()) {
        if (other._digits.empty() || (other._digits.size() == 1 && other._digits[0] == 0)) {
            return true;
        } else {
        	return false;
        }
    }
    if (other._digits.empty()) {
        if (_digits.size() == 1 && _digits[0] == 0) {
          	return true;
        } else {
             return false;
        }
    }
    if (_digits.size() != other._digits.size()) {
    	return false;
    }
    for (size_t i = 0; i < _digits.size(); ++i) {
    	if (_digits[i] != other._digits[i]) {
    		return false;
    	}
    }
    return true;
}

bool big_integer::operator<(const big_integer& other) const {
	if (*this == other) {
		return false;
	}
    if (_digits.size() != other._digits.size()) {
        return _digits.size() < other._digits.size();
    } else {
        for (long long i = _digits.size() - 1; i >= 0; --i) {
            if (_digits[i] != other._digits[i]) {
            	return _digits[i] < other._digits[i];
            }
        }              
        return false;
    }
}

bool big_integer::operator!=(const big_integer& other) const {
	return !(*this == other);
}

bool big_integer::operator<=(const big_integer& other) const {
	return (*this < other || *this == other);
}

bool big_integer::operator>=(const big_integer& other) const {
	return !(*this < other);
}

bool big_integer::operator>(const big_integer& other) const {
	return !(*this <= other);
}

const big_integer big_integer::operator+(const big_integer& other) const{
	int carry = 0;
	big_integer result = *this;
    for (size_t i = 0; i < std::max(result._digits.size(), other._digits.size()) || carry != 0; ++i) {
        if (i == result._digits.size()) {
        	result._digits.push_back(0);
        }
        result._digits[i] += carry + (i < other._digits.size() ? other._digits[i] : 0);
        carry = result._digits[i] >= big_integer::BASE;
        if (carry != 0) {
         	result._digits[i] -= big_integer::BASE;
        }
    }
    return result;
}

const big_integer big_integer::operator-(const big_integer& other) const {
	int carry = 0;
	big_integer result = *this;
    for (size_t i = 0; i < other._digits.size() || carry != 0; ++i) {
        result._digits[i] -= carry + (i < other._digits.size() ? other._digits[i] : 0);
        carry = result._digits[i] < 0;
        if (carry != 0) {
        	result._digits[i] += big_integer::BASE;
        }
    }
    result.remove_leading_zeros();
    return result;
}

const big_integer big_integer::operator*(const big_integer& other) const {
	big_integer result;
    result._digits.resize(_digits.size() + other._digits.size());
    for (size_t i = 0; i < _digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
            _digits[i] * 1LL * (j < other._digits.size() ? other._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % big_integer::BASE);
            carry = static_cast<int>(cur / big_integer::BASE);
        }
    }
    result.remove_leading_zeros();
    return result;
}

const big_integer big_integer::operator/(const big_integer& other) const {
    big_integer b = other;
    big_integer result, current;
    result._digits.resize(_digits.size());
    for (long long i = static_cast<long long>(_digits.size()) - 1; i >= 0; --i) {
        current.shift_other();
        current._digits[0] = _digits[i];
        current.remove_leading_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else {
            	r = m - 1;
            }
        }
        result._digits[i] = x;
        current = current - b * x;
    }
	result.remove_leading_zeros();
    return result;
}

const big_integer big_integer::operator%(const big_integer& other) {
    big_integer b = other;
    big_integer result, current;
    result._digits.resize(_digits.size());
    for (long long i = static_cast<long long>(_digits.size()) - 1; i >= 0; --i) {
        current.shift_other();
        current._digits[0] = _digits[i];
        current.remove_leading_zeros();
        int x = 0, l = 0, r = big_integer::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            big_integer t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            } else {
            	r = m - 1;
            }
        }
        result._digits[i] = x;
        current = current - b * x;
    }
	current.remove_leading_zeros();
    return current;
}

void big_integer::shift_other() {
	if (_digits.size() == 0) {
        _digits.push_back(0);
        return;
    }
    _digits.push_back(_digits[_digits.size() - 1]);
    for (size_t i = _digits.size() - 2; i > 0; --i) {
    	_digits[i] = _digits[i - 1];
    }
    _digits[0] = 0;
}

big_integer& big_integer::operator+=(const big_integer& value) {
	return *this = (*this + value);
}

big_integer& big_integer::operator*=(const big_integer& value) {
	return *this = (*this * value);
}

big_integer& big_integer::operator/=(const big_integer& value) {
	return *this = (*this / value);
}

big_integer& big_integer::operator-=(const big_integer& value) {
	return *this = (*this - value);
}

big_integer& big_integer::operator%=(const big_integer& value) {
	return *this = (*this % value);
}

const big_integer big_integer::operator++() {
	return (*this += 1);
}

const big_integer big_integer::operator--() {
	return (*this -= 1);
}

const big_integer big_integer::operator --(int) {
	*this -= 1;
	return *this + 1;
}

const big_integer big_integer::operator ++(int) {
	*this += 1;
	return *this - 1;
}

std::ostream& operator <<(std::ostream& os, const big_integer& bi) {
    if (bi._digits.empty()) {
        os << 0;
    }
    else {
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) {
            os << bi._digits[i];
        }
	    os.fill(old_fill);
    }
    return os;
}

int big_integer::to_integer() const {
	int result = 0, pw = 1;
	for (long long i = 0; i < static_cast<long long>(_digits.size()); i++) {
		result += _digits[i] * pw;
		pw *= big_integer::BASE;
	}
	return result;
}