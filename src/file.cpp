#include "main.h"
#include "file.hpp"

using namespace std;

vector<vector<int>> vectors;
vector<vector<double>> cordVectors;

void clearVectors() {
    for (int x = 0; x < 29; x++) {
        vectors[x].clear(); 
    }
    for (int y = 0; y < 3; y++) {
        cordVectors[y].clear(); 
    }
    cout << "vectors cleared" << endl;
}

void recordInput(int index, int * instInputs, double * cords) {
    vectors[0].push_back(index);
    for (int x = 0; x < 28; x++) {
        vectors[x + 1].push_back(instInputs[x]);
    }
    cordVectors[0].push_back(cords[0]);
    cordVectors[1].push_back(cords[1]);
    cordVectors[2].push_back(cords[2]);
    cout << "inputs recorded" << endl;
}

void updateVecs(int index, int * recValues) {
    for (int x = 0; x < 28; x++) {
        recValues[x] = vectors[x + 1].at(index); 
    }
}

void updateLocation(int index, double * cords) {
    cords[0] = cordVectors[0].at(index);
    cords[1] = cordVectors[1].at(index);
    cords[2] = cordVectors[2].at(index);
}

int getVectorSize() {
    cout << "vector size returned" << vectors[0].size() << endl;
    return vectors[0].size();
}

void printVectors() {
    int recOutputs[28];
    double cords[3];
    int interations = getVectorSize();
    cout << "begin vector output with size : " << interations << endl;
    for (int x = 0; x < interations; x++) {
        updateVecs(x, &recOutputs[0]);
        updateLocation(x, &cords[0]);
        cout << x + 1;
        for (int y = 0; y < 28; y++) {
            cout << " " << recOutputs[y];
        }
        for (int z = 0; z < 3; z++) {
            cout << " " << cords[z];
        }
        cout << endl;
    }
    cout << "end vector output with size : " << interations << endl;
}

void writeToFile(const char * filename) {
    ofstream outfile(filename);
    outfile << "data\n";
    string filebuffer = "";
    int interations = getVectorSize();
    for (int x = 0; x < interations; x++) {
        filebuffer = "";
        for (int y = 0; y < size(vectors); y++) {
            filebuffer.append(to_string(vectors[y].at(x)));
            filebuffer.append(" ");
        }
        for (int y = 0; y < size(cordVectors); y++) {
            filebuffer.append(to_string(cordVectors[y].at(x)));
            filebuffer.append(" ");
        }
        filebuffer.pop_back();
        filebuffer.append("\n");
        outfile << filebuffer;
    }
    outfile.close();

    cout << "file written" << endl;
}

bool readFromFile(const char * filename) {
    clearVectors();
    ifstream infile(filename);
    string buffer;
    getline(infile, buffer);
    cout << buffer << endl;
    if (buffer == "none") {
        return false;
    }
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        for (int x = 0; x < 29; x++) {
            int temp;
            ss >> temp;
            vectors[x].push_back(temp);
        }
        for (int y = 0; y < 3; y++) {
            double temp;
            ss >> temp;
            cordVectors[y].push_back(temp);
        }
    }
    infile.close();

    cout << "file read: " << filename << getVectorSize() << endl;
    return true;
}

bool exists(const char * name) {
    ifstream f(name);
    return f.good();
}

void generateDatastructures() {
    for (int x = 0; x < 29; x++) {
        vector<int> vector;
        vectors.push_back(vector); 
    }
    for (int x = 0; x < 3; x++) {
        vector<double> cordVector;
        cordVectors.push_back(cordVector); 
    }

    char filename[20];
    for (int x = 0; x < 7; x++) {
        sprintf(filename, "/usd/RecAuton%i.txt", x);
        if (!exists(filename)) {
            ofstream file(filename);
            file << "none";
            file.close();
            cout << "file created: " << endl;
        }
    }
}