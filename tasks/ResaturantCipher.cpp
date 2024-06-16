#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main() {

    int n;
    std::cin >> n;
    std::cin.ignore(100, '\n');
    std::vector<std::string> v(n);

    for(int i = 0; i < n; i++) {
        char a;
        while(std::cin.peek() != '\n') {
            std::cin >> a;
            v.at(i).push_back(a);
        }
        std::cin.ignore(100, '\n');
    }

    std::vector<std::string> rezultat;

    for(int i = 0; i < n; i++) {
        std::string pomi = v.at(i);
        std::map<char, int> ucestanost{{'a', 0}, {'b', 0}, {'c', 0}, {'d', 0}, {'e', 0}, {'f', 0},
                                        {'g', 0}, {'h', 0}, {'i', 0}, {'j', 0}, {'k', 0}, {'l', 0},
                                        {'m', 0}, {'n', 0}, {'o', 0}, {'p', 0}, {'q', 0}, {'r', 0},
                                        {'s', 0}, {'t', 0}, {'u', 0}, {'v', 0}, {'w', 0}, {'x', 0},
                                        {'y', 0}, {'z', 0}};
        for(int j = 0; j < pomi.length(); j++) {
            int val = ucestanost[pomi.at(j)];
            val++;
            ucestanost[pomi.at(j)] = val;
        }
        int maks = 0;
        char slovo = 'E';
        for(auto [key, value] : ucestanost) {
            if(value > maks) {
                maks = value;
                slovo = std::toupper(key);
            }
        }
        rezultat.push_back(std::string(1, slovo));

    }

    for(auto x : rezultat)
        std::cout << x << "\n";

    return 0;
}
