#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

int count(std::vector<int> &vektor, int k) {
    int counter = 0;
    for (int &i:vektor) {
        if (i == k) counter++;
    }
    return counter;
}

int main() {
    std::vector<std::set<std::string>> rime;
    int n = 0, m = 0;
    char k;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::set<std::string> rima;
        std::cin.get(k);
        while (std::cin.peek() != '\n') {
        std::string rijec;
        std::cin >> rijec;
        rima.insert(rijec);
        }
        rime.push_back(rima);
    }
    std::cin.get(k);
    std::vector<int> pasusi(m,-1);
    for (int i = 0; i < m; i++) {
        std::cin.get(k);
        std::string rijec;
        while (std::cin.peek() != EOF && std::cin.peek() != '\n') {
        std::cin >> rijec;
        }
        std::transform(rijec.begin(), rijec.end(), rijec.begin(), tolower);
        for (int j = 0; j<n; j++) {
            if (rime.at(j).find(rijec) != rime.at(j).end()) {
                pasusi.at(i) = j;
                break;
            }
        }
    }
    for (int i = 0; i<m; i++) {
        if (count(pasusi,pasusi.at(i)) == 1) pasusi.at(i) = -1;
    }
    std::vector<char> izlazi(1000,'X');
    int brojac = 0;
    for (int i = 0; i<m; i++) {
        if (pasusi.at(i) == -1) {
            std::cout << 'X';
            continue;
        }
        if (izlazi.at(pasusi.at(i)) == 'X') {
            izlazi.at(pasusi.at(i)) = 'A' + brojac++;
        }
        std::cout << izlazi.at(pasusi.at(i));
    }
    return 0;
}