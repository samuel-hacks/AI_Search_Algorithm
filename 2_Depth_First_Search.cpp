#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>
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

string depthSearch(char node, char target, set<char>& seen) {
    seen.insert(node);
    if (node == target) {
        string p = "";
        p += node;
        return p;
    }
    for (char next : graphMap[node]) {
        if (seen.find(next) == seen.end()) {
            string partPath = depthSearch(next, target, seen);
            if (!partPath.empty()) {
                string fullPath = "";
                fullPath += node + partPath;
                return fullPath;
            }
        }
    }
    return "";
}

string runDFS(char start, char target) {
    set<char> visitedNodes;
    return depthSearch(start, target, visitedNodes);
}

int main() {
    char start = 'P';
    char goal = 'X';
    string path = runDFS(start, goal);
    cout << "Paths from " << start << " to " << goal << endl;
    if (!path.empty()) {
        cout << "Path found: " << path << endl;
    } else {
        cout << "No path found." << endl;
    }
    return 0;
}
