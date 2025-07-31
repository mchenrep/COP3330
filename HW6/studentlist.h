// Matthew Chen Section 6
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum course{English, History, Math};


class Student
{
    friend ostream& operator<<(ostream& os, const Student& s);
    public:
        Student();
        ~Student();
        Student(string, string, course co);
        string getFirstName() const;
        string getLastName() const;
        string getCourse() const;
        virtual double finalGrade() const;
        virtual int getFinal() const;
        char letterGrade() const;
    protected:
        string fn, ln;
        course c;
        double grade;
};

class EStudent : public Student
{
    public:
        ~EStudent();
        EStudent(string fn, string ln, course c, double a, double p, double m, double f);
        virtual double finalGrade() const;
        virtual int getFinal() const;
        char letterGrade() const;
    private:
        double attendance;
        double project;
        double midterm;
        double fin;
};

class HStudent : public Student
{
    public:
        ~HStudent();
        HStudent(string fn, string ln, course c, double t, double m, double f);
        virtual double finalGrade() const;
        virtual int getFinal() const;
        char letterGrade() const;
    private:
        double termpaper;
        double midterm;
        double fin;
};

class MStudent : public Student
{
    public:
        ~MStudent();
        MStudent(string fn, string ln, course c, double qa, double t1, double t2, double f);
        virtual double finalGrade() const;
        virtual int getFinal() const;
        char letterGrade() const;
    private:
        double quizavg;
        double test1;
        double test2;
        double fin;
};

class StudentList
{
    public:
        StudentList();
        ~StudentList();
        bool ImportFile(const char* filename);
        bool CreateReportFile(const char* filename);
        void ShowList() const;
        void sort();
    private:
        int size;
        Student ** list;
        void grow();
};
