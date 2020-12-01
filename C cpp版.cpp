#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#include<algorithm>
#include<vector>

using namespace std;

const unsigned long long MODD = 998244353;

char readBuf[100010];

struct BigInteger
{
	static const int maxn = 13500;
	static const unsigned long long radix = 100000000;
	unsigned long long num[maxn];
	int size;
	string print()
	{
	    static char temp[15];
	    memset(temp, 0, sizeof(temp));
	    string ret = "";
	    sprintf(temp, "%llu", num[size]);
	    ret += string(temp);
	    int i;
	    for(i = size - 1; i > 0; --i)
		{
	        memset(temp, 0, sizeof(temp));
	        sprintf(temp, "%08llu", num[i]);
	        ret += string(temp);
	    }
	    return ret;
	}
	void read()
	{
	    scanf("%s", readBuf);
	    int len = strlen(readBuf);
	    size = 0;
	    long long wid = 1, cur = 0;
	    int i; 
	    for(i = len - 1; i + 1; --i)
		{
	        cur += (readBuf[i] ^ '0') * wid;
	        wid = (wid << 1) + (wid << 3);
	        if (wid == radix)
			{
	            wid = 1;
	            num[++size] = cur;
	            cur = 0;
	        }
	    }
	    if (cur)
		{
			num[++size] = cur;
		}
	}
	BigInteger operator >> (const int& b)const
	{
	    BigInteger c;
	    c = *this;
	    int k;
	    for(k = 0; k < b; ++k)
		{
			int i;
	        for(i = c.size; i > 0; --i)
			{
	            c.num[i - 1] += (c.num[i] & 1ll) * radix;
	            c.num[i] >>= 1;
	        }
	        c.num[0] = 0;
	    }
	    while(c.size && !c.num[c.size])
		{
			--c.size;
		}
	    return c;
	}
};

