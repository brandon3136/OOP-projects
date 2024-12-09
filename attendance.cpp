#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
const string studentDb = "studentsDb.txt";
const string attendanceFile = "attendance.txt";
const string signFile = "Account Info.txt";
int opt = 0;

struct SignStruct
{
    bool alreadySigned = false;
    string username;
    string year;
    string programme;
    string semester;
    vector<string> course;
};

struct StudentStruct
{
    string name;
    string regNumber;
    string phoneNo;

    void display() const
    {
        cout << left << setw(40) << name
             << setw(20) << regNumber
             << setw(20) << phoneNo << "\n";
    }
};

void addStudent();
void deleteStudent();
vector<StudentStruct> loadStudent();
void readStudent();
void saveStudents(const vector<StudentStruct> &studentsVect);
void studentDetailsMenu();
void attendance();
void mainMenu();
void signing();
SignStruct loadSignDetails();

int main()
{

    cout << "WELCOME TO THE ATTENDANCE SYSTEM\n"
         << endl;

    SignStruct s = loadSignDetails();

    // cout << s.alreadySigned<<endl;

    if (!s.alreadySigned)
    {
        signing();
    }

    mainMenu();
    return 0;
}

void addStudent()
{
    vector<StudentStruct> studentsVect = loadStudent();
    int numStudents;
    cout << "How many students do you want to add: ";
    cin >> numStudents;
    cin.ignore();
    StudentStruct s;

    for (int i = 1; i <= numStudents; i++)
    {
        cout << "\t\t\tSTUDENT " << i << endl;
        cout << "Enter the full name of the student: ";
        getline(cin, s.name);

        cout << "Enter the registration number: ";
        cin >> s.regNumber;

        cout << "Enter Phone number: ";
        cin >> s.phoneNo;
        cout << endl;

        cin.ignore();
        studentsVect.push_back(s);
    }

    saveStudents(studentsVect);
    cout << "Student's details added successfully" << endl;
}

void deleteStudent()
{
    vector<StudentStruct> studentVect = loadStudent();
    string r;
    bool found = false;

    if (studentVect.empty())
    {
        cout << "Student data not found!, unable to delete students' details" << endl;
    }
    else
    {
        cout << "Enter the student's registration number to delete: ";
        cin >> r;
        for (auto i = studentVect.begin(); i != studentVect.end(); i++)
        {
            if (i->regNumber == r)
            {
                found = true;
                studentVect.erase(i);
                saveStudents(studentVect);
                cout << "The student has been deleted successfully\n"
                     << endl;
            }
        }
        if (!found)
        {
            cout << "The student is not found!"
                 << endl;
        }
    }
}

vector<StudentStruct> loadStudent()
{
    vector<StudentStruct> studentsVect;
    ifstream file(studentDb);

    if (file.is_open())
    {
        StudentStruct s;
        while (getline(file, s.regNumber))
        {
            getline(file, s.name);
            getline(file, s.phoneNo);
            studentsVect.push_back(s);
        }

        file.close();
    }
    return studentsVect;
}

void readStudent()
{
    vector<StudentStruct> studentVect = loadStudent();
    int count = 1;

    if (!studentVect.empty())
    {
        cout << "\n---------- Student Details --------" << endl;
        cout << left << setw(5) << "No."
             << setw(40) << "Student's Name"
             << setw(20) << "Registration No."
             << setw(20) << "Phone No." << endl;

        for (const auto &s : studentVect)
        {
            cout << left << setw(5) << count;
            s.display();
            count += 1;
        }
    }
    else
    {
        cout << "Student data not found!, unable to read students' details" << endl;
    }
    cout << endl;
}

void saveStudents(const vector<StudentStruct> &studentsVect)
{
    ofstream file(studentDb, ios::trunc);
    if (file.is_open())
    {
        for (const auto &s : studentsVect)
        {
            file << s.regNumber << "\n"
                 << s.name << "\n"
                 << s.phoneNo << endl;
        }

        file.close();
    }
}

void studentDetailsMenu()
{
    int choice;
    do
    {
        cout << "\n------- STUDENT DETAILS MENU -------" << endl;
        cout << "1. Add student details" << endl;
        cout << "2. Delete student details" << endl;
        cout << "3. Read student details" << endl;
        cout << "4. Back to main menu" << endl;

        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.clear();

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            deleteStudent();
            break;
        case 3:
            readStudent();
            break;
        case 4:
            cin.clear();
            mainMenu();
            break;
        default:
            cout << "\nWrong Input!, please input (1-4)\n"
                 << endl;
            break;
        }
    } while (choice != 4);
}

