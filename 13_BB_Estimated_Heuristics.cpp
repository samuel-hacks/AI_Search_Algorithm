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

int branch_and_bound_heuristic(unordered_map<char, vector<pair<char, int>>>& graph,
                               unordered_map<char, int>& heuristic,
                               char start, char goal, int bound)
{
    using State = tuple<int, int, char, vector<char>>; 
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({heuristic[start], 0, start, {start}});

    while (!pq.empty()) {
        auto top = pq.top();
        int f = std::get<0>(top);
        int g = std::get<1>(top);
        char current = std::get<2>(top);
        std::vector<char> path = std::get<3>(top);

        pq.pop();

        if (g > bound)
            return -1;

        if (current == goal) {
            cout << "Path found: ";
            for (char node : path) cout << node << " ";
            cout << "| Distance: " << g << endl;
            return g;
        }

        for (auto& neighbor : graph[current]) {
            if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
                vector<char> newPath = path;
                newPath.push_back(neighbor.first);
                int newG = g + neighbor.second;
                int newF = newG + heuristic[neighbor.first];
                pq.push({newF, newG, neighbor.first, newPath});
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

    unordered_map<char, int> heuristic;
    heuristic['P'] = 7;
    heuristic['Q'] = 6;
    heuristic['R'] = 6;
    heuristic['S'] = 4;
    heuristic['T'] = 5;
    heuristic['U'] = 4;
    heuristic['V'] = 2;
    heuristic['W'] = 6;
    heuristic['X'] = 0;

    vector<char> path = {'P'};
    int oracle_distance = oracle(graph, 'P', 'X', path, 0);
    if (oracle_distance == INT_MAX)
        cout << "Goal not reachable." << endl;
    else
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;

    cout << "\n--- Branch and Bound with Heuristic ---\n";
    int result = branch_and_bound_heuristic(graph, heuristic, 'P', 'X', oracle_distance);
    if (result != -1)
        cout << "Best path cost via Branch and Bound (Heuristic): " << result << endl;

    return 0;
}
