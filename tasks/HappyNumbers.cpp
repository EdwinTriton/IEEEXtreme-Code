#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

long long happyUpTo(long long x);
int kvadrat[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
vector< vector<long long>> mat1(17, vector<long long> (1300, 0));

std::unordered_set<long long> happy, unhappy;
vector<bool> ih;

long long sumOfSquares(long long num) {
    long long sum = 0;
    while (num > 0) {
        long long digit = num % 10;
        sum += digit * digit;
        num /= 10;
    }
    return sum;
}

bool isHappy(long long n) {
    unordered_set<long long> seen;
    bool ok = 0;


    while (1) {
        if(happy.count(n)) {
            ok = 1;
            break;
        }

        if(unhappy.count(n)) {
            ok = 0;
            break;
        }

        seen.insert(n);
        n = sumOfSquares(n);
    }


    if(ok) {
        happy.insert(seen.begin(), seen.end());
    }
    else {
        unhappy.insert(seen.begin(), seen.end());
    }
    return ok;
}

bool isHappyFast(long long x) {
    return ih[sumOfSquares(x)];
}

long long countHappyNumbers(long long start, long long end) {
    long long count = 0;
    for(int i=start;i<=end;i++) {
        count += ih[sumOfSquares(i)];
    }
    return count;
    // return happyUpTo(end) - happyUpTo(start);
}

int prvaCifra(long long x) {
    int c = x;
    while(x) {
        c = x;
        x /= 10;
    }
    return c;
}

long long bezPrveCifre(long long x) {
    long long p = 1;
    while(p<=x) p*=10;
    p/=10;
    return x%p;
}

long long happyUpTo(long long x) {
    if(x==0) return 0;
    long long sum = 0;
    long long xc = x, xcc;
    int brcif = 0;
    while(xc) {
        xc/=10;
        brcif++;
    }

    xc = x;

    int odranije = 0;

    while(xc) {
        // cout << xc << ' ' << sum << '\n';
        xcc = xc;
        brcif = 0;
        while(xcc) {
            xcc/=10;
            brcif++;
        }

        if(brcif == 1) {
//            cout << xc << ' ' << odranije << ' ' << sum << ' ' << isHappyFast(16) << endl;
            for(int i=0;i<=xc;i++) {
                if(isHappyFast(odranije+i*i)) sum++;
            }
            break;
        }

        int pc = prvaCifra(xc);

        for(int i=0;i<1300;i++) {
            for(int j=0;j<pc;j++) {
                // if(i+j*j+odranije >= 1300) continue;
                if(brcif<=0) continue;
                sum += ih[i+j*j+odranije]*mat1[brcif-1][i];
                // cout << i << ' ' << j << ' ' << sum << '\n';
            }
        }

        odranije += pc*pc;
        xc = bezPrveCifre(xc);
        brcif--;

        if(xc == 0 && brcif != 0) {
            sum += ih[odranije];
        }
    }

    return sum;
}

int main() {
    // mat1[i][j] kaze koliko brojeva sa i cifara (moze poceti sa 0) ciji je sumofsquares jednak j
    for(int i=0;i<=9;i++) {
        mat1[1][i*i] = 1;
    }
    for(int i=1;i<16;i++) {
        for(int j=0;j<1300;j++) {
            if(mat1[i][j] != 0) {
                for(int x=0;x<=9;x++) {
                    mat1[i+1][j+x*x] += mat1[i][j];
                }
            }
        }
    }


    happy.insert(1);
    unhappy.insert(4);

    long long start = 1, end = 10;

    cin >> start >> end;

    ih.resize(1300, 0);
    for(int i=1;i<1300;i++) {
        ih[i] = isHappy(i);
    }

//    long long sum = 0;
//    for(int i=0;i<1300;i++) {
//        sum += ih[i]*mat1[6][i];
//        sum += ih[i+1]*mat1[6][i];
//        sum += ih[i+4]*mat1[6][i];
//        sum += ih[i+9]*mat1[6][i];
//        sum += ih[i+16]*mat1[6][i];
//    }
//    cout << sum << endl;

    cout << happyUpTo(end)-happyUpTo(start-1) << endl;

//      long long happyCount = countHappyNumbers(start, end);
//      std::cout << happyCount;

//    cout << '\n';
//    cout << mat1[1][0] << ' ';
//    cout << mat1[1][1] << ' ';
//    cout << mat1[1][2] << ' ';
//    cout << mat1[1][3] << ' ';
//    cout << mat1[1][4] << ' ';
//    cout << mat1[1][5] << ' ';
//    cout << mat1[1][6] << ' ';
//    cout << mat1[1][7] << ' ';
//    cout << mat1[1][8] << ' ';
//    cout << mat1[1][9] << ' ';
    return 0;
}