void attendance()
{
    vector<StudentStruct> studentVect = loadStudent();
    if (studentVect.empty())
    {
        cout << "No student data found, Unable to make an attendance file" << endl;
    }
    else
    {
        cout << "\n--------Making an Attendace---------" << endl;
        bool cont = false;
        string date;
        string tempReg;
        vector<string> tempVect;
        int count = 1;

        ofstream file(attendanceFile);
        cout << "Enter the date: ";
        cin.ignore();
        getline(cin, date);
        if (file.is_open())
        {
            file << "DATE: " << date << endl;
            file << left << setw(5) << "No."
                 << setw(30) << "Student's name"
                 << setw(20) << "Registration No."
                 << setw(20) << "Phone No."
                 << endl;
        }

        while (true)
        {
            cout << "Enter registration no. (To exit press \'quit\') : ";
            getline(cin, tempReg);
            bool already = false;

            if (tempReg == "quit")
            {
                cout << "\nExiting from adding present students, go to \"attendance.txt\" for the attendance made\n"
                     << endl;
                break;
            }
            else
            {
                bool found = false;
                for (auto &i : studentVect)
                {
                    if (i.regNumber == tempReg)
                    {
                        for (string s : tempVect)
                        {
                            if (tempReg == s)
                            {
                                already = true;
                                cout << "This student has already been added" << endl;
                            }
                        }
                        if (!already)
                        {

                            tempVect.push_back(tempReg);

                            found = true;
                            cout << "ACCEPT" << endl;
                            if (file.is_open())
                            {
                                file << left << setw(5) << count
                                     << setw(30) << i.name
                                     << setw(20) << i.regNumber
                                     << setw(20) << i.phoneNo
                                     << endl;
                            }
                            count += 1;
                        }
                    }
                }
                if (!found && !already)
                {
                    cout << "DENIED. student not found" << endl;
                }
            }
        }
        file.close();
        mainMenu();
    }
}

void mainMenu()
{
    while (opt != 3)
    {
        cout << "------ MAIN MENU -------" << endl;
        cout << "1. Issues about student details" << endl;
        cout << "2. Make an attendance" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> opt;

        switch (opt)
        {
        case 1:
            studentDetailsMenu();
            break;
        case 2:
            attendance();
            break;
        case 3:
            cout << "Exiting...";
            break;
        default:
            cout << "\nWrong Input!, please input (1-3)\n"
                 << endl;
            break;
        }
    }
}

void signing()
{
    cout << "-------- Sign In to the attendance system -------" << endl;
    SignStruct s;

    cout << "Enter your Name: ";
    getline(cin, s.username);

    cout << "Enter name of the Programme: ";
    getline(cin, s.programme);
    cout << endl;

    int yearChoice = 0;
    do
    {
        cout << "Year of study" << endl;
        cout << "1. First Year" << endl;
        cout << "2. Second Year" << endl;
        cout << "3. Third Year" << endl;
        cout << "4. Fourth Year\n"
             << endl;

        cout << "Enter your choice(1-4): ";
        cin >> yearChoice;

        switch (yearChoice)
        {
        case 1:
            s.year = "First Year";
            break;
        case 2:
            s.year = "Second Year";
            break;
        case 3:
            s.year = "Third Year";
            break;

        case 4:
            s.year = "Fourth Year";
            break;
        default:
            cout << "\nWrong Input!, Try again\n"
                 << endl;
            break;
        }
    } while (!(yearChoice <= 4 && yearChoice > 0));

    int semChoice = 0;
    do
    {
        cout << "\nSemester" << endl;
        cout << "1. Semester I" << endl;
        cout << "2. Semester II" << endl;

        cout << "Enter your choice(1-2): ";
        cin >> semChoice;

        switch (semChoice)
        {
        case 1:
            s.semester = "I";
            break;
        case 2:
            s.semester = "II";
            break;

        default:
            cout << "\nWrong Input!, Try again\n"
                 << endl;
            break;
        }
    } while (!(semChoice <= 2 && semChoice > 0));

    int numCourse = 0;
    cout << "Number of courses(modules) do you have for this semester? : ";
    cin >> numCourse;

    cout << "Enter the courses below:" << endl;
    cin.ignore();

    for (int i = 1; i <= numCourse; i++)
    {
        string courseTemp;
        cout << i << " - ";
        getline(cin, courseTemp);

        s.course.push_back(courseTemp);
    }

    s.alreadySigned = true;

    ofstream file(signFile);
    if (file.is_open())
    {
        file << s.username << endl
             << s.programme << endl
             << s.year << endl
             << s.semester << endl
             << s.alreadySigned << endl;

        for (auto &i : s.course)
        {
            file << i << endl;
        }
    }

    cout << "------ sign in complete, Enjoy our program -------\n"
         << endl;
}

SignStruct loadSignDetails()
{
    SignStruct s;

    ifstream file(signFile);
    if (file.is_open())
    {
        getline(file, s.username);
        getline(file, s.programme);
        getline(file, s.year);
        getline(file, s.semester);

        file >> s.alreadySigned;

        string courseTemp;

        while (getline(file, courseTemp))
        {
            s.course.push_back(courseTemp);
        }
    }
    return s;
}