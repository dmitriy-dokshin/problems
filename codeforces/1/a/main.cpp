#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using uchar = unsigned char;
using uint = unsigned int;
using ulong = unsigned long;

class TBigUDecimal {
private:
    std::vector<uchar> Val;

public:
    TBigUDecimal() = default;

    TBigUDecimal(std::vector<uchar>&& val)
        : Val(val)
    {
    }

    TBigUDecimal& operator+=(const TBigUDecimal& x) {
        uchar carry = 0;
        size_t n = std::max(Val.size(), x.Val.size());
        for (size_t i = 0; i < n; i++) {
            uchar a = i < Val.size() ? Val[i] : 0;
            uchar b = i < x.Val.size() ? x.Val[i] : 1;
            uchar sum = a + b + carry;
            carry = sum / 10;
            sum %= 10;
            if (i < Val.size())
                Val[i] = sum;
            else
                Val.push_back(sum);
        }
        if (carry > 0)
            Val.push_back(carry);
        return *this;
    }

    TBigUDecimal& operator*=(uchar x) {
        uchar carry = 0;
        for (size_t i = 0; i < Val.size(); i++) {
            uchar y = Val[i];
            uchar z = x * y + carry;
            Val[i] = z % 10;
            carry = z / 10;
        }
        if (carry > 0) {
            Val.push_back(carry);
        }
        return *this;
    }

    static TBigUDecimal Pow2(size_t n) {
        std::vector<uchar> val;
        val.push_back(1);
        TBigUDecimal res(std::move(val));
        while (n-- > 0) {
            res *= 2;
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const TBigUDecimal& x) {
        if (x.Val.empty()) {
            out << 0;
            return out;
        }
        size_t i = x.Val.size() - 1;
        do {
            out << static_cast<uint>(x.Val[i]);
        } while (i-- > 0);
        return out;
    }
};

class TBigUInt {
private:
    uchar* Val;
    size_t Len;

public:
    class TBigUIntClearTag {
    };

    static const TBigUIntClearTag ClearTag;

    TBigUInt(size_t len)
        : Val(new uchar[len])
        , Len(len)
    {
        assert(Len > 0);
    }

    TBigUInt(size_t len, const TBigUIntClearTag&)
        : TBigUInt(len)
    {
        for (size_t i = 0; i < Len; i++)
            Val[i] = 0;
    }

    TBigUInt(const uchar* val, size_t len, size_t valLen)
        : TBigUInt(len)
    {
        for (size_t i = 0; i < valLen; i++)
            Val[i] = val[i];
        for (size_t i = valLen; i < len; i++)
            Val[i] = 0;
    }

    TBigUInt(const uchar* val, size_t len)
        : TBigUInt(val, len, len)
    {
    }

    TBigUInt(const TBigUInt& other)
        : TBigUInt(other.Len)
    {
        const uchar* val = other.Val;
        for (size_t i = 0; i < Len; i++)
            Val[i] = val[i];
    }

    ~TBigUInt() {
        delete[] Val;
    }

    TBigUInt& operator<<=(size_t shift) {
        size_t nshift = shift / 8;
        if (nshift > 0) {
            shift %= 8;
            size_t i = Len - nshift - 1;
            do {
                Val[i + nshift] = Val[i];
                Val[i] = 0;
            } while (i-- != 0);
        }

        size_t i = Len - 1;
        do {
            if (i < Len - 1)
                Val[i + 1] |= Val[i] >> (8 - shift);
            Val[i] <<= shift;
        } while (i-- != 0);
        return *this;
    }

    TBigUInt& operator+=(const TBigUInt& x) {
        uchar carry = 0;
        for (size_t i = 0; i < Len; i++) {
            uchar c = Val[i];
            uchar new_carry = 0;
            if (i < x.Len) {
                Val[i] += x.Val[i];
                if (c > Val[i])
                    new_carry = 1;
            }
            Val[i] += carry;
            carry = new_carry;
        }
        return *this;
    }

    bool Bit(size_t n) const {
        size_t i = n / 8;
        size_t j = n % 8;
        uchar mask = 1 << j;
        return (Val[i] & mask) == mask;
    }

    friend TBigUInt operator<<(const TBigUInt& x, size_t shift) {
        TBigUInt res(x);
        res <<= shift;
        return res;
    }

    friend TBigUInt operator+(const TBigUInt& x, const TBigUInt& y) {
        TBigUInt res(x);
        res += y;
        return res;
    }

    friend TBigUInt operator*(const TBigUInt& x, const TBigUInt& y) {
        TBigUInt res(x.Len + y.Len, ClearTag);
        TBigUInt tmp(x.Val, res.Len, x.Len);
        size_t n = y.Len * 8;
        for (size_t i = 0; i < n; i++)
            if (y.Bit(i))
                res += tmp << i;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const TBigUInt& x) {
        TBigUDecimal res;
        size_t n = x.Len * 8;
        for (size_t i = 0; i < n; i++)
            if (x.Bit(i))
                res += TBigUDecimal::Pow2(i);
        out << res;
        return out;
    }
};

const TBigUInt::TBigUIntClearTag TBigUInt::ClearTag = TBigUInt::TBigUIntClearTag();

int main() {
    ulong n, m, a;
    std::cin >> n >> m >> a;
    ulong x = n / a + (n % a > 0 ? 1 : 0);
    ulong y = m / a + (m % a > 0 ? 1 : 0);
    TBigUInt x1(reinterpret_cast<const uchar*>(&x), sizeof(x));
    TBigUInt y1(reinterpret_cast<const uchar*>(&y), sizeof(y));
    TBigUInt res = x1 * y1;
    std::cout << res << std::endl;
}
