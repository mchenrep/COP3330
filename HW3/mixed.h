// mixed .h -- Declartion for Mixed class
//
// Matthew Chen

#include <iostream>
using namespace std;

class Mixed
{

	// friends
	friend istream& operator>>(istream& s, Mixed& m);
	friend ostream& operator<<(ostream& s, const Mixed& m);
	
	friend bool operator<(const Mixed& m1, const Mixed& m2);
	friend bool operator>(const Mixed& m1, const Mixed& m2); 
	friend bool operator<=(const Mixed& m1, const Mixed& m2); 
	friend bool operator>=(const Mixed& m1, const Mixed& m2); 
	friend bool operator==(const Mixed& m1, const Mixed& m2); 
	friend bool operator!=(const Mixed& m1, const Mixed& m2);   

	friend Mixed operator+(const Mixed& m1, const Mixed& m2); 
	friend Mixed operator-(const Mixed& m1, const Mixed& m2);
	friend Mixed operator*(const Mixed& m1, const Mixed& m2); 
	friend Mixed operator/(const Mixed& m1, const Mixed& m2); 

	public:
		// constructor
		Mixed(int i, int n, int d);
		Mixed(int i = 0); // conversion constructor
		
		// accesors and non-mutators
		double Evaluate() const;

		// mutators
		void ToFraction();
		void Simplify();
		
		// prefix 
		Mixed& operator++();            
        Mixed& operator--();
		
		// postfix 
		Mixed& operator++(int n);            
        Mixed& operator--(int n);


	private:
		int integer;
		int numerator;
		int denominator; // non-zero numbers

		int GreatestCommonFactor(int x, int y); // helper function
		int AbsoluteValue(int x); // helper function
};

		 
