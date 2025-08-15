#include <bits/stdc++.h>
using namespace std;

bool hillClimbingWithHistory(
    map<char, vector<pair<char, int>>>& graph,
    map<char, int>& heuristic,
    char start, char goal,
    vector<char>& path
) {
    set<char> visited;
    char current = start;
    path.push_back(current);
    visited.insert(current);

    while (true) {
        if (current == goal) return true;

        vector<pair<char, int>> neighbors;
        for (auto& nb : graph[current]) {
            if (!visited.count(nb.first)) {
                neighbors.push_back({nb.first, heuristic[nb.first]});
            }
        }

        if (neighbors.empty()) return false; 

        sort(neighbors.begin(), neighbors.end(),
             [](auto& a, auto& b) { return a.second < b.second; });

        
        current = neighbors.front().first;
        path.push_back(current);
        visited.insert(current);
    }
}

int main() {
    
    map<char, vector<pair<char, int>>> graphMap = {
        {'P', {{'Q', 2}, {'R', 4}}},
        {'Q', {{'T', 3}, {'U', 5}}},
        {'R', {{'S', 2}}},
        {'S', {{'V', 3}}},
        {'T', {{'V', 2}}},
        {'U', {{'W', 4}}},
        {'V', {{'X', 1}}},
        {'W', {}},
        {'X', {}}
    };

    map<char, int> heuristic = {
        {'P', 10}, {'Q', 8}, {'R', 7}, {'S', 6},
        {'T', 5},  {'U', 4}, {'V', 3}, {'W', 2},
        {'X', 0} 
    };

    vector<char> path;

    if (hillClimbingWithHistory(graphMap, heuristic, 'P', 'X', path)) {
        cout << "Path found: ";
        for (char node : path) cout << node << " ";
        cout << endl;
    } else {
        cout << "Goal not reachable.\n";
    }

    return 0;
}
