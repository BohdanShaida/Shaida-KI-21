#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "profile.h"
using namespace std;

int main() {
    {
        LOG_DURATION("Total runtime");

        ifstream input("input.txt");
        int n;
        input >> n;

        vector<int> sportsmen(n);
        unordered_map<int, int> lineup;

        for (int i = 0; i < n; ++i) {
            int current, before;
            input >> current >> before;
            sportsmen[i] = current;
            lineup[current] = before;
        }

        vector<int> result;
        result.reserve(n); // Попереднє резервування пам'яті

        for (int i = 0; i < n; ++i) {
            if (lineup.count(sportsmen[i]) && lineup[sportsmen[i]] >= 0 && lineup[sportsmen[i]] < result.size()) {
                result.insert(result.begin() + lineup[sportsmen[i]] + 1, sportsmen[i]);
            }
            else {
                result.push_back(sportsmen[i]);
            }
        }

        for (int num : result) {
            cout << num << '\n';
        }
    }
    return 0;
}
