#include <iostream>
#include <vector>
#include <algorithm>

double odvod = -1;

struct cordinate {
    int x, y;
    cordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct maximum {
    int value = 0;
    std::vector<cordinate> cordinates;
    void add(cordinate a) {
        cordinates.push_back(a);
    }
    maximum(int valued) {value = valued;}
};

bool checkX(int x, std::vector<std::vector<int>> &matrica) {
    return x >= 0 && x<matrica.size();
}

bool checkY(int y, std::vector<std::vector<int>> &matrica) {
    return y >= 0 && matrica.size() && y<matrica.at(0).size();
}

void dodijeli(std::vector<std::vector<int>> &matrica, std::vector<std::vector<double>> &flow, const int &x, const int &y) {
    int podijela = 0;
    if (checkX(x+1, matrica) && matrica.at(x).at(y) > matrica.at(x+1).at(y)) podijela++;
    if (checkX(x-1, matrica) && matrica.at(x).at(y) > matrica.at(x-1).at(y)) podijela++;
    if (checkY(y+1, matrica) && matrica.at(x).at(y) > matrica.at(x).at(y+1)) podijela++;
    if (checkY(y-1, matrica) && matrica.at(x).at(y) > matrica.at(x).at(y-1)) podijela++;
    if (!podijela) {
        if (flow.at(x).at(y) > odvod) odvod = flow.at(x).at(y);
        return;
    }
    double tok = flow.at(x).at(y) / podijela;
    flow.at(x).at(y) = 0;
    if (checkX(x+1, matrica) && matrica.at(x).at(y) > matrica.at(x+1).at(y)) {
        flow.at(x+1).at(y) += tok;
        dodijeli(matrica, flow, x+1, y);
    }
    if (checkX(x-1, matrica) && matrica.at(x).at(y) > matrica.at(x-1).at(y)) {
        flow.at(x-1).at(y) += tok;
        dodijeli(matrica, flow, x-1, y);
    }
    if (checkY(y+1, matrica) && matrica.at(x).at(y) > matrica.at(x).at(y+1)) {
        flow.at(x).at(y+1) += tok;
        dodijeli(matrica, flow, x, y+1);
    }
    if (checkY(y-1, matrica) && matrica.at(x).at(y) > matrica.at(x).at(y-1)) {
        flow.at(x).at(y-1) += tok;
        dodijeli(matrica, flow, x, y-1);
    }
    if (flow.at(x).at(y) > odvod) odvod = flow.at(x).at(y); 
}


void locateLocals(std::vector<std::vector<int>> &matrica, maximum &locals) {
    for (int x = 0; x<matrica.size(); x++) {
        for (int y = 0; y<matrica.at(0).size(); y++) {
            if (checkX(x+1, matrica) && matrica.at(x).at(y) < matrica.at(x+1).at(y)) continue;
            if (checkX(x-1, matrica) && matrica.at(x).at(y) < matrica.at(x-1).at(y)) continue;
            if (checkY(y+1, matrica) && matrica.at(x).at(y) < matrica.at(x).at(y+1)) continue;
            if (checkY(y-1, matrica) && matrica.at(x).at(y) < matrica.at(x).at(y-1)) continue;
            locals.add({x,y});
        }
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;
    std::vector<std::vector<int>> matrica(a,(std::vector<int>(b)));
    std::vector<std::vector<double>> flow(a,(std::vector<double>(b,1)));
    maximum localMax(-1);
    for (int i = 0; i<a; i++) {
        for (int j = 0; j<b; j++) {
            std::cin >> matrica.at(i).at(j);
        }
    }
    locateLocals(matrica, localMax);
    for (cordinate& cordinate:localMax.cordinates) {
        dodijeli(matrica, flow, cordinate.x, cordinate.y);
    }
    std::cout << odvod;
    return 0;
}