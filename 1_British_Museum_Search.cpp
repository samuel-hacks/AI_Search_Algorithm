#include <iostream>
#include <map>
#include <vector>
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

void britishMuseumSearch(char node, char goal, string path, vector<string> &allPaths) {
    path += node;

    if (node == goal) {
        allPaths.push_back(path);
        return;
    }

    for (char nextNode : graphMap[node]) {
        
        if (path.find(nextNode) == string::npos) {
            britishMuseumSearch(nextNode, goal, path, allPaths);
        }
    }
}

int main() {
    char start = 'P';
    char target = 'X';

    vector<string> foundPaths;
    britishMuseumSearch(start, target, "", foundPaths);

    if (!foundPaths.empty()) {
        cout << "Paths from " << start << " to " << target << ":\n";
        for (auto &p : foundPaths) {
            cout << p << endl;
        }
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
