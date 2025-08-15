#include <bits/stdc++.h>
using namespace std;

void bfsLevelGlobalVisitedAllPaths(map<char, vector<char>> &graph, char start, char goal) {
    queue<vector<char>> q;
    set<char> visited;
    vector<vector<char>> results;
    bool found = false;

    q.push({start});
    visited.insert(start);

    while (!q.empty() && !found) {
        int levelSize = q.size();
        set<char> levelVisited; // track nodes visited *this* level

        for (int i = 0; i < levelSize; i++) {
            auto path = q.front();
            q.pop();

            char node = path.back();

            if (node == goal) {
                results.push_back(path);
                found = true;
                continue; // still check other paths at same level
            }

            for (char neigh : graph[node]) {
                if (!visited.count(neigh)) {
                    levelVisited.insert(neigh);
                    auto newPath = path;
                    newPath.push_back(neigh);
                    q.push(newPath);
                }
            }
        }

        // Add all nodes visited this level to global visited
        for (char v : levelVisited) visited.insert(v);
    }

    cout << "Paths from " << start << " to " << goal << endl;
    if (!results.empty()) {
        for (auto &path : results) {
            cout << "Path found: ";
            for (char c : path) cout << c;
            cout << endl;
        }
    } else {
        cout << "No path found." << endl;
    }
}

int main() {
    map<char, vector<char>> graphMap = {
        {'P', {'Q', 'R'}},
        {'Q', {'T', 'U'}},
        {'R', {'S'}},
        {'S', {'V'}},
        {'T', {'V'}},
        {'U', {'W'}},
        {'V', {'X'}},
        {'W', {}},
        {'X', {}}
    };

    bfsLevelGlobalVisitedAllPaths(graphMap, 'P', 'X');
}
