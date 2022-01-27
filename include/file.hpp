#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void clearVectors();

void recordInput(int index, int * instInputs, double * cords);

void updateIndex(int index, int * recValues);

int getVectorSize();

void printVectors();

void writeToFile(const char * filename);

bool readFromFile(const char * filename);

bool exists(const char * name);

void generateDatastructures();

#endif