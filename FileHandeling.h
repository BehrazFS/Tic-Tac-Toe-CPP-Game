#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <iostream>
#include <fstream>
#include "Colored.h"
using namespace std;

struct FileHandeling {
    Colored error_color = Colored(Foreground::RED, Background::BLACK, Attribute::BOLD);
    bool saveToFile(const string& filename, const string& data) {
        ofstream outFile(filename);
        if (!outFile) {
            error_color.print("Error opening file for writing: ", filename);
            return false;
        }
        outFile << data;
        outFile.close();
        return true;
    }

    bool readFromFile(const string& filename, string& data) {// data is output parameter
        ifstream inFile(filename);
        if (!inFile) {
            error_color.print("Error opening file for reading: ", filename);
            return false;
        }
        string line;
        data.clear();
        while (getline(inFile, line)) {
            data += line + '\n';
        }
        inFile.close();
        return true;
    }
};




#endif // FILE_HANDLING_H