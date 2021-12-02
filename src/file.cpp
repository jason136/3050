#include "main.h"
#include "file.hpp"

std::vector<std::vector<int8_t>> vectors;

std::vector<int8_t> listAnalog1RightX;
std::vector<int8_t> listAnalog1RightY;
std::vector<int8_t> listAnalog1LeftX;
std::vector<int8_t> listAnalog1LeftY;

std::vector<int8_t> listDigital1R;
std::vector<int8_t> listDigital1L;
std::vector<int8_t> listDigital1UpDown;
std::vector<int8_t> listDigital1LeftRight;
std::vector<int8_t> listDigital1XB;
std::vector<int8_t> listDigital1YA;

std::vector<int8_t> listAnalog2RightX;
std::vector<int8_t> listAnalog2RightY;
std::vector<int8_t> listAnalog2LeftX;
std::vector<int8_t> listAnalog2LeftY;

std::vector<int8_t> listDigital2R;
std::vector<int8_t> listDigital2L;
std::vector<int8_t> listDigital2UpDown;
std::vector<int8_t> listDigital2LeftRight;
std::vector<int8_t> listDigital2XB;
std::vector<int8_t> listDigital2YA;

void clearVectors() {
    
    for (std::vector<int8_t> vector : vectors) {
        vector.clear(); 
    }

    std::cout << "vectors cleared" << std::endl;
}

void recordInput(int8_t * instInputs) {

    for (int x = 0; x < 28; x++) {
        vectors[x].push_back(instInputs[x]);
    }

    std::cout << "inputs recorded" << std::endl;
}

void updateIndex(int8_t * recInputs, int8_t index) {
    
    for (int x = 0; x < 28; x++) {
        recInputs[x] = vectors[x].at(index); 
    }

    //std::cout << "vectors returned" << std::endl;
}

int getVectorSize() {
    std::cout << "vector size returned" << std::endl;
    return vectors[0].size();
}

void printVectors() {
    int interations = getVectorSize();
    std::cout << "begin vector output with size : " << interations << std::endl;
    int8_t recOutputs[28];
    for (int x = 0; x < interations; x++) {
        updateIndex(&recOutputs[0], x);
        for (int y = 0; y < 7; y++) {
            std::cout << " " << recOutputs[1] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "end vector output with size : " << interations << std::endl;
}

void writeToFile(const char * filename) {
    std::ofstream outfile(filename);
    outfile << "data\n";
    char filebuffer[1000] = "";
    for (int x = 0; x < getVectorSize(); x++) {
        sprintf(filebuffer, "%hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx %hhx\n",
                vectors[0].at(x),
                vectors[1].at(x),
                vectors[2].at(x),
                vectors[3].at(x),
                vectors[4].at(x),
                vectors[5].at(x),
                vectors[6].at(x),
                vectors[7].at(x),
                vectors[8].at(x),
                vectors[9].at(x),
                vectors[10].at(x),
                vectors[11].at(x),
                vectors[12].at(x),
                vectors[13].at(x),
                vectors[14].at(x),
                vectors[15].at(x),
                vectors[16].at(x),
                vectors[17].at(x),
                vectors[18].at(x),
                vectors[19].at(x),
                vectors[20].at(x),
                vectors[21].at(x),
                vectors[22].at(x),
                vectors[23].at(x),
                vectors[24].at(x),
                vectors[25].at(x),
                vectors[26].at(x),
                vectors[27].at(x));
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
    int8_t a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, aa, ab;
    while (infile >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> q >> r >> s >> t >> u >> v >> w >> x >> y >> z >> aa >> ab) {
        vectors[0].push_back(a);
        vectors[1].push_back(b);
        vectors[2].push_back(c);
        vectors[3].push_back(d);
        vectors[4].push_back(e);
        vectors[5].push_back(f);
        vectors[6].push_back(g);
        vectors[7].push_back(h);
        vectors[8].push_back(i);
        vectors[9].push_back(j);
        vectors[10].push_back(k);
        vectors[11].push_back(l);
        vectors[12].push_back(m);
        vectors[13].push_back(n);
        vectors[14].push_back(o);
        vectors[15].push_back(p);
        vectors[16].push_back(q);
        vectors[17].push_back(r);
        vectors[18].push_back(s);
        vectors[19].push_back(t);
        vectors[20].push_back(u);
        vectors[21].push_back(v);
        vectors[22].push_back(w);
        vectors[23].push_back(x);
        vectors[24].push_back(y);
        vectors[25].push_back(z);
        vectors[26].push_back(aa);
        vectors[27].push_back(ab);
    }
    infile.close();

    std::cout << "file read: " << filename << getVectorSize() << std::endl;
    return true;
}

bool exists(const char * name) {
    std::ifstream f(name);
    return f.good();
}

void generateDatastructures() {

    for (int x = 0; x < 28; x++) {
        std::vector<int8_t> vector;
        vectors.push_back(vector); 
    }

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