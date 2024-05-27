#include <iostream>
#include <random>
#include <iostream>
#include <algorithm>

#define capacity 99
#define elements 10

using std::max;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::vector;

void findAns(int (&a)[elements][capacity],int (&eSize)[elements],int k, int s, vector<int>& ans) {
    if (a[k][s] == 0) return;
    if (a[k - 1][s] == a[k][s]) findAns(a, eSize, k - 1, s, ans);
    else {
        findAns(a, eSize,k - 1, s - eSize[k], ans);
        ans.push_back(k);
    }
}

int main() {
    int eSize[elements];
    int eCost[elements];

    int a[elements][capacity] {};
    std::random_device r;
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> sizeDist(1, int(capacity/2));
    std::uniform_int_distribution<int> costDist(1, 100);
    for (int i = 0; elements > i; i++) {
        eSize[i] = sizeDist(randomEngine);
        eCost[i] = costDist(randomEngine);
        cout << eSize[i] << " : " << eCost[i] << endl;
    }

    for (int k = 1; elements > k; k++){
        for (int s = 1; capacity > s; s++){
            if (s >= eCost[k])
                a[k][s] = max(a[k - 1][s], a[k - 1][s - eSize[k]] + eCost[k]);
            else a[k][s] = a[k - 1][s];
        }
    }
    vector<int> answer;
    findAns(a, eSize, elements - 1, capacity - 1, answer);
    for(int i : answer){
        cout << i << " ";
    }
    cout << endl;
}