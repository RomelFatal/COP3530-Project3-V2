#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

// This function removes the quotation from
// the csv file that contains the dataset
string removeQuotes(string& str) {
    string result;
    for (char ch : str) {
        if (ch != '"')
            result += ch;
    }
    return result;
}


/**
 * This function sort the data using the Merge Sort algorithm,
 * the algorithm is modeled after slides from class lectures
 * using the recursion method to sort all flight delays
 * extracted from the CSV file
 */
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}



/**
 * This function sort the data using the Quick Sort algorithm,
 * the algorithm is modeled after slides from class lectures
 * using the recursion method to sort all flight delays
 * extracted from the CSV file
 */

// Function to swap position of elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<int>& array, int low, int high) {
    // Select the pivot element
    int pivot = array[low];
    int up = low, down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (array[up] > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (array[down] < pivot)
                break;
            down--;
        }
        if (up < down)
            swap(&array[up], &array[down]);
    }
    swap(&array[low], &array[down]);
    return down;
}


void quickSort(vector<int>& array, int low, int high) {
    if (low < high)
    {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}


// Function to display the result of the sorted elements
void printVector(vector<int>& arr) {
    for (unsigned int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}



// This function reads the data from the csv file
vector<int> readCSV(string& filename, int targetColumnIndex) {
    vector<int> data;
    ifstream file(filename);
    string line;

    // Ensure the file opens correctly
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return data;
    }

    // Get all data from a specific column
    getline(file, line);

    while (getline(file, line)) {
        stringstream lineStream(line);
        string cell;
        int currentIndex = 0;

        while (getline(lineStream, cell, ',')) {
            if (currentIndex == targetColumnIndex) {
                string extractedData = removeQuotes(cell);
                data.push_back(std::stoi(extractedData));
                break;
            }
            currentIndex++;
        }
    }
    file.close();
    return data;
}


// Read data from CSV file
void writeCSV(string& filename, vector<int>& data) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto& in : data) {
            file << in << " ";
        }
        file.close();
    }
    else {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main() {
    string inputFile = "airlines.csv";
    string outputFile = "airlines_sorted.csv";
    int columnIndex = 7;

    vector<int> data = readCSV(inputFile, columnIndex);
    int dataSize = data.size() - 1;

    // Display flight delays using Merge Sort algorithm
    mergeSort(data, 0, dataSize);
    cout << "Statistics number of Delays by Carrier using Merge Sort algorithm:\n";
    printVector(data);
    cout << endl;

    // Display flight delays using Quick Sort algorithm
    cout << "Statistics number of Delays by Carrier using Quick Sort algorithm:\n";
    quickSort(data, 0, dataSize);
    printVector(data);


    // Extracted and sorted Data is formatted into a csv file
    writeCSV(outputFile, data);
    cout << "Data sorted and written to " << outputFile << endl;

    return 0;
}
