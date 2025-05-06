#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Student
{
    int roll_no;
    char name[50];
    char addr[50];

public:
    void setData()
    {
        cout << "Enter Roll No.: ";
        cin >> roll_no;
        cout << "Enter name of student: ";
        cin >> name;
        cout << "Enter the address of the student: ";
        cin >> addr;
    }
    void showData()
    {
        cout << endl;
        cout << "Roll no. : " << roll_no << endl;
        cout << "Student name : " << name << endl;
        cout << "Address : " << addr << endl;
    }
    int retroll_no()
    {
        return roll_no;
    }
};

void write_record()
{
    ofstream outFile;
    outFile.open("student.dat", ios::binary | ios::app);
    Student obj;

    obj.setData();
    outFile.write((char*)&obj, sizeof(obj));
    outFile.close();
}

void display()
{
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    Student obj;
    while (inFile.read((char*)&obj, sizeof(obj)))
    {
        obj.showData();
    }

    inFile.close();
}

void search(int n)
{
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    Student obj;
    bool found = false;
    while (inFile.read((char*)&obj, sizeof(obj)))
    {
        if (obj.retroll_no() == n)
        {
            obj.showData();
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Record not found." << endl;
    }
    inFile.close();
}

void delete_record(int n)
{
    Student obj;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    ofstream outFile;
    outFile.open("temp.dat", ios::binary);
    while (inFile.read((char*)&obj, sizeof(obj)))
    {
        if (obj.retroll_no() != n)
        {
            outFile.write((char*)&obj, sizeof(obj));
        }
    }
    inFile.close();
    outFile.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
}

void modify_record(int n)
{
    fstream file;
    file.open("student.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "File not found or could not be opened." << endl;
        return;
    }

    Student obj;
    bool found = false;
    while (file.read((char*)&obj, sizeof(obj)))
    {
        if (obj.retroll_no() == n)
        {
            cout << "\nEnter the new details of student:" << endl;
            obj.setData();
            long int pos = file.tellg() - static_cast<long int>(sizeof(obj));
            file.seekp(pos);
            file.write((char*)&obj, sizeof(obj));
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Record not found." << endl;
    }
    file.close();
}

int main()
{
    int ch;
    do
    {
        cout << "\n*** Menu ***" << endl;
        cout << "1. Write" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Modify" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter number of records: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++)
                write_record();
            break;
        case 2:
            cout << "List of records:" << endl;
            display();
            break;
        case 3:
            cout << "Enter Roll No. to be searched: ";
            int s;
            cin >> s;
            search(s);
            break;
        case 4:
            cout << "Enter Roll No. to be deleted: ";
            int d;
            cin >> d;
            delete_record(d);
            cout << "Record Deleted!" << endl;
            break;
        case 5:
            cout << "Enter Roll No. to be modified: ";
            int m;
            cin >> m;
            modify_record(m);
            break;
        case 6:
            cout << "Thanks for using this Program!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (ch != 6);
}
