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

map<char, int> heuristic = {
    {'P', 6}, {'Q', 4}, {'R', 5},
    {'S', 3}, {'T', 2}, {'U', 4},
    {'V', 1}, {'W', 3}, {'X', 0}
};

bool hillClimb(char node, char goal, vector<char> &path, unordered_set<char> &visited) {
    visited.insert(node);
    path.push_back(node);

    if (node == goal)
        return true;

    vector<char> neighbors = graphMap[node];
    sort(neighbors.begin(), neighbors.end(),
         [](char a, char b) { return heuristic[a] < heuristic[b]; });

    for (char neighbor : neighbors) {
        if (!visited.count(neighbor)) {
            if (hillClimb(neighbor, goal, path, visited))
                return true;
        }
    }

    path.pop_back();
    return false;
}

int main() {
    char start = 'P';
    char goal = 'X';

    vector<char> path;
    unordered_set<char> visited;

    bool found = hillClimb(start, goal, path, visited);

    cout << "Path from " << start << " to " << goal << ": ";
    if (found) {
        for (char node : path)
            cout << node << " ";
    } else {
        cout << "No path found.";
    }
    cout << endl;

    return 0;
}
