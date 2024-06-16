#include <iostream>
#include <vector>
#include <algorithm>

std::vector<char> poredak = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore(100, '\n');
    std::vector<char> player1, player2;
    char a;

    for(int i = 0; i < n; i++) {
        while(std::cin.peek() != '\n') {
            std::cin >> a;
            player1.push_back(a);
        }
        std::cin.ignore(100, '\n');
        while(std::cin.peek() != '\n') {
            std::cin >> a;
            player2.push_back(a);
        }
        std::cin.ignore(100, '\n');

        int uslov = 0;
        while(player1.size() > 0 && player2.size() > 0) {
            auto it1 = std::find(poredak.begin(), poredak.end(), player1.at(0));
            auto it2 = std::find(poredak.begin(), poredak.end(), player2.at(0));
            if(it1 > it2) {
                player1.push_back(player2.at(0));
                player1.erase(player1.begin());
                player2.erase(player2.begin());
            }
            else if(it1 < it2) {
                player2.push_back(player1.at(0));
                player1.erase(player1.begin());
                player2.erase(player2.begin());
            }
            else {
                player1.push_back(player1.at(0));
                player2.push_back(player2.at(0));
                player1.erase(player1.begin());
                player2.erase(player2.begin());
            }

            uslov++;
            if(uslov == 1000) break;

        }

        if(player1.size() == 0) std::cout << "player 2" << std::endl;
        else if(player2.size() == 0) std::cout << "player 1" << std::endl;
        else std::cout << "draw" << std::endl;

        player1.resize(0);
        player2.resize(0);

    }




    return 0;
}
