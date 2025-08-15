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

int branch_and_bound_history(unordered_map<char, vector<pair<char, int>>>& graph,
                             char start, char goal, int bound,
                             vector<char>& visited_order, vector<char>& best_path)
{
    struct State {
        int cost;
        char node;
        vector<char> path;
    };
    struct Cmp {
        bool operator()(const State& a, const State& b) const { return a.cost > b.cost; }
    };

    priority_queue<State, vector<State>, Cmp> pq;
    pq.push({0, start, vector<char>(1, start)});

    unordered_map<char, int> best_g;

    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
        visited_order.push_back(cur.node);

        if (cur.cost > bound) continue;
        if (cur.node == goal) { best_path = cur.path; return cur.cost; }

        if (best_g.count(cur.node) && cur.cost >= best_g[cur.node]) continue;
        best_g[cur.node] = cur.cost;

        for (auto& nb : graph[cur.node]) {
            char nxt = nb.first;
            int w = nb.second;
            if (find(cur.path.begin(), cur.path.end(), nxt) != cur.path.end()) continue;
            vector<char> np = cur.path;
            np.push_back(nxt);
            pq.push({cur.cost + w, nxt, np});
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
    vector<char> visited_order, best_path;
    int result = branch_and_bound_history(graph, 'P', 'X', oracle_distance, visited_order, best_path);
    if (result != -1) {
        cout << "Best path cost via Branch and Bound: " << result << endl;
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
