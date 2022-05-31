#include <iostream>
#include <vector>
#include <string>


const int base = 1000000000;
const int base_digits = 9;


class bigint {
    std::vector<int> nums;
    bool negative;

public:
    //**CONSTRUCTORS**//
    bigint();

    bigint(int number);

    bigint(const bigint &other);

    bigint &operator=(const bigint &other);

    bigint(const std::string &s);

    ~bigint() = default;

    std::string to_string() const;

    //***LOGICAL OPERATORS***//
    friend bool operator<(const bigint &u, const bigint &v);

    friend bool operator>(const bigint &u, const bigint &v);

    friend bool operator<=(const bigint &u, const bigint &v);

    friend bool operator>=(const bigint &u, const bigint &v);

    friend bool operator==(const bigint &u, const bigint &v);

    friend bool operator!=(const bigint &u, const bigint &v);

    explicit operator bool() const;


    //*** BIWISE OPERATORS***//
    friend std::ostream &operator<<(std::ostream &stream, const bigint &v);

    friend std::istream &operator>>(std::istream &stream, bigint &v);

    //***ARITHMETIC OPERATORS***//
    bigint operator-() const;

    bigint operator+() const;

    //---addition/subtraction---//
    friend bigint operator+(const bigint &u, const bigint &v);

    friend bigint operator-(const bigint &u, const bigint &v);

    std::string add_str(std::string& number1, std::string& number2);

    bigint &operator+=(const bigint &v);

    bigint &operator-=(const bigint &v);

    bigint &operator++() { return operator+=(1); }

    bigint &operator--() { return operator-=(1); }

    const bigint operator++(int) {
        bigint temp(*this);
        operator+=(1);
        return temp;
    }

    const bigint operator--(int) {
        bigint temp(*this);
        operator-=(1);
        return temp;
    }

    //---multiplication division---//
    std::string multiply(std::string n1, std::string n2);

    friend bigint operator*(const bigint &u, const bigint &v);

    bigint &operator*=(const bigint &v);

    //***USEFUL METHODS***//
    void format(const std::string &s);

    void set_sign(bool sign);

    std::vector<int> getvec();

    void trim();

    bigint abs() const;

    std::string getNumber() const;


};

//***CONSTRUCTORS***//
bigint::bigint() : negative(false) { nums.push_back(0); }

bigint::bigint(int number) {
    negative = false;
    nums.clear();
    if (number < 0)
        negative = (number < 0), number = -number;
    for (; number > 0; number = number / base)
        nums.push_back(number % base);
}


bigint::bigint(const std::string &s) {
    format(s);
}


bigint::bigint(const bigint &other) : nums(other.nums), negative(other.negative) {}

bigint &bigint::operator=(const bigint &other) {
    nums = other.nums;
    negative = other.negative;
    return *this;
}



//** USEFUL METHODS **//

void bigint::set_sign(bool sign) {
    negative = sign;
}

bigint bigint::abs() const {
    bigint res = *this;
    if (negative) { res.set_sign(!negative); }
    return res;
}

void bigint::trim() {
    while (!nums.empty() && !nums.back())
        nums.pop_back();
    if (nums.empty())
        negative = !nums.empty();
}

std::vector<int> bigint::getvec() {
    return nums;
}


void bigint::format(const std::string &s) {
    negative = false;
    nums.clear();
    int pos = 0;
    while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
        if (s[pos] == '-')
            negative = true;
        ++pos;
    }
    for (int i = s.size() - 1; i >= pos; i -= base_digits) {
        int x = 0;
        for (int j = std::max(pos, i - base_digits + 1); j <= i; j++)
            x = x * 10 + s[j] - '0';
        nums.push_back(x);
    }
    trim();
}

#include <iomanip>

std::string bigint::to_string() const {
    std::stringstream ss;
    std::string temp;
    ss << *this;
    ss >> temp;
    return temp;
}

std::string bigint::getNumber() const {
    std::string str = abs().to_string();
    return str;
}

//*** BOOL OPERATORS ***//
bool operator<(const bigint &u, const bigint &v) {
    if (u.negative != v.negative) {
        return u.negative > v.negative;
    }

    if (u.nums.size() != v.nums.size())
        return u.negative ? u.nums.size() > v.nums.size() : u.nums.size() < v.nums.size();

    for (int i = u.nums.size() - 1; i >= 0; i--) {
        if (u.nums[i] != v.nums[i] && !u.negative) { return u.nums[i] < v.nums[i]; }
        else if (u.nums[i] != v.nums[i] && u.negative) { return u.nums[i] > v.nums[i]; }
    }

    return false;
}