struct cd
{
	double re, im;
	cd(double re = 0, double im = 0) : re(re), im(im) {}
	double real() const
	{
	    return re;
	}
	void imag(double im)
	{
	    this->im = im;
	}
	double norm() const
	{
	    return re * re + im * im;
	}
	cd operator+(const cd &rhs) const
	{
	    return cd(re + rhs.re, im + rhs.im);
	}
	cd operator-(const cd &rhs) const
	{
	    return cd(re - rhs.re, im - rhs.im);
	}
	cd operator*(const cd &rhs) const
	{
	    return cd(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
	}
	cd operator/(double x) const
	{
	    return cd(re / x, im / x);
	}
	void operator+=(const cd &rhs)
	{
	    re += rhs.re;
	    im += rhs.im;
	}
	void operator/=(double x)
	{
	    re /= x;
	    im /= x;
	}
	void operator*=(const cd &rhs)
	{
	    *this = *this * rhs;
	}
	friend cd conj(const cd &z)
	{
	    return cd(z.re, -z.im);
	}
	cd operator/(const cd &rhs) const
	{
	    return (*this * conj(rhs)) / rhs.norm();
	}
};

const int BASE = 4;
const int MOD = 10000;
const int LGM = 17;

const double PI = 3.1415926535897932384626;

class UnsignedDigit;

namespace DivHelper
{
	UnsignedDigit quasiInv(const UnsignedDigit &v);
}

namespace ConvHelper
{
	vector<long long> conv(const vector<int> &a, const vector<int> &b);
}

class UnsignedDigit
{
	vector<int> digits;
public:
	UnsignedDigit() : digits(1) {}
	UnsignedDigit(const vector<int> &digits) : digits(digits)
	{
	    if (this->digits.empty())
	    {
	    	this->digits.resize(1);
		}
	    trim();
	}
	UnsignedDigit(long long x)
	{
	    while (x)
		{
	        digits.push_back(x % MOD);
	        x /= MOD;
	    }
	    if (digits.empty())
	    {
	    	digits.push_back(0);
		}
	}
	void trim()
	{
	    while (digits.size() > 1 && digits.back() == 0)
	    {
	    	digits.pop_back();
		}
	}
	UnsignedDigit(char *str)
	{
	    int n = strlen(str);
	    reverse(str, str + n);
	    digits.resize((n + BASE - 1) / BASE);
	    int cur = 1;
	    int i;
	    for(i = 0; i < n; ++i)
		{
	        if (i % BASE == 0)
	        {
	        	cur = 1;
			}
	        digits[i / BASE] += cur * (str[i] - '0');
	        cur *= 10;
	    }
	    trim();
	}
	unsigned long long trans_normal()
	{
	    unsigned long long ret = 0;
	    unsigned long long wid = 1;
	    for(int i = 0; i < (int)digits.size(); ++i)
		{
	        ret += digits[i] * wid;
	        wid *= 10000;
	    }
	    return ret;
	}
	bool operator<(const UnsignedDigit &rhs) const
	{
	    int n = digits.size(), m = rhs.digits.size();
	    if (n != m)
	    {
	    	return n < m;
		}
	    for (int i = n - 1; i >= 0; --i)
	    {
	    	if (digits[i] != rhs.digits[i])
	    	{
	    		return digits[i] < rhs.digits[i];
			}
		}
	    return false;
	}
	bool operator<=(const UnsignedDigit &rhs) const
	{
	    int n = digits.size(), m = rhs.digits.size();
	    if (n != m)
	    {
	    	return n < m;
		}
	    for (int i = n - 1; i >= 0; --i)
	    {
	    	if (digits[i] != rhs.digits[i])
	    	{
	    		return digits[i] < rhs.digits[i];
			}
		}
	    return true;
	}
	friend UnsignedDigit DivHelper::quasiInv(const UnsignedDigit &v);
	UnsignedDigit move(int k) const
	{
	    if (k == 0)
	    {
	    	return *this;
		}
	    if (k < 0)
		{
	        if (-k >= digits.size())
	        {
	        	return UnsignedDigit();
			}
	        return vector<int>(digits.begin().base() + (-k), digits.end().base());
	    }
	    if (digits.size() == 1 && digits[0] == 0)
	    {
	    	return UnsignedDigit();
		}
	    UnsignedDigit ret;
	    ret.digits.resize(k, 0);
	    ret.digits.insert(ret.digits.end(), digits.begin(), digits.end());
	    return ret;
	}
	UnsignedDigit operator+(const UnsignedDigit &rhs) const
	{
	    int n = digits.size(), m = rhs.digits.size();
	    vector<int> tmp = digits;
	    if (m > n)
		{
	        tmp.resize(m + 1);
	        for (int i = 0; i < m; ++i)
	        {
	        	if ((tmp[i] += rhs.digits[i]) >= MOD)
				{
	                tmp[i] -= MOD;
	                ++tmp[i + 1];
	            }
			}
	    }
		else
		{
	        tmp.resize(n + 1);
	        for (int i = 0; i < m; ++i)
	        {
	        	if ((tmp[i] += rhs.digits[i]) >= MOD)
				{
	                tmp[i] -= MOD;
	                ++tmp[i + 1];
	            }
			}
	        for (int i = m; i < n; ++i)
	        {
	        	if (tmp[i] == MOD)
				{
	                tmp[i] = 0;
	                ++tmp[i + 1];
	            }
			}
	    }
	    return tmp;
	}
	UnsignedDigit operator-(const UnsignedDigit &rhs) const
	{
	    UnsignedDigit ret(*this);
	    int n = rhs.digits.size();
	    for (int i = 0; i < n; ++i)
	    {
	    	if ((ret.digits[i] -= rhs.digits[i]) < 0)
			{
	            ret.digits[i] += MOD;
	            --ret.digits[i + 1];
	        }
		}
	    ret.trim();
	    return ret;
	}
	UnsignedDigit operator*(const UnsignedDigit &rhs) const
	{
	    vector<long long> tmp = ConvHelper::conv(digits, rhs.digits);
		int i;
	    for(i = 0; i + 1 < tmp.size(); ++i)
		{
	        tmp[i + 1] += tmp[i] / MOD;
	        tmp[i] %= MOD;
	    }
	    while (tmp.back() >= MOD)
		{
	        long long remain = tmp.back() / MOD;
	        tmp.back() %= MOD;
	        tmp.push_back(remain);
	    }
	    return vector<int>(tmp.begin(), tmp.end());
	}
	UnsignedDigit operator/(UnsignedDigit rhs) const
	{
	    int m = digits.size(), n = rhs.digits.size(), t = 0;
	    if (m < n)
	    {
	    	return 0LL;
		}
	    if (m > n * 2)
	    {
	    	t = m - 2 * n;
		}
	    rhs=DivHelper::quasiInv(rhs.move(t));
	    UnsignedDigit ret = move(t) * rhs;
	    return ret.move(-2 * (n + t));
	}
	UnsignedDigit operator/(int k) const
	{
	    UnsignedDigit ret;
	    int n = digits.size();
	    ret.digits.resize(n);
	    long long r = 0;
		int i;
	    for(i = n - 1; i >= 0; --i)
		{
	        r = r * MOD + digits[i];
	        ret.digits[i] = r / k;
	        r %= k;
	    }
	    ret.trim();
	    return ret;
	}
};

namespace DivHelper
{
	UnsignedDigit quasiInv(const UnsignedDigit &v)
	{
	    if (v.digits.size() == 1)
		{
	        UnsignedDigit tmp;
	        tmp.digits.resize(3);
	        tmp.digits[2] = 1;
	        return tmp / v.digits[0];
	    }
	    if (v.digits.size() == 2)
		{
	        UnsignedDigit sum = 0LL, go = 1;
	        vector<int> tmp(4);
	        go = go.move(4);
	        vector<UnsignedDigit> db(LGM);
	        db[0] = v;
	        int i;
	        for(i = 1; i < LGM; ++i)
	        {
	        	db[i] = db[i - 1] + db[i - 1];
			}
	        for (int i = 3; i >= 0; --i)
			{
	            for (int k = LGM - 1; k >= 0; --k)
	                if (sum + db[k].move(i) <= go)
					{
	                    sum = sum + db[k].move(i);
	                    tmp[i] |= 1 << k;
	                }
	        }
	        return tmp;
	    }
	    int n = v.digits.size(), k = (n + 2) / 2;
	    UnsignedDigit tmp = quasiInv(vector<int>(v.digits.end().base() - k, v.digits.end().base()));
	    return (UnsignedDigit(2) * tmp).move(n - k) - (v * (tmp * tmp)).move(-2 * k);
	}
}

namespace ConvHelper
{
	struct FFT
	{
	    int L;
	    int brev[1 << 20];
	    cd w[1 << 20];
	    void init(int L)
		{
	        this->L = L;
			int i;
	        for(i = 0; i < (1 << L); ++i)
	        {
	        	brev[i] = (brev[i >> 1] >> 1) | ((i & 1) << (L - 1));
			}
	        for(i = 0; i < 1 << L; ++i)
	        {
	        	w[i] = cd(cos(i * PI * 2 / (1 << L)), sin(i * PI * 2 / (1 << L)));
			}
	    }
	    void dft(cd *a, int lgn, int d)
		{
	        int n = 1 << lgn;
	        for (int i = 0; i < n; ++i)
			{
	            int rv = brev[i] >> (L - lgn);
	
	            if (rv < i)
	                swap(a[rv], a[i]);
	        }
	        int fa = L;
	        for (int t = 1; t < n; t <<= 1)
			{
	            --fa;
	            for (int i = 0; i < n; i += t << 1)
				{
	                cd *p = a + i;
	                for (int j = 0; j < t; ++j)
					{
	                    cd x = p[j + t] * w[j << fa];
	                    p[j + t] = p[j] - x;
	                    p[j] += x;
	                }
	            }
	        }
	        if (d == -1)
			{
	            reverse(a + 1, a + n);
	            for (int i = 0; i < n; ++i)
	            {
	            	a[i] /= n;
				}
	        }
	    }
	    void dft(cd *a, cd *b, int lgn, int d)
		{
	        int n = 1 << lgn;
	        for (int i = 0; i < n; ++i)
	        {
	        	a[i].imag(b[i].real());
			}
	        dft(a, lgn, d);
	        b[0] = conj(a[0]);
	        for (int i = 1; i < n; ++i)
	        {
	        	b[i] = conj(a[n - i]);
			}
	        for (int i = 0; i < n; ++i)
			{
	            cd x = a[i], y = b[i];
	            a[i] = (x + y) / 2.;
	            b[i] = (x - y) / cd(0, 2);
	        }
	    }
	};
	struct FFT fft;
	vector<long long> conv(const vector<int> &a, const vector<int> &b)
	{
	    int n = a.size() - 1, m = b.size() - 1;
	    if (n < 100 / (m + 1) || n < 3 || m < 3)
		{
	        vector<long long> ret(n + m + 1);
	        int i;
	        for(i = 0; i <= n; ++i)
	        {
	        	int j;
	        	for(j = 0; j <= m; ++j)
	        	{
	        		ret[i + j] += a[i] * (long long)b[j];
				}
			}
	        return ret;
	    }
	    int lgn = 0;
	    while ((1 << lgn) <= n + m)
	    {
	    	++lgn;
		}
	    vector<cd> ta(a.begin(), a.end()), tb(b.begin(), b.end());
	    ta.resize(1 << lgn);
	    tb.resize(1 << lgn);
	    if (a == b)
		{
	        fft.dft(ta.begin().base(), lgn, 1);
	        tb = ta;
	    }
		else
		{
			fft.dft(ta.begin().base(), tb.begin().base(), lgn, 1);
		}
		int i;
	    for(i = 0; i < (1 << lgn); ++i)
	    {
	    	ta[i] *= tb[i];
		}
	    fft.dft(ta.begin().base(), lgn, -1);
	    vector<long long> ret(n + m + 1);
	    for(i = 0; i <= n + m; ++i)
	    {
	    	ret[i] = ta[i].real() + 0.5;
		}
	    return ret;
	}
}

long long ApowBmodP(long long a, long long b, long long p)
{
	long long ret = 1;
	while (b)
	{
	    if (b & 1)ret = (ret * a) % p;
	    a = (a * a) % p;
	    b >>= 1;
	}
	return ret % p;
}

char s[1000010];
bool odd;
BigInteger input;
string temp;

int main()
{
	input.read();
	odd = input.num[1] & 1;
	temp = (input >> 1).print();
	strcpy(s, temp.c_str());
	UnsignedDigit a(s);
	int l = ceil(log2(strlen(s)));
	ConvHelper::fft.init(l + 2);
	strcpy(s, "998244352");
	UnsignedDigit b(s);
	UnsignedDigit res = a / b;
	while ((res + 1) * b <= a)
	{
		res = res + 1;
	}
	while (a < res * b)
	{
		res = res - 1;
	}
	UnsignedDigit mod = a - (res * b);
	unsigned long long nor_mod = mod.trans_normal();
	if(odd)
	{
		printf("%llu\n", (ApowBmodP(6, nor_mod, MODD) << 2) % MODD);
	}
	else
	{
		printf("%llu\n", ApowBmodP(6, nor_mod, MODD) % MODD);
	}
	return 0;
}
