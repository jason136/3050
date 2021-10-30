#include "main.h"
#include "file.hpp"
//#include "opcontrol.hpp"

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
}

void recordInput(double instJoysticks[4], int instButtons[3]) {
	listAnalogRightX.push_back(instJoysticks[0]);
	listAnalogRightY.push_back(instJoysticks[1]);
	listAnalogLeftX.push_back(instJoysticks[2]);
	listAnalogLeftY.push_back(instJoysticks[3]);

	listDigitalR.push_back(instButtons[0]);
	listDigitalL.push_back(instButtons[1]);
	listDigitalUpDown.push_back(instButtons[2]);
}

void updateIndex(double recJoysticks[4], int recButtons[3], int index) {
    
}

void writeToFile(const char* filename) {
    ofstream outfile (filename);
    char filebuffer[500] = "";
    for (int x = 0; x < listAnalogRightX.size(); x ++) {
        sprintf(filebuffer, "%F %F %F % %i %i %i\n", 
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
}

void readFromFile(const char* filename) {
    clearVectors();
    ifstream infile (filename);
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
}