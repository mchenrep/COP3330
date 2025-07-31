// Matthew Chen Section 6
#include <iostream>
#include <fstream>
#include <string>
#include "studentlist.h"

using namespace std;

ostream& operator<<(ostream& os, const Student& s)
{
    os<<s.getLastName()<<"\t"<<s.getFirstName()<<"\t"<<s.getCourse()<<"\n";
    return os;
}

StudentList::StudentList()
{
    list = new Student*[5];
    size = 0;
}

StudentList::~StudentList()
{
    delete [] list;
}

bool StudentList::ImportFile(const char* filename)
{
    ifstream in;
    int lines = 0;
    in.open(filename);
    if(!in)
    {
        cout<<"Invalid file. No data imported\n";
        return false;
    }
    in>>lines;
    for(int i = 0; i < lines; i++)
    {
        string fn, ln, c;
        char space;
        getline(in,ln, ',');
        in.ignore();
        getline(in,fn);
        in>>c;
        if(c == "English")
        {
            int a,p,m,f;
            in>>a>>p>>m>>f;
            EStudent * e = new EStudent(fn,ln,English,a,p,m,f);
            grow();
            list[size-1] = e;
        }
        if(c == "History")
        {
            int t,m,f;
            in>>t>>m>>f;
            HStudent * h = new HStudent(fn,ln,History,t,m,f);
            grow();
            list[size-1] = h;
        }
        if(c == "Math")
        {
            int q1,q2,q3,q4,q5,t1,t2,f;
            in>>q1>>q2>>q3>>q4>>q5>>t1>>t2>>f;
            double qa = (q1+q2+q3+q4+q5)/5.0;
            MStudent *m = new MStudent(fn,ln,Math,qa,t1,t2,f);
            grow();
            list[size-1] = m;
        }
        in.ignore();
    }
    in.close();
    return true;
}

bool StudentList::CreateReportFile(const char* filename)
{
    ofstream out;
    int a = 0,b = 0,c = 0,d = 0,f = 0;
    out.open(filename);
    if(!out)
    {
        cout<<"Invalid file. No data imported\n";
        return false;
    }
    out<<"Student Grade Summary\n---------------------\n\n";
    out<<"ENGLISH CLASS\n\n";
    out<<"Student\t\tFinal Final\tLetter\n";
    out<<"Name   \t\tExam  Avg\t  Grade\n----------------------------------------------------------------------\n";
    for(int i = 0; i < size; i++)
    {
        if(list[i]->getCourse() == "English")
        {
            out<<list[i]->getFirstName()<<" "<<list[i]->getLastName()<<"\t\t"<<list[i]->getFinal()<<" "<<list[i]->finalGrade()<<" "<<list[i]->letterGrade()<<"\n";
            if(list[i]->letterGrade() ==  'A')
                a++;
            if(list[i]->letterGrade() =='B')
                b++;
            if(list[i]->letterGrade() =='C')
                c++;
            if(list[i]->letterGrade() == 'D')
                d++;
            if(list[i]->letterGrade() == 'F')
                f++;
        }
    }
    out<<"\nHISTORY CLASS\n\n";
    out<<"Student\t\tFinal Final\tLetter\n";
    out<<"Name   \t\tExam  Avg\t   Grade\n----------------------------------------------------------------------\n";
    for(int i = 0; i < size; i++)
    {
        if(list[i]->getCourse() == "History")
        {
            out<<list[i]->getFirstName()<<" "<<list[i]->getLastName()<<"\t\t"<<list[i]->getFinal()<<" "<<list[i]->finalGrade()<<" "<<list[i]->letterGrade()<<"\n";
            if(list[i]->letterGrade() ==  'A')
                a++;
            if(list[i]->letterGrade() =='B')
                b++;
            if(list[i]->letterGrade() =='C')
                c++;
            if(list[i]->letterGrade() == 'D')
                d++;
            if(list[i]->letterGrade() == 'F')
                f++;
        }
    }
    out<<"\nMATH CLASS\n\n";
    out<<"Student\t\tFinal Final\tLetter\n";
    out<<"Name   \t\tExam  Avg\t   Grade\n----------------------------------------------------------------------\n";
    for(int i = 0; i < size; i++)
    {
        if(list[i]->getCourse() == "Math")
        {
            out<<list[i]->getFirstName()<<" "<<list[i]->getLastName()<<"\t\t"<<list[i]->getFinal()<<" "<<list[i]->finalGrade()<<" "<<list[i]->letterGrade()<<"\n";
            if(list[i]->letterGrade() ==  'A')
                a++;
            if(list[i]->letterGrade() =='B')
                b++;
            if(list[i]->letterGrade() =='C')
                c++;
            if(list[i]->letterGrade() == 'D')
                d++;
            if(list[i]->letterGrade() == 'F')
                f++;
        }
    }
    out<<"\n\nOVERALL GRADE DISTRIBUTION\n\n\nA:\t"<<a<<"\nB:\t"<<b<<"\nC:\t"<<c<<"\nD:\t"<<d<<"\nF:\t"<<f<<"\n";
    out.close();
    return true;
}

