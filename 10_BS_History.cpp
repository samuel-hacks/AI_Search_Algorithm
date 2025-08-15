#include <bits/stdc++.h>
using namespace std;

bool beamSearchWithHistory(
    map<char, vector<pair<char, int>>>& graph,
    map<char, int>& heuristic,
    char start, char goal, int beamWidth,
    vector<char>& path
) {
    set<char> visited;
    vector<vector<char>> beams = {{start}};
    visited.insert(start);

    while (!beams.empty()) {
        vector<vector<char>> newBeams;

        for (auto& seq : beams) {
            char current = seq.back();

            if (current == goal) {
                path = seq;
                return true;
            }

            vector<pair<char, int>> neighbors;
            for (auto& nb : graph[current]) {
                if (!visited.count(nb.first)) {
                    neighbors.push_back({nb.first, heuristic[nb.first]});
                }
            }

            sort(neighbors.begin(), neighbors.end(),
                 [](auto& a, auto& b) { return a.second < b.second; });

            for (auto& nb : neighbors) {
                auto newSeq = seq;
                newSeq.push_back(nb.first);
                newBeams.push_back(newSeq);
                visited.insert(nb.first);
            }
        }

        sort(newBeams.begin(), newBeams.end(), [&](auto& a, auto& b) {
            return heuristic[a.back()] < heuristic[b.back()];
        });

        if ((int)newBeams.size() > beamWidth)
            newBeams.resize(beamWidth);

        beams = newBeams;
    }

    return false;
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
    int beamWidth = 2; 

    if (beamSearchWithHistory(graphMap, heuristic, 'P', 'X', beamWidth, path)) {
        cout << "Path found: ";
        for (char node : path) cout << node << " ";
        cout << endl;
    } else {
        cout << "Goal not reachable.\n";
    }

    return 0;
}
