#include<iostream>
using namespace std;

#define MAX_SIZE 20

class StudentMarks {
public:
    int numStudents;
    int* marks;;

    // Function to heapify the max heap
    void maxHeapify(int arr[], int i, int n) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int largest = i;

        if (left <= n && arr[left] > arr[largest])
            largest = left;
        if (right <= n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeapify(arr, largest, n);
        }
    }

    // Function to build the max heap
    void buildMaxHeap(int arr[], int n) {
        for (int i = n / 2; i >= 1; i--) {
            maxHeapify(arr, i, n);
        }
    }

    // Function to sort the array using heap sort
    void heapSort(int arr[], int n) {
        buildMaxHeap(arr, n);
        for (int i = n; i >= 2; i--) {
            swap(arr[i], arr[1]);
            maxHeapify(arr, 1, i - 1);
        }
    }

    // Function to accept marks from the user
    void acceptMarks() {
        cout << "\nEnter the number of students: ";
        cin >> numStudents;

        int marks[numStudents+1];
        cout << "\nEnter the marks of students: ";
        for (int i = 1; i <= numStudents; i++) {
            cin >> marks[i];
        }
        heapSort(marks, numStudents);
    }

    // Function to display sorted marks
    void displaySortedMarks() {
        cout << "\n*** Sorted Marks ***" << endl;
        for (int i = 1; i <= numStudents; i++) {
            cout << marks[i] << endl;
        }
    }

    // Function to display the maximum mark
    void displayMaxMark() {
        cout << "\nMaximum marks obtained: " << marks[numStudents] << endl;
    }

    // Function to display the minimum mark
    void displayMinMark() {
        cout << "Minimum marks obtained: " << marks[1] << endl;
    }
};

int main() {
    StudentMarks studentMarks;

    // Accept student marks and sort them
    studentMarks.acceptMarks();

    // Display sorted marks
    studentMarks.displaySortedMarks();

    // Display maximum and minimum marks
    studentMarks.displayMaxMark();
    studentMarks.displayMinMark();

    return 0;
}
