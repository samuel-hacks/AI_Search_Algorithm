#include <bits/stdc++.h>
using namespace std;

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

bool dfsWithDeadEnds(char node, char goal, vector<char> &path, unordered_set<char> &visited, unordered_set<char> &deadEnd) {
    if (visited.count(node) || deadEnd.count(node))
        return false;

    visited.insert(node);
    path.push_back(node);

    if (node == goal) {
        return true; // Found the goal, stop here without popping
    }

    for (char neighbor : graphMap[node]) {
        if (!visited.count(neighbor)) {
            if (dfsWithDeadEnds(neighbor, goal, path, visited, deadEnd)) {
                return true; // If found, propagate success upwards without modifying path
            }
        }
    }

    // Mark as dead-end if not found
    deadEnd.insert(node);
    path.pop_back(); // Backtrack only if not found
    return false;
}

int main() {
    char start = 'P';
    char goal = 'X';

    vector<char> path;
    unordered_set<char> visited;
    unordered_set<char> deadEnd;

    bool found = dfsWithDeadEnds(start, goal, path, visited, deadEnd);

    cout << "Path from " << start << " to " << goal << ": ";
    if (found) {
        for (char node : path) cout << node << " ";
    } else {
        cout << "No path found.";
    }
    cout << endl;

    return 0;
}
