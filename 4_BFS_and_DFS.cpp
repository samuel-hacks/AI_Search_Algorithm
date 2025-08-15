#include <iostream>
#include <map>
#include <vector>
#include <set>
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

bool depthLimitedSearch(char current, char goal, int limit, set<char> &visited, vector<char> &path) {
    path.push_back(current);

    if (current == goal) return true;
    if (limit == 0) { path.pop_back(); return false; }

    visited.insert(current);
    for (char neighbor : graphMap[current]) {
        if (!visited.count(neighbor)) {
            if (depthLimitedSearch(neighbor, goal, limit - 1, visited, path))
                return true;
        }
    }

    path.pop_back();
    return false;
}

vector<char> iterativeDeepening(char start, char goal) {
    for (int depth = 0; ; depth++) {
        set<char> visited;
        vector<char> path;
        if (depthLimitedSearch(start, goal, depth, visited, path))
            return path;
    }
}

int main() {
    char start = 'P';
    char goal = 'X';
    vector<char> path = iterativeDeepening(start, goal);

    cout << "Path from " << start << " to " << goal << ": ";
    for (char node : path) cout << node << " ";
    cout << endl;

    return 0;
}
