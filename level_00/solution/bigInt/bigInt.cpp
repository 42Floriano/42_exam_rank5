#include "bigint.hpp"
#include <sstream> // For ostringstream
#include <algorithm> // For reverse

// Constructors
bigint::bigint() : digits("0") {}

bigint::bigint(unsigned int num) {
    std::ostringstream oss;
    oss << num; // Convert number to string
    digits = oss.str();
    std::reverse(digits.begin(), digits.end()); // Reverse to make it "least significant digit first"
}

bigint::bigint(const std::string& str) {
    if (str.empty() || !std::all_of(str.begin(), str.end(), ::isdigit)) {
        digits = "0";
    } else {
        digits = str;
        std::reverse(digits.begin(), digits.end()); // Reverse for internal storage
        removeLeadingZeros();
    }
}

// Private helper: Add two reversed-digit strings
std::string bigint::addStrings(const std::string& a, const std::string& b) {
    std::string result;
    int carry = 0, sum = 0;
    size_t len = std::max(a.size(), b.size());

    for (size_t i = 0; i < len; ++i) {
        int digitA = i < a.size() ? a[i] - '0' : 0;
        int digitB = i < b.size() ? b[i] - '0' : 0;
        sum = digitA + digitB + carry;
        result.push_back((sum % 10) + '0');
        carry = sum / 10;
    }

    if (carry) result.push_back(carry + '0');
    return result;
}

void bigint::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == '0') {
        digits.pop_back();
    }
}

// Addition operators
bigint bigint::operator+(const bigint& other) const {
    bigint result;
    result.digits = addStrings(this->digits, other.digits);
    return result;
}

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

// Comparison operators
bool bigint::operator==(const bigint& other) const {
    return this->digits == other.digits;
}

bool bigint::operator!=(const bigint& other) const {
    return !(*this == other);
}

bool bigint::operator<(const bigint& other) const {
    if (this->digits.size() != other.digits.size()) 
        return this->digits.size() < other.digits.size();
    return std::lexicographical_compare(this->digits.rbegin(), this->digits.rend(),
                                        other.digits.rbegin(), other.digits.rend());
}

bool bigint::operator>(const bigint& other) const {
    return other < *this;
}

bool bigint::operator<=(const bigint& other) const {
    return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}

// Digit shift operators
bigint bigint::operator<<(unsigned int shift) const {
    if (*this == 0) return *this;
    bigint result = *this;
    result.digits.insert(result.digits.begin(), shift, '0');
    return result;
}

bigint bigint::operator>>(unsigned int shift) const {
    if (shift >= digits.size()) return bigint(0);
    bigint result = *this;
    result.digits.erase(result.digits.begin(), result.digits.begin() + shift);
    result.removeLeadingZeros();
    return result;
}

std::string bigint::getDigits(void) const
{
	return (this->digits);
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const bigint& num) {
    std::string str(num.getDigits());
    std::reverse(str.begin(), str.end());
    os << str;
    return os;
}

int main() {
    bigint num(123456);
    std::cout << "Number: " << num << std::endl; // Should print "123456"
    return 0;
}