bigint::operator bool() const {
    return (nums.size() > 1 || nums[0] != 0);
}

bool operator>(const bigint &u, const bigint &v) {
    return v < u;
}

bool operator<=(const bigint &u, const bigint &v) {
    return !(v < u);
}

bool operator>=(const bigint &u, const bigint &v) {
    return !(u < v);
}

bool operator==(const bigint &u, const bigint &v) {
    return !(u < v) && !(u > v);
}

bool operator!=(const bigint &u, const bigint &v) {
    return u < v || v < u;
}

//*** BITWISE OPERATORS ***//
std::istream &operator>>(std::istream &stream, bigint &v) {
    std::string s;
    stream >> s;
    v.format(s);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const bigint &v) {
    if (v.negative)
        stream << '-';
    stream << (v.nums.empty() ? 0 : v.nums.back());
    for (int i = (int) v.nums.size() - 2; i >= 0; --i)
        stream << std::setw(base_digits) << std::setfill('0') << v.nums[i];
    return stream;
}


//** ARITHMETIC OPERATORS **//

bigint bigint::operator-() const {
    bigint res = *this;
    res.negative = !negative;
    return res;
}

bigint bigint::operator+() const {
    bigint res = *this;
    return res;
}

//---ADDITION/SUBTRACTION---///
bigint operator+(const bigint &u, const bigint &v) {
    if (u.negative == v.negative) {
        bigint res = v;
        for (int i = 0, carry = 0; i < (int) std::max(u.nums.size(), v.nums.size()) || carry; ++i) {
            if (i == (int) res.nums.size())
                res.nums.push_back(0);
            res.nums[i] += carry + (i < (int) u.nums.size() ? u.nums[i] : 0);
            carry = res.nums[i] >= base;
            if (carry)
                res.nums[i] -= base;
        }
        return res;
    }
    return u - (-v);
}

bigint operator-(const bigint &u, const bigint &v) {
    if (u.negative == v.negative) {
        if (u.abs() >= v.abs()) {
            bigint res = u;
            for (int i = 0, carry = 0; i < (int) v.nums.size() || carry; ++i) {
                res.nums[i] -= carry + (i < (int) v.nums.size() ? v.nums[i] : 0);
                carry = res.nums[i] < 0;
                if (carry)
                    res.nums[i] += base;
            }
            res.trim();
            return res;
        }
        return -(v - u);
    }
    return u + (-v);
}

bigint &bigint::operator+=(const bigint &v) {
    *this = *this + v;
    return *this;
}

bigint &bigint::operator-=(const bigint &v) {
    *this = *this - v;
    return *this;
}

std::string bigint::add_str(std::string& number1, std::string& number2) {
    bigint v(number1), u(number2);
    v+=u;
    std::string add = v.to_string();
    return add;
}

//---MULTIPLICATION/DIVISION---///

std::string bigint::multiply(std::string n1, std::string n2) {
    if (n1.length() > n2.length())
        n1.swap(n2);

    std::string res = "0";
    for (int i = n1.length() - 1; i >= 0; --i) {
        std::string temp = n2;
        int currentDigit = n1[i] - '0';
        int carry = 0;

        for (int j = temp.length() - 1; j >= 0; --j) {
            temp[j] = ((temp[j] - '0') * currentDigit) + carry;

            if (temp[j] > 9) {
                carry = (temp[j] / 10);
                temp[j] -= (carry * 10);
            } else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if (carry > 0)
            temp.insert(0, 1, (carry + '0'));

        temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add_str(res, temp); // O(n)
    }

    while (res[0] == '0' && res.length() != 1) // erase leading zeros
        res.erase(0, 1);

    return res;
}


bigint operator*(const bigint &u, const bigint &v) {
    bigint final;
    std::string res = final.multiply(u.getNumber(), v.getNumber());
    final.format(res);
    u.negative == v.negative ? final.negative = false : final.negative = true;
    return final;
}

bigint &bigint::operator*=(const bigint &v) {
    *this = (*this) * v;
    return *this;
}
