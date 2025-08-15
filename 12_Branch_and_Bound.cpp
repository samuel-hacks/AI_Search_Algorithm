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

int branch_and_bound(unordered_map<char, vector<pair<char, int>>>& graph,
                     char start, char goal, int bound)
{
    using State = pair<int, pair<char, vector<char>>>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, {start, {start}}});
    while (!pq.empty()) {
        auto nodePathPair = pq.top();
        int cost = nodePathPair.first;
        auto nodePath = nodePathPair.second;

        char current = nodePath.first;
        auto path = nodePath.second;

        pq.pop();
        if (cost > bound)
            continue;
        if (current == goal) {
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "| Distance: " << cost << endl;
            return cost;
        }
        for (auto& neighbor : graph[current]) {
            if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
                vector<char> newPath = path;
                newPath.push_back(neighbor.first);
                pq.push({cost + neighbor.second, {neighbor.first, newPath}});
            }
        }
    }
    return -1;
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
    if (oracle_distance == INT_MAX)
        cout << "Goal not reachable." << endl;
    else
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;

    cout << "\n--- Branch and Bound ---\n";
    int result = branch_and_bound(graph, 'P', 'X', oracle_distance);
    if (result != -1)
        cout << "Best path cost via Branch and Bound: " << result << endl;

    return 0;
}
