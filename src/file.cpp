#include "main.h"
#include "file.hpp"

std::vector<int> listAnalogRightX;
std::vector<int> listAnalogRightY;
std::vector<int> listAnalogLeftX;
std::vector<int> listAnalogLeftY;

std::vector<int> listDigitalR;
std::vector<int> listDigitalL;
std::vector<int> listDigitalUpDown;

void clearVectors() {
    listAnalogRightX.clear();
    listAnalogRightY.clear();
    listAnalogLeftX.clear();
    listAnalogLeftY.clear();
    listDigitalR.clear();
    listDigitalL.clear();
    listDigitalUpDown.clear();

    std::cout << "vectors cleared" << std::endl;
}

void recordInput(int * instInputs) {
    listAnalogRightX.push_back(instInputs[0]);
    listAnalogRightY.push_back(instInputs[1]);
    listAnalogLeftX.push_back(instInputs[2]);
    listAnalogLeftY.push_back(instInputs[3]);

    listDigitalR.push_back(instInputs[4]);
    listDigitalL.push_back(instInputs[5]);
    listDigitalUpDown.push_back(instInputs[6]);

    std::cout << "inputs recorded" << std::endl;
}

void updateIndex(int * recInputs, int index) {
    recInputs[0] = listAnalogRightX.at(index);
    recInputs[1] = listAnalogRightY.at(index);
    recInputs[2] = listAnalogLeftX.at(index);
    recInputs[3] = listAnalogLeftY.at(index);
    recInputs[4] = listDigitalR.at(index);
    recInputs[5] = listDigitalL.at(index);
    recInputs[6] = listDigitalUpDown.at(index);

    //std::cout << "vectors returned" << std::endl;
}

int getVectorSize() {
    std::cout << "vector size returned" << std::endl;
    return listAnalogRightX.size();
}

void printVectors() {
    int interations = getVectorSize();
    std::cout << "begin vector output with size : " << interations << "\n" << std::endl;
    int recOutputs[7];
    for (int x = 0; x < interations; x++) {
        updateIndex(&recOutputs[0], x);
        for (int y = 0; y < 7; y++) {
            std::cout << " " << recOutputs[1] << " ";
        }
        std::cout << "\n" << std::endl;
    }
    std::cout << "end vector output with size : " << interations << "\n" << std::endl;
}

void writeToFile(const char * filename) {
    std::ofstream outfile(filename);
    outfile << "data\n";
    char filebuffer[500] = "";
    for (int x = 0; x < listAnalogRightX.size(); x++) {
        sprintf(filebuffer, "%i %i %i %i %i %i %i\n",
                listAnalogRightX.at(x),
                listAnalogRightY.at(x),
                listAnalogLeftX.at(x),
                listAnalogLeftY.at(x),
                listDigitalR.at(x),
                listDigitalL.at(x),
                listDigitalUpDown.at(x));
        outfile << filebuffer;
    }
    outfile.close();

    std::cout << "file written" << std::endl;
}

bool readFromFile(const char * filename) {
    clearVectors();
    std::ifstream infile(filename);
    char buffer[10];
    infile >> buffer;
    std::cout << buffer << std::endl;
    if (strcmp(buffer, "none") == 0) {
        return false;
    }
    int a, b, c, d, e, f, g;
    while (infile >> a >> b >> c >> d >> e >> f >> g) {
        listAnalogRightX.push_back(a);
        listAnalogRightY.push_back(b);
        listAnalogLeftX.push_back(c);
        listAnalogLeftY.push_back(d);

        listDigitalR.push_back(e);
        listDigitalL.push_back(f);
        listDigitalUpDown.push_back(g);
    }
    infile.close();

    std::cout << "file read: " << filename << getVectorSize() << std::endl;
    return true;
}

bool exists(const char * name) {
    std::ifstream f(name);
    return f.good();
}

void generateFiles() {
    char filename[20];
    for (int x = 0; x < 7; x++) {
        sprintf(filename, "/usd/RecAuton%i.txt", x);
        if (!exists(filename)) {
            std::ofstream file(filename);
            file << "none";
            file.close();
            std::cout << "file created: " << std::endl;
        }
    }
}