// base of house is a SQUARE, roof of house is an EQUILATERAL TRIANGLE which hangs 1 unit further than the base (so each side is 2 + base side)

class House
{
	public:
		House(int s, char b, char f); // constructor with parameters for size, border, and fill

		// Accessor functions
		int GetSize() const;
		int Perimeter() const;
		double Area() const;

		// Mutator functions
		void Grow();
		void Shrink();
		void setBorder(char c);
		void setFill(char c);
		void Draw() const;
		void Summary() const;

	private:
		int size; // size of the base
		char border;
		char fill;

};
