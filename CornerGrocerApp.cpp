#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <cctype>
#include <algorithm>

using namespace std;

// Converts a string to lowercase
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class GroceryFrequency {
public:
    // Reads input file and populates frequency data
    void processInputFile(const string& filename) {
        ifstream input(filename);
        if (!input) {
            cout << "Failed to open " << filename << "." << endl;
            return;
        }
        string item;
        while (getline(input, item)) {
            // Converts and stores each item in lowercase
            freqData[toLowerCase(item)]++;
        }
        input.close();
    }

    // Returns the frequency of a specific item, handling different cases
    int getItemFrequency(const string& item) const {
        auto it = freqData.find(toLowerCase(item));
        if (it != freqData.end()) {
            return it->second;
        }
        else {
            return 0;
        }
    }

    // Prints all items and their frequencies
    void printFrequencyList() const {
        cout << "\nItem Frequencies:\n";
        for (const auto& pair : freqData) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

    // Prints a histogram of item frequencies
    void printFrequencyHistogram() const {
        cout << "\nFrequency Histogram:\n";
        for (const auto& pair : freqData) {
            cout << pair.first << " ";
            cout << string(pair.second, '*') << endl;
        }
    }

    // Backs up frequency data to a specified file
    void backupFrequencyData(const string& filename = "frequency.dat") const {
        ofstream output(filename);
        if (!output) {
            cout << "Failed to create " << filename << "." << endl;
            return;
        }
        for (const auto& pair : freqData) {
            output << pair.first << " - " << pair.second << " times\n";
        }
        output.close();
    }

private:
    map<string, int> freqData; // Stores item names and their frequency counts
};

// Validates user's menu choice
int getValidatedChoice() {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << "Invalid choice. Enter a number between 1 and 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

// Checks if a given item name is valid (only letters and spaces)
bool isValidItemName(const string& itemName) {
    for (char ch : itemName) {
        if (!isalpha(ch) && ch != ' ') {
            return false;
        }
    }
    return true;
}

int main() {
    GroceryFrequency grocery;
    // Process input file for frequency data
    grocery.processInputFile("CS210_Project_Three_Input_File.txt");

    bool running = true;
    while (running) {
        cout << "\nMenu Options:\n"
            << "1. Look up item frequency\n"
            << "2. Print all items and frequencies\n"
            << "3. Print frequency histogram\n"
            << "4. Exit program\n"
            << "Enter your choice: ";

        int choice = getValidatedChoice();

        switch (choice) {
        case 1: {
            cout << "Enter item name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string item;
            getline(cin, item);
            if (!isValidItemName(item)) {
                cout << "Invalid item name." << endl;
                break;
            }
            cout << item << " frequency: " << grocery.getItemFrequency(item) << endl;
            break;
        }
        case 2:
            grocery.printFrequencyList();
            break;
        case 3:
            grocery.printFrequencyHistogram();
            break;
        case 4:
            grocery.backupFrequencyData();
            running = false;
            break;
        }
    }

    return 0;
}