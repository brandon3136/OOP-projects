#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
const string studentDb = "studentsDb.txt";
const string attendanceFile = "attendance.txt";
int opt = 0;

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

int main()
{
    cout << "WELCOME TO THE ATTENDANCE SYSTEM\n"
         << endl;
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
                cout << "\nExiting from adding present students, go to \"attendance.txt\" for the attendance made" << endl;
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