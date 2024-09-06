#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class student
{
	int rollno;
	char name[50];
	int csd_marks, beee_marks, eees_marks, itp_marks, maths_marks;
	double per;
	char grade;
	void calculate();

public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int retrollno() const;
};
void student::calculate()
{
	per = (csd_marks + beee_marks + eees_marks + itp_marks + maths_marks) / 5.0;
	if (per >= 17)
		grade = 'A';
	else if (per >= 14)
		grade = 'B';
	else if (per >= 10)
		grade = 'C';
	else
		grade = 'F';
}

void student::getdata()
{
	cout << "\nEnter The roll number of student ";
	cin >> rollno;
	cout << "\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter The marks in csd out of 20 : ";
	cin >> csd_marks;
	cout << "\nEnter The marks in beee out of 20 : ";
	cin >> beee_marks;
	cout << "\nEnter The marks in eees out of 20 : ";
	cin >> eees_marks;
	cout << "\nEnter The marks in itp out of 20 : ";
	cin >> itp_marks;
	cout << "\nEnter The marks in maths out of 20 : ";
	cin >> maths_marks;
	calculate();
}

void student::showdata() const
{
	cout << "\nRoll number of student : " << rollno;
	cout << "\nName of student : " << name;
	cout << "\nMarks in csd : " << csd_marks;
	cout << "\nMarks in beee : " << beee_marks;
	cout << "\nMarks in eees : " << eees_marks;
	cout << "\nMarks in itp : " << itp_marks;
	cout << "\nMarks in maths :" << maths_marks;
	cout << "\nPercentage of student is  :" << per;
	cout << "\nGrade of student is :" << grade;
}

void student::show_tabular() const
{
	cout << rollno << setw(6) << " " << name << setw(10) << csd_marks << setw(4) << beee_marks << setw(4) << eees_marks << setw(4)
		 << itp_marks << setw(4) << maths_marks << setw(8) << per << setw(6) << grade << endl;
}

int student::retrollno() const
{
	return rollno;
}

void write_student();
void display_all();
void display_sp(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();

int main()
{
	char ch;
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2);
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tWELCOME TO RESULT DAY";
		cout << "\n\n\t01. RESULT ";
		cout << "\n\n\t02. ENTER OR DELETE RESULT ";
		cout << "\n\n\t03. EXIT";
		cout << "\n\n\tPLEASE Select (1-3) ";
		cin >> ch;
		switch (ch)
		{
		case '1':
			result();
			break;
		case '2':
			entry_menu();
			break;
		case '3':
			break;
		default:
			cout << "\a";
		}
	} while (ch != '3');
	return 0;
}

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat", ios::binary | ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *>(&st), sizeof(student));
	outFile.close();
	cout << "\n\nStudent record  Created ";
	cin.ignore();
	cin.get();
}

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press ENTER ...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
	{
		st.showdata();
		cout << "\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press ENTER ...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
	{
		if (st.retrollno() == n)
		{
			st.showdata();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press ENTER ...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
	{
		if (st.retrollno() != n)
		{
			outFile.write(reinterpret_cast<char *>(&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\t\tALL STUDENTS RESULT \n\n";
	cout << "==========================================================\n";
	cout << "R.No    Name    csd  beee  eees  itp  maths  %age  Grade" << endl;
	cout << "==========================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

void result()
{
	char ch;
	int rno;
	system("cls");
	cout << "\n\n\n\tRESULT ";
	cout << "\n\n\n\t1. Class Report Card ";
	cout << "\n\n\t2. Student Report Card";
	cout << "\n\n\t3. main page ";
	cout << "\n\n\n\tplease select one Choice (1/2/3)? ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		class_result();
		break;
	case '2':
		cout << "\n\n\tEnter Roll Number Of Student : ";
		cin >> rno;
		display_sp(rno);
		break;
	case '3':
		break;
	default:
		cout << "\a";
	}
}

void intro()
{
	cout << "\n\n\n\t\t  PROJECT";
	cout << "\n\n\t\t STUDENT REPORT CARD SYSTEM";
	cout << "\n\n\n\tMADE BY :  aditya singh chauhan" << endl;
	cout << "\t\t   kusum barothiya" << endl;
	cout << "\t\t   ayush pratap singh" << endl;
	cout << "\n\tcollege : mits (gwalior)";
	cin.get();
}

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout << "\n\n\n\tENTER MENU";
	cout << "\n\n\t1.MAKE STUDENT RECORD";
	cout << "\n\n\t2.SHOW ALL STUDENTS RECORDS";
	cout << "\n\n\t3.DELETE STUDENT RECORD";
	cout << "\n\n\t4.MAIN PAGE";
	cout << "\n\n\tplease select one Choice (1-4) ";
	cin >> ch;
	system("cls");
	switch (ch)
	{
	case '1':
		write_student();
		break;
	case '2':
		display_all();
		break;
        case '3':
		cout << "\n\n\tPlease Enter The roll number ";
		cin >> num;
		delete_student(num);
		break;
	case '4':
		break;
	default:
		cout << "\a";
		entry_menu();
	}
}
