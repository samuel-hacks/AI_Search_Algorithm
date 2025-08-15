#include <bits/stdc++.h>
using namespace std;

int oracle(unordered_map<char, vector<pair<char, int>>>& graph,
           char current, char goal,
           vector<char>& path, int cost)
{
    if (current == goal) {
        cout << "Path found: ";
        for (char node : path) cout << node << " ";
        cout << "| Distance: " << cost << endl;
        return cost;
    }

    int best = INT_MAX;

    for (auto& neighbor : graph[current]) {
        if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
            path.push_back(neighbor.first);
            best = min(best, oracle(graph, neighbor.first, goal, path, cost + neighbor.second));
            path.pop_back();
        }
    }
    return best;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    graph['P'] = {{'Q', 2}, {'R', 4}};
    graph['Q'] = {{'T', 3}, {'U', 6}};
    graph['R'] = {{'S', 5}};
    graph['S'] = {{'V', 2}};
    graph['T'] = {{'V', 4}};
    graph['U'] = {{'W', 3}};
    graph['V'] = {{'X', 5}};
    graph['W'] = {};
    graph['X'] = {};

    vector<char> path = {'P'};

    int oracle_distance = oracle(graph, 'P', 'X', path, 0);

    if (oracle_distance == INT_MAX) {
        cout << "Goal not reachable." << endl;
    } else {
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;
    }

    return 0;
}