void StudentList::ShowList() const
{
    cout<<"Last\tFirst\tCourse\n";
    for(int i = 0; i < size; i++)
    {
        cout<<*list[i]<<"\n";
    } 
}

Student::Student(string f, string l, course co)
{
    fn = f;
    ln = l;
    c = co;
}

Student::~Student()
{
}

string Student::getFirstName() const
{
    return fn;
}

string Student::getLastName() const
{
    return ln;
}

string Student::getCourse() const
{
    if(c == English)
        return "English";
    if(c == History)
        return "History";
    if(c == Math)
        return "Math";
}

double Student::finalGrade() const
{
}
int Student::getFinal() const
{
}

char Student::letterGrade() const
{
    double f = finalGrade();
    if(f >= 90 && f <= 100)
        return 'A';
    if(f >= 80 && f < 90)
        return 'B';
    if(f >= 70 && f <= 80)
        return 'C';
    if(f >= 60 && f <= 70)
        return 'D';
    return 'F';
}

EStudent::~EStudent()
{
}

EStudent::EStudent(string fn, string ln, course c, double a, double p, double m, double f) : Student(fn, ln, c)
{
    attendance = a;
    project = p;
    midterm = m;
    fin = f;
}

double EStudent::finalGrade() const
{
    return ((attendance/100.)*10) + ((project/100)*30) + ((midterm/100.)*30) + ((fin/100.)*30);
}

int EStudent::getFinal() const
{
    return fin;
}

HStudent::~HStudent()
{
}

HStudent::HStudent(string fn, string ln, course c, double t, double m, double f) : Student(fn, ln, c)
{
    termpaper = t;
    midterm = m;
    fin = f;
}

double HStudent::finalGrade() const
{
    return ((termpaper/100.)*25) + ((midterm/100.)*35) + ((fin/100.)*40);
}

int HStudent::getFinal() const
{
    return fin;
}

MStudent::~MStudent()
{
}

MStudent::MStudent(string fn, string ln, course c, double qa, double t1, double t2, double f) : Student(fn,ln,c)
{
    quizavg = qa;
    test1 = t1;
    test2 = t2;
    fin = f;
}

double MStudent::finalGrade() const
{
    return ((quizavg/100.)*15) + ((test1/100.)*25) + ((test2/100.)*25) + ((fin/100.)*35);
}

int MStudent::getFinal() const
{
    return fin;
}

void StudentList::grow()
{
    Student ** p = list;
    list = new Student*[size+5];
    size++;
    for(int i = 0; i < size; i++)
        list[i] = p[i];
    delete [] p;
}

void StudentList::sort()
{
    for(int i = 0; i < size-1; i++)
    {
        for(int j = i+1; j < size; j++)
        {
            if(list[j]->getLastName().compare(list[i]->getLastName()) < 0)
            {
                Student * t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
        }
    }
}