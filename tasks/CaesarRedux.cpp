#include <iostream>
#include <string>
#include <regex>

using namespace std;

bool containsWord(const std::string& sentence, const std::string& word) {
    // Construct a regex pattern to match the word as a whole word
    std::string pattern = "\\b" + word + "\\b";
    std::regex r(pattern, std::regex_constants::icase);  // icase makes the search case-insensitive
    return std::regex_search(sentence, r);
}

string dodaj(string s, int n) {
    for(int i=0;i<s.size();i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 26;
            s[i] += n;
            if(s[i] < 'a') s[i] += 26;
        }
    }
    return s;
}

int main() {
    int N;
    cin >> N;

    string s, sc, ans;
    int n;

    while(N--) {
        getline(cin >> ws, s);
        n = stoi(s);
        getline(cin >> ws, s);

        if(containsWord(s, "the")) {
            ans = dodaj(s, 26-n);
        }
        else {
            ans = dodaj(s, n);
        }
        
        cout << ans << '\n';
        // cout << int(ans[0]) << '\n';;
    }

    return 0;
}
