#include <iostream>
#include <map>
#include <vector>
#include <queue>
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

string runBFS(char start, char goal) {
    queue<string> pathQueue;
    set<char> visited;
    pathQueue.push(string(1, start));
    visited.insert(start);

    while (!pathQueue.empty()) {
        string currentPath = pathQueue.front();
        pathQueue.pop();
        char currentNode = currentPath.back();

        if (currentNode == goal) {
            return currentPath;
        }

        for (char neighbor : graphMap[currentNode]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                pathQueue.push(currentPath + neighbor);
            }
        }
    }
    return "";
}

int main() {
    char start = 'P';
    char goal = 'X';
    string path = runBFS(start, goal);

    cout << "Paths from " << start << " to " << goal << endl;

    if (!path.empty()) {
        cout << "Path found: " << path << endl;
    } else {
        cout << "No path found." << endl;
    }
    return 0;
}
