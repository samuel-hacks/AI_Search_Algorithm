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

bool beamSearch(char start, char goal, size_t beamWidth) {
    auto cmp = [](const pair<char, vector<char>> &a, const pair<char, vector<char>> &b) {
        return heuristic[a.first] > heuristic[b.first]; // lower heuristic first
    };

    priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> currentLevel(cmp);
    currentLevel.push(make_pair(start, vector<char>{start}));

    while (!currentLevel.empty()) {
        priority_queue<pair<char, vector<char>>, vector<pair<char, vector<char>>>, decltype(cmp)> nextLevel(cmp);

        while (!currentLevel.empty()) {
            pair<char, vector<char>> temp = currentLevel.top();
            currentLevel.pop();

            char node = temp.first;
            vector<char> path = temp.second;

            if (node == goal) {
                cout << "Path from " << start << " to " << goal << ": ";
                for (char n : path) cout << n << " ";
                cout << endl;
                return true;
            }

            for (char neighbor : graphMap[node]) {
                vector<char> newPath = path;
                newPath.push_back(neighbor);
                nextLevel.push(make_pair(neighbor, newPath));
            }
        }

        vector<pair<char, vector<char>>> pruned;
        while (!nextLevel.empty() && pruned.size() < beamWidth) {
            pruned.push_back(nextLevel.top());
            nextLevel.pop();
        }

        for (auto &node : pruned) {
            currentLevel.push(node);
        }
    }

    cout << "No path found from " << start << " to " << goal << "." << endl;
    return false;
}

int main() {
    char start = 'P';
    char goal = 'X';
    size_t beamWidth = 2; 

    beamSearch(start, goal, beamWidth);
    return 0;
}
