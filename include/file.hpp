#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void clearVectors();

void recordInput(int8_t * instInputs);

void updateIndex(int8_t * recInputs, int8_t index);

int getVectorSize();

void printVectors();

void writeToFile(const char * filename);

bool readFromFile(const char * filename);

bool exists(const char * name);

void generateDatastructures();

#endif