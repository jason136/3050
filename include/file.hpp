#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void clearVectors();

void recordInput(int * instInputs);

void updateIndex(int * recInputs, int index);

int getVectorSize();

void writeToFile(const char * filename);

bool readFromFile(const char * filename);

bool exists(const char * name);

void generateFiles();

#endif