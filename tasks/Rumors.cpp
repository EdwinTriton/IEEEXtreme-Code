#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

std::map<std::string, std::vector<std::string>> susjedi;
std::map<std::string, bool> nisu_sigurno;

void prosiri(std::string osoba) {
    for(auto x : susjedi[osoba]) {
        if(nisu_sigurno[x] == false) {
            nisu_sigurno[x] = true;
            prosiri(x);
        }
    }
}

int main() {

    int n;
    std::cin >> n;
    std::cin.ignore(100, '\n');

    std::vector<std::string> owo(n);

    for(int i = 0; i < n; i++) {
        std::string s;
        std::getline(std::cin, s, '\n');
        owo.at(i) = s + "\n";
    }

    std::vector<std::string> imena_lijevo, imena_desno, znak;
    std::set<std::string> sus2;

    for(int i = 0; i < n; i++) {
        std::stringstream ss(owo.at(i));
        std::string ime;
        std::vector<std::string> pomi;
        while(ss >> ime)
            pomi.push_back(ime);
        imena_lijevo.push_back(pomi.at(0));
        imena_desno.push_back(pomi.at(2));
        znak.push_back(pomi.at(1));
        sus2.insert(pomi.at(0));
        sus2.insert(pomi.at(2));
    }

    for(auto x : imena_desno) sus2.erase(x);
    int j = 0;
    for(auto x : imena_lijevo) {
        if(znak.at(j) == "??") {
            sus2.erase(x);
        }
        j++;
    }

    if(sus2.size() == 1)
        std::cout << *sus2.begin() << std::endl;
    else {

        for(int i = 0; i < n; i++) {
            if(znak.at(i) == "->")
                nisu_sigurno[imena_desno.at(i)] = true;
            else {
                if(nisu_sigurno.count(imena_desno.at(i))==0)  nisu_sigurno[imena_desno.at(i)] = false;
                if(nisu_sigurno.count(imena_lijevo.at(i))==0) nisu_sigurno[imena_lijevo.at(i)] = false;
            }
            if(znak.at(i) == "??") {
                susjedi[imena_lijevo.at(i)].push_back(imena_desno.at(i));
                susjedi[imena_desno.at(i)].push_back(imena_lijevo.at(i));
            }
        }

        for(auto [osoba, non_sussiness] : nisu_sigurno) {
            if(non_sussiness == true) prosiri(osoba);
        }


        for(auto [osoba, non_sussiness] : nisu_sigurno) {
            // cout << "Osoba i ns: " << osoba << ' ' << non_sussiness << '\n';
            if(non_sussiness == false)
                std::cout << osoba << std::endl;
        }
    }

    return 0;
}
