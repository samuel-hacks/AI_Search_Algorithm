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

int a_star_history(unordered_map<char, vector<pair<char, int>>>& graph,
                   unordered_map<char, int>& heuristic,
                   char start, char goal,
                   vector<char>& visited_order, vector<char>& best_path)
{
    struct State {
        int g; // cost so far
        int f; // g + h
        char node;
        vector<char> path;
    };
    struct Cmp {
        bool operator()(const State& a, const State& b) const { return a.f > b.f; }
    };

    priority_queue<State, vector<State>, Cmp> pq;
    pq.push({0, heuristic[start], start, vector<char>(1, start)});

    unordered_map<char, int> best_g;

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        visited_order.push_back(cur.node);

        if (cur.node == goal) { best_path = cur.path; return cur.g; }

        if (best_g.count(cur.node) && cur.g >= best_g[cur.node]) continue;
        best_g[cur.node] = cur.g;

        for (auto& nb : graph[cur.node]) {
            char nxt = nb.first;
            int w = nb.second;
            if (find(cur.path.begin(), cur.path.end(), nxt) != cur.path.end()) continue;
            vector<char> np = cur.path;
            np.push_back(nxt);
            int g_new = cur.g + w;
            int f_new = g_new + heuristic[nxt];
            pq.push({g_new, f_new, nxt, np});
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

    // Heuristic values (straight-line estimate to goal 'X')
    unordered_map<char, int> heuristic;
    heuristic['P'] = 7;
    heuristic['Q'] = 6;
    heuristic['R'] = 5;
    heuristic['S'] = 4;
    heuristic['T'] = 5;
    heuristic['U'] = 3;
    heuristic['V'] = 2;
    heuristic['W'] = 6;
    heuristic['X'] = 0;

    // Oracle to get smallest possible path for comparison
    vector<char> path = {'P'};
    int oracle_distance = oracle(graph, 'P', 'X', path, 0);
    if (oracle_distance == INT_MAX)
        cout << "Goal not reachable." << endl;
    else
        cout << "Smallest path distance (oracle): " << oracle_distance << endl;

    cout << "\n--- A* Search ---\n";
    vector<char> visited_order, best_path;
    int result = a_star_history(graph, heuristic, 'P', 'X', visited_order, best_path);
    if (result != -1) {
        cout << "Best path cost via A*: " << result << endl;
        cout << "Visited Order: ";
        for (size_t i = 0; i < visited_order.size(); ++i) {
            cout << visited_order[i];
            if (i + 1 < visited_order.size()) cout << " -> ";
        }
        cout << endl;
        cout << "Best Path: ";
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i];
            if (i + 1 < best_path.size()) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "Goal not reachable." << endl;
    }

    return 0;
}
