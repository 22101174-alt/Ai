
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    string to;
    double cost;
};

struct Node {
    string name;
    double f, g, h;
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

map<string, vector<Edge>> graph;
map<string, double> heuristic;

pair<vector<string>, double> aStar(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open;
    map<string, double> gScore;
    map<string, string> parent;
    set<string> closed;

    gScore[start] = 0;
    open.push({start, heuristic[start], 0, heuristic[start]});

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        if (current.name == goal) {
            vector<string> path;
            string node = goal;
            while (node != "") {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            return {path, gScore[goal]};
        }

        if (closed.count(current.name)) continue;
        closed.insert(current.name);

        for (auto& edge : graph[current.name]) {
            double tentative_g = gScore[current.name] + edge.cost;
            if (!gScore.count(edge.to) || tentative_g < gScore[edge.to]) {
                gScore[edge.to] = tentative_g;
                parent[edge.to] = current.name;
                double f = tentative_g + heuristic[edge.to];
                open.push({edge.to, f, tentative_g, heuristic[edge.to]});
            }
        }
    }
    return {{}, -1};
}

int main() {

    graph["Home"] = {{"Shyamoli", 2.8}, {"Shewrapara", 0.5}};
    graph["Shyamoli"] = {{"DRMC", 1.2}};
    graph["DRMC"] = {{"Lalmatia", 1.0}};
    graph["Lalmatia"] = {{"Khamarbari", 1.3}};
    graph["Khamarbari"] = {{"Farmgate", 0.5}, {"WestRajabajar", 0.9}};
    graph["WestRajabajar"] = {{"EastRajabajar", 0.9}};
    graph["EastRajabajar"] = {{"UAP", 0.4}};
    graph["Shewrapara"] = {{"BijoySarani", 3.1}};
    graph["BijoySarani"] = {{"Farmgate", 2.1}};
    graph["Farmgate"] = {{"KarwanBajar", 1.6}, {"EastRajabajar", 0.85}, {"UAP", 1.1}};
    graph["KarwanBajar"] = {{"Panthopath", 1.4}};
    graph["Panthopath"] = {{"UAP", 0.65}};


    heuristic["Home"] = 3.95;
    heuristic["Shyamoli"] = 3.28;
    heuristic["DRMC"] = 2.24;
    heuristic["Lalmatia"] = 1.63;
    heuristic["Khamarbari"] = 0.743;
    heuristic["WestRajabajar"] = 0.814;
    heuristic["EastRajabajar"] = 0.513;
    heuristic["Shewrapara"] = 3.27;
    heuristic["BijoySarani"] = 1.44;
    heuristic["Farmgate"] = 0.498;
    heuristic["KarwanBajar"] = 0.610;
    heuristic["Panthopath"] = 0.526;
    heuristic["UAP"] = 0.0;

    string start = "Home";
    string goal = "UAP";

    auto result = aStar(start, goal);
    vector<string> path = result.first;
    double cost = result.second;

    if (cost != -1) {
        cout << "Shortest path using A*: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal cost = " << cost << " Km" << endl;
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}
