#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>

void clearVectors();

void recordInput(double * instJoysticks, int * instButtons);

void updateIndex(double * recJoysticks, int * recButtons, int index);

int getVectorSize();

void writeToFile(const char * filename);

void readFromFile(const char * filename);

bool exists(const char * name);

void generateFiles();

#endif