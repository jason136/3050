#include "main.h"
#include "file.hpp"

std::vector<std::vector<int>> vectors;

void clearVectors() {
    
    for (std::vector<int> vector : vectors) {
        vector.clear(); 
    }

    std::cout << "vectors cleared" << std::endl;
}

void recordInput(int * instInputs) {

    for (int x = 0; x < 28; x++) {
        vectors[x].push_back(instInputs[x]);
    }

    std::cout << "inputs recorded" << std::endl;
}

void updateIndex(int * recValues, int index) {
    
    for (int x = 0; x < 28; x++) {
        recValues[x] = vectors[x].at(index); 
    }
}

int getVectorSize() {
    std::cout << "vector size returned" << vectors[0].size() << std::endl;
    return vectors[0].size();
}

void printVectors() {
    int interations = getVectorSize();
    std::cout << "begin vector output with size : " << interations << std::endl;
    int recOutputs[28];
    for (int x = 0; x < interations; x++) {
        updateIndex(&recOutputs[0], x);
        for (int y = 0; y < 28; y++) {
            std::cout << " " << recOutputs[y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "end vector output with size : " << interations << std::endl;
}

void writeToFile(const char * filename) {
    std::ofstream outfile(filename);
    outfile << "data\n";
    char filebuffer[1000] = "";
    int interations = getVectorSize();
    for (int x = 0; x < interations; x++) {
        sprintf(filebuffer, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",
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
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, aa, ab;
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
        std::vector<int> vector;
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