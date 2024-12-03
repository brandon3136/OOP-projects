#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;
const string studentDb = "studentsDb.txt";

struct StudentStruct {
    string name;
    long long regNumber;
    string phoneNo;

    void display() const{
        cout << "Name: " << name<< "________Registration No.: " << regNumber  << "______Phone No.: " << phoneNo  <<"\n\n";
    }
};

void addStudent();
void deleteStudent();
vector<StudentStruct> loadStudent();
void readStudent();
void saveStudents(const vector<StudentStruct>& studentsVect);

int main(){
    cout << "WELCOME TO THE ATTENDANCE PROGRAM" << endl;

    int choice;

    do{
        cout << "---- Student attendance system ----" << endl;
        cout << "1. Add student details" << endl;
        cout << "2. Delete student details" << endl;
        cout << "3. Read student details" << endl;
        cout << "4. Exit" << endl;

        cout<<"\n\nEnter your choice (1-4): ";
        cin >> choice;

        switch(choice){
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
                cout << "Exiting...";
                break;
            default:
                cout << "\nWrong Input!, please input (1-4)\n"
                     << endl;
                break;
        }
    } while (choice != 4);
}

void addStudent(){
    vector<StudentStruct> studentsVect = loadStudent();
    int numStudents;
    cout << "How many students do you want to add: ";
    cin >> numStudents;
    cin.ignore();
    StudentStruct s;

    for (int i = 0; i < numStudents; i++){
    
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
            cout << "This service is currently not available\n\n " << endl;
        }

vector<StudentStruct> loadStudent() {
    vector<StudentStruct> studentsVect;
    ifstream file(studentDb);

    if (file.is_open()) {
        StudentStruct s;
        string regNumString;

        while (getline(file, regNumString)) { 
            s.regNumber = stoll(regNumString);  // Convert string to long long
            getline(file, s.name);
            getline(file, s.phoneNo);
            studentsVect.push_back(s);
        }

        file.close();
    }
    return studentsVect;
}


void readStudent(){
    vector<StudentStruct> studentVect = loadStudent();
    int count = 1;

    if(!studentVect.empty()){
        for(const auto& s : studentVect){
            cout << "(" << count << ") ";
            s.display();
            count += 1;
        }
    }else{
        cout << "Student data not found" << endl;
    }
    //cout << "This service is currently not available\n\n"<< endl;
}

void saveStudents(const vector<StudentStruct>& studentsVect){
    ofstream file(studentDb, ios::trunc);
    if (file.is_open()) {
        for (const auto& s : studentsVect) {
            file << s.regNumber<< "\n"  << s.name <<"\n"  << s.phoneNo << endl;
        }
        
        file.close();
    }
}
