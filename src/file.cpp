#include "main.h"
#include "file.hpp"

using namespace std;

std::vector<double> listAnalogRightX;
std::vector<double> listAnalogRightY;
std::vector<double> listAnalogLeftX;
std::vector<double> listAnalogLeftY;

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

void recordInput(double instJoysticks[], int instButtons[]) {
    listAnalogRightX.push_back(instJoysticks[0]);
    listAnalogRightY.push_back(instJoysticks[1]);
    listAnalogLeftX.push_back(instJoysticks[2]);
    listAnalogLeftY.push_back(instJoysticks[3]);

    listDigitalR.push_back(instButtons[0]);
    listDigitalL.push_back(instButtons[1]);
    listDigitalUpDown.push_back(instButtons[2]);

    std::cout << "inputs recorded" << std::endl;
}

void updateIndex(double recJoysticks[], int recButtons[], int index) {
    recJoysticks[0] = listAnalogRightX.at(index);
    recJoysticks[1] = listAnalogRightY.at(index);
    recJoysticks[2] = listAnalogLeftX.at(index);
    recJoysticks[3] = listAnalogLeftY.at(index);
    recButtons[0] = listDigitalR.at(index);
    recButtons[1] = listDigitalL.at(index);
    recButtons[2] = listDigitalUpDown.at(index);

    std::cout << "vectors returned" << std::endl;
}

int getVectorSize() {
    return listAnalogRightX.size();

    std::cout << "vector size returned" << std::endl;
}

void writeToFile(const char * filename) {
    ofstream outfile(filename);
    outfile << "data\n";
    char filebuffer[500] = "";
    for (int x = 0; x < listAnalogRightX.size(); x++) {
        sprintf(filebuffer, "%F %F %F %F %i %i %i\n",
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
    ifstream infile(filename);
    char buffer[5];
    infile >> buffer;
    std::cout << buffer << std::endl;
    if (buffer == "none") return false;
    double a, b, c, d;
    int e, f, g;
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
    ifstream f(name);
    return f.good();
}

void generateFiles() {
    char filename[20];
    for (int x = 0; x < 7; x++) {
        sprintf(filename, "/usd/RecAuton%i.txt", x);
        if (!exists(filename)) {
            ofstream file(filename);
            file << "none";
            file.close();
            std::cout << "file created: " << std::endl;
        }
    }
}