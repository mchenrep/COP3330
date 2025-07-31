class Date
{
	public:
		Date();
		Date(int m, int d, int y);

		void Input();
		void Show() const;

		int GetMonth() const;
		int GetDay() const;
		int GetYear() const;
		int Compare(const Date& d) const;

		bool Set(int m, int d, int y);		
		bool SetFormat(char f);
		void Increment(int numDays = 1);
		
	private:
		int month;
		int day;
		int year;
		char format;
		bool EndOfTheMonth(int m) const;
		bool IsLeapYear(int m) const;
};
