#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>

void clearVectors();

void recordInput(double instJoysticks[4], int instButtons[3]);

void updateIndex(double recJoysticks[4], int recButtons[3], int index);

int getVectorSize();

void writeToFile(const char* filename);

void readFromFile();

#endif