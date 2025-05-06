#include <iostream>
#include <fstream>
#include <cstring>  // Include this header for strncpy
using namespace std;

class Record {
    int id;
    char name[50];

public:
    // Constructor to initialize record
    Record() : id(0) {
        name[0] = '\0';
    }

    // Set data for a record
    void setData(int id, const char* name) {
        this->id = id;
        strncpy(this->name, name, 50);
        this->name[49] = '\0'; // Ensure the name is null-terminated
    }

    // Display record data
    void showData() const {
        cout << "ID: " << id << ", Name: " << name << endl;
    }

    // Getter for ID
    int getId() const {
        return id;
    }

    // Write record to a specific position in the file
    void writeToFile(fstream& file, long position) {
        file.seekp(position * sizeof(Record), ios::beg);
        file.write((char*)this, sizeof(Record));
    }

    // Read record from a specific position in the file
    void readFromFile(fstream& file, long position) {
        file.seekg(position * sizeof(Record), ios::beg);
        file.read((char*)this, sizeof(Record));
    }
};

// Insert a record at the end of the file
void insertRecord(fstream& file, int id, const char* name) {
    Record record;
    record.setData(id, name);
    
    // Move to the end of the file and insert the record
    file.seekp(0, ios::end);
    long position = file.tellp() / sizeof(Record);
    record.writeToFile(file, position);
    cout << "Record inserted successfully at position: " << position << endl;
}

// Delete a record (set it to a default state)
void deleteRecord(fstream& file, int id) {
    fstream tempFile("temp.dat", ios::out | ios::binary);
    Record record;
    bool found = false;
    
    file.seekg(0, ios::beg);
    
    while (file.read((char*)&record, sizeof(record))) {
        if (record.getId() == id) {
            found = true;
            cout << "Record with ID " << id << " found and deleted." << endl;
        } else {
            // Write the record to the temporary file
            tempFile.write((char*)&record, sizeof(record));
        }
    }

    if (!found) {
        cout << "Record with ID " << id << " not found." << endl;
    }

    file.close();
    tempFile.close();

    // Remove the original file and rename temp file
    remove("records.dat");
    rename("temp.dat", "records.dat");
}

int main() {
    fstream file("records.dat", ios::in | ios::out | ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    // Example: Insert a record
    insertRecord(file, 1, "John Doe");

    // Example: Insert another record
    insertRecord(file, 2, "Jane Smith");

    // Example: Delete a record
    deleteRecord(file, 1);

    file.close();
    return 0;
}
