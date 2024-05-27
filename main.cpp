#include <iostream>
#include <random>
#include <iostream>
#include <algorithm>

#define capacity 10
#define elements 6

using std::max;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::swap;
using std::vector;

void findAns(int (&a)[elements+1][capacity+1],int (&eSize)[elements],int k, int s, vector<int>& ans) {
    if (a[k][s] == 0) return;
    if (a[k - 1][s] == a[k][s]) findAns(a, eSize, k - 1, s, ans);
    else {
        findAns(a, eSize, k - 1, s - eSize[k-1], ans);
        ans.push_back(k);
    }
}

int main() {
    int eSize[elements];
    int eCost[elements];
    int a[elements+1][capacity+1] {};
    vector<int> answer;
    
    std::random_device r;
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution<int> sizeDist(2, int(capacity/2));
    std::uniform_int_distribution<int> costDist(1, 100);
    
    for (int i = 0; elements > i; i++) {
        eSize[i] = sizeDist(randomEngine);
        eCost[i] = costDist(randomEngine);
    }
    for (int step = elements - 1; 0 < step; step /= 1.3)
                for (int i = 0; elements > i + step; i++)
                    if (eSize[i] > eSize[i + step]){
                        swap(eSize[i], eSize[i + step]);
                        swap(eCost[i], eCost[i + step]);
                    } 

    for (int i = 0; elements > i; i++)
    cout << i + 1 << ") " << eSize[i] << " : " << eCost[i] << endl;
        
    for (int k = 1; elements >= k; k++){
        for (int s = 1; capacity >= s; s++){
            if (s >= eSize[k-1])
                a[k][s] = max(a[k - 1][s], (a[k - 1][s - eSize[k-1]] + eCost[k-1]));
            else a[k][s] = a[k - 1][s];
        }
    }
    cout << endl;
    for (int k = 0; elements >= k; k++){
        for (int s = 0; capacity >= s; s++)
            cout << a[k][s] << ',';
        cout << endl;
    }
    
    findAns(a, eSize, elements, capacity, answer);
    cout << endl;
    for(int i : answer){
        cout << i << " ";
    }
}
