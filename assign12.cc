#include <iostream>
#include <cmath>
using namespace std;

void sortIntArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int a = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = a;
            }
        }
    }
}

int linearSearch(int elem, int *arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == elem)
            return i;
    }
    return -1;
}

int binarySearch(int elem, int *arr, int size) {
    int start = 0;
    int end = size - 1;
    while(start <= end) {
        int mid = (end + start) / 2;
        if (arr[mid] == elem)
            return mid;
        if (arr[mid] > elem) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return -1;
}

int jumpSearch(int elem, int *arr, int size) {
    int block = sqrt(size);
    for (int i = 0; i < size; i += block + 1) {
        int last;
        if (i >= size) {
            last = arr[size - 1];
        } else {
            last = arr[i + block];
        }

        if (last == elem)
            return i;
        
        if (last > elem) {
            int binSearch = linearSearch(elem, &arr[i], block);
            if (binSearch != -1)
                return i + binSearch;
        }
    }
    return -1;
}

int main() {
    int rollNos[] = {67, 41, 36, 85, 10, 65, 21, 74, 20, 64, 82, 57, 11, 88, 62, 99, 46, 91, 72, 22, 34, 1};
    int size = sizeof(rollNos) / sizeof(int);
    cout << "Sorting the roll number list..." << endl;
    sortIntArr(rollNos, size);
    for (int i : rollNos) {
        cout << i << " ";
    }
    cout << endl;

    int roll;
    cout << "Enter the roll of student: ";
    cin >> roll;

    int linear = linearSearch(roll, rollNos, size);
    cout << "Linear search result: " << linear << endl;

    int binary = binarySearch(roll, rollNos, size);
    cout << "Binary search result: " << binary << endl;

    int jump = jumpSearch(roll, rollNos, size);
    cout << "Jump search result: " << jump << endl;
}
