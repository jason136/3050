#pragma once

#ifndef FILE_H_
#define FILE_H_

#include <iostream>
#include <vector>
#include <fstream>

void clearVectors();

void recordInput(double instJoysticks[4], int instButtons[3]);

void writeToFile(const char* filename);

void readFromFile();

#endif