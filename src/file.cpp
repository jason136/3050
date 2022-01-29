#include "main.h"
#include "file.hpp"

std::vector<std::vector<int>> vectors;
std::vector<std::vector<double>> cordVectors;

void clearVectors() {
    for (std::vector<int> vector : vectors) {
        vector.clear(); 
    }
    for (std::vector<double> vector : cordVectors) {
        vector.clear(); 
    }
    std::cout << "vectors cleared" << std::endl;
}

void recordInput(int index, int * instInputs, double * cords) {
    vectors[0].push_back(index);
    for (int x = 0; x < 28; x++) {
        vectors[x + 1].push_back(instInputs[x]);
    }
    cordVectors[0].push_back(cords[0]);
    cordVectors[1].push_back(cords[1]);
    cordVectors[2].push_back(cords[2]);
    std::cout << "inputs recorded" << std::endl;
}

void updateVecs(int index, int * recValues) {
    for (int x = 0; x < 28; x++) {
        recValues[x] = vectors[x + 1].at(index); 
    }
}

void updateLocation(int index, double * cords) {
    cords[0] = cordVectors[0].at(index);
    cords[1] = cordVectors[1].at(index);
    cords[2] = cordVectors[2].at(index);
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
        updateVecs(x, &recOutputs[0]);
        for (int y = 0; y < 29; y++) {
            std::cout << " " << recOutputs[y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "end vector output with size : " << interations << std::endl;
}

void writeToFile(const char * filename) {
    std::ofstream outfile(filename);
    outfile << "data\n";
    std::string filebuffer = "";
    int interations = getVectorSize();
    for (int x = 0; x < interations; x++) {
        filebuffer = "";
        for (int y = 0; y < std::size(vectors); y++) {
            filebuffer.append(std::to_string(vectors[y].at(x)));
            filebuffer.append(" ");
        }
        filebuffer.pop_back();
        // for (int y = 0; y < std::size(cordVectors); y++) {
        //     filebuffer.append(std::to_string(cordVectors[y].at(x)));
        //     filebuffer.append(" ");
        // }
        filebuffer.append("\n");
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
    std::cout << vectors.size() << std::endl;
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, aa, ab, ac;
    //double y1, y2, xx;
    while (infile >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> q >> r >> s >> t >> u >> v >> w >> x >> y >> z >> aa >> ab >> ac) {
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
        vectors[28].push_back(ac);
        
        // cordVectors[0].push_back(y1);
        // cordVectors[1].push_back(y2);
        // cordVectors[2].push_back(xx);
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
    for (int x = 0; x < 29; x++) {
        std::vector<int> vector;
        vectors.push_back(vector); 
    }
    for (int x = 0; x < 3; x++) {
        std::vector<double> cordVector;
        cordVectors.push_back(cordVector); 
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