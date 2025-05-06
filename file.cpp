#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
    int roll_no;
    char name[50];
    char division[5];
    char addr[100];

public:
    void setData() {
        cout << "Enter Roll No.: ";
        cin >> roll_no;
        cin.ignore();  // To clear any remaining newline character in the buffer
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Division: ";
        cin.getline(division, 5);
        cout << "Enter Address: ";
        cin.getline(addr, 100);
    }

    void showData() {
        cout << "\nRoll No: " << roll_no << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << addr << endl;
        cout << "-----------------------------\n";
    }

    int getRollNo() const {
        return roll_no;
    }

    // For file handling, let's serialize the student object
    void writeToFile(ofstream& outFile) {
        outFile.write((char*)this, sizeof(*this));
    }

    void readFromFile(ifstream& inFile) {
        inFile.read((char*)this, sizeof(*this));
    }

    bool isEqual(int roll) {
        return roll_no == roll;
    }
};

// Function to add a student record
void addStudent() {
    ofstream outFile;
    outFile.open("students.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    student.setData();
    student.writeToFile(outFile);
    outFile.close();
    cout << "Student record added successfully!" << endl;
}

// Function to display a student record based on roll number
void displayStudent() {
    int roll;
    cout << "Enter Roll No. to display: ";
    cin >> roll;

    ifstream inFile;
    inFile.open("students.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student student;
    bool found = false;
    while (inFile.read((char*)&student, sizeof(student))) {
        if (student.isEqual(roll)) {
            student.showData();
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Record not found!" << endl;
    }
    inFile.close();
}

// Function to delete a student record based on roll number
void deleteStudent() {
    int roll;
    cout << "Enter Roll No. to delete: ";
    cin >> roll;

    ifstream inFile;
    inFile.open("students.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    ofstream outFile;
    outFile.open("temp.dat", ios::binary);

    Student student;
    bool found = false;
    while (inFile.read((char*)&student, sizeof(student))) {
        if (student.isEqual(roll)) {
            found = true;
        } else {
            student.writeToFile(outFile);
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        cout << "Record deleted successfully!" << endl;
    } else {
        cout << "Record not found!" << endl;
        remove("temp.dat"); // If not found, remove the temporary file
    }
}

int main() {
    // Example of adding a student
    addStudent();

    // Example of displaying a student
    displayStudent();

    // Example of deleting a student
    deleteStudent();

    return 0;
}
