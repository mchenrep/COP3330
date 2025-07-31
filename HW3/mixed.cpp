#include "mixed.h"

// Friend Functions
istream& operator>>(istream& s, Mixed& m) // POSSIBLE LOGIC ERROR
{
    char c;
    
    s >> m.integer >> m.numerator >> c >> m.denominator;
    if((m.integer < 0 && m.numerator < 0) || m.denominator == 0)
    {
        m = 0;
        return s;
    }
    return s;
}

ostream& operator<<(ostream& s, const Mixed& m)
{
    if(m.integer == 0) 
    {
        if(m.numerator == 0)
        {
            s << 0 << "\n";
            return s; // if numerator is 0, then the fraction is 0
        }
        s << m.numerator << "/" << m.denominator<< "\n";
        return s;
    }
    if(m.numerator == 0 && m.integer != 0)
    {
        s<< m.integer << "\n";
        return s;
    }
    s << m.integer<< " " << m.numerator << "/" << m.denominator<<"\n";
    return s;
}

bool operator<(const Mixed& m1, const Mixed& m2)
{
    if(m1.integer < m2.integer)
        return true;
    if(m1.integer > m2.integer)
        return false;
    else
    {
        if((m1.numerator/m1.denominator) < (m2.numerator/m2.denominator))
            return true;
        return false;
    }
}

bool operator>=(const Mixed& m1, const Mixed& m2) // opposite of < function
{
    if(!(m1 < m2))
        return true;
    return false;
}

bool operator>(const Mixed& m1, const Mixed& m2)
{
    if(m1.integer > m2.integer)
        return true;
    if(m1.integer < m2.integer)
        return false;
    else
    {
        if((m1.numerator/m1.denominator) > (m2.numerator/m2.denominator))
            return true;
        return false;
    }
}

bool operator<=(const Mixed& m1, const Mixed& m2) // opposite of > function
{
    if(!(m1 > m2))
        return true;
    return false;
}

bool operator==(const Mixed& m1, const Mixed& m2)
{
    if(m1.integer == m2.integer && (m1.numerator/m1.denominator) == (m2.numerator/m2.denominator))
        return true;
    return false;
}

bool operator!=(const Mixed& m1, const Mixed& m2) // opposite of == function
{
    if(!(m1 == m2))
        return true;
    return false;
}

Mixed operator+(const Mixed& m1, const Mixed& m2) // adds integers, then puts fractions in common denominators before adding and simplifying
{
    Mixed r, x, y;
    x = m1;
    y = m2;
    x.ToFraction();
    y.ToFraction();
    r.numerator = (x.numerator * y.denominator) + (y.numerator * x.denominator);
    r.denominator = x.denominator * y.denominator;
    r.Simplify();
    return r;
}

Mixed operator-(const Mixed& m1, const Mixed& m2) // turns fractions improper for an easier time subtracting, then simplifies
{
    Mixed r, x, y;
    x = m1;
    y = m2;
    x.ToFraction();
    y.ToFraction();
    r.numerator = (x.numerator * y.denominator) - (y.numerator * x.denominator);
    r.denominator = x.denominator * y.denominator;
    r.Simplify();
    return r;
}    

Mixed operator*(const Mixed& m1, const Mixed& m2) // multiplies integers then fractions before simplifying
{
    Mixed r, x, y;
    x = m1;
    y = m2;
    x.ToFraction();
    y.ToFraction();
    r.numerator = x.numerator * y.numerator;
    r.denominator = x.denominator * y.denominator;
    r.Simplify();
    return r;
}

Mixed operator/(const Mixed& m1, const Mixed& m2) // turns into improper fractions then does division before simplifying, if 2nd operand is 0 return default (0)
{
    Mixed r, x, y;
    x = m1;
    y = m2;
    x.ToFraction();
    y.ToFraction();
    if(x.numerator * y.denominator == 0 || x.denominator * y.numerator == 0)
        return r;
    r.numerator = x.numerator * y.denominator;
    r.denominator = x.denominator * y.numerator;
    r.Simplify();
    return r;
}

//----------------------------------------------------------Member functions---------------------------------------------------------------------------
Mixed::Mixed(int i, int n, int d)
// first constructor, error checks than only the first non zero integer is negative and denominator is 0 before editing values
{
    if((i < 0 && n < 0) && d != 0)
    {
        integer = 0;
        numerator = 0;
        denominator = 1;
    }
    else
    {
        integer = i;
        numerator = n;
        denominator = d;

    }
}

Mixed::Mixed(int n)
{
    Mixed(n,0,1);
}

double Mixed::Evaluate() const
{
    double r = integer;
    if(r < 0)
    {
        r+=(static_cast<double>(numerator)/denominator) * -1;
        return r;
    }
    r+=(static_cast<double>(numerator)/denominator);
    return r;
}

void Mixed::ToFraction()
{
    if(integer < 0)
    {
        int i = AbsoluteValue(integer);
        numerator+=(i * denominator);
        numerator*=-1;
        integer = 0;
    }
    else if(integer > 0)
    {
        numerator+=(integer * denominator);
        integer = 0;
    }
}

void Mixed::Simplify()
{
    int n = AbsoluteValue(numerator), g = 1;
    if(n > denominator)
    {
        g = GreatestCommonFactor(n,denominator);
        if(integer < 0)
            integer+= (n/denominator) * -1;
        else if(integer == 0)
            integer+=(numerator/denominator);
        else
            integer+= (n/denominator);
        /*
            To solve problem of integer and numerator being negative, use if statement to detect and set numerator positive if both are negative
            To solve problem of reducing numerator use n
        */
        numerator = n-((n/denominator)*denominator);
        numerator/=g;
        denominator/=g;
    }
    else if(denominator > n)
    {
        g = GreatestCommonFactor(denominator, n);
        numerator/=g;
        denominator/=g;
    }
}

Mixed& Mixed::operator++()
{
    integer++;
    Simplify();
    return *this;
}          

Mixed& Mixed::operator--()
{
    integer--;
    Simplify();
    return *this;
}

Mixed& Mixed::operator++(int n)
{
    return *this;
    integer++;
    Simplify();
} 

Mixed& Mixed::operator--(int n)
{
    return *this;
    integer--;
    Simplify();

}

int Mixed::GreatestCommonFactor(int x, int y)
// assumes y < x, increments from 1 to y in order to find the greatest common factor between x and y
{
    int r = 1;
    for(int i = 1; i < y; i++)
    {  
        if(x % i == 0 && y % i == 0)
            r = i; 
    }
    return r;
}

int Mixed::AbsoluteValue(int x) // helper function to return absolute value of a number
{
    if(x < 0)
        return x*-1;
    return x;
}
