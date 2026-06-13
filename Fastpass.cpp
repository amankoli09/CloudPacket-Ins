#ifndef FAST_PASS_H
#define FAST_PASS_H

// Fast Pass — Dijkstra: shortest (lowest-latency) path between zones
// graph: zone -> list of {neighbour, cost}

#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class FastPass {
private:
  map<string, vector<pair<string, int>>> graph;

  void addZone(string z) {
    if (!graph.count(z))
      graph[z] = {};
  }

  // Dijkstra: fill dist[] and prev[] from source
  void computeDistances(string src, map<string, int> &dist,
                        map<string, string> &prev) {
    map<string, bool> done;
    for (auto &z : graph)
      dist[z.first] = INT_MAX;
    dist[src] = 0;

    for (size_t s = 0; s < graph.size(); s++) {
      // pick nearest unvisited zone
      string cur = "";
      int best = INT_MAX;
      for (auto &z : graph)
        if (!done[z.first] && dist[z.first] < best)
          best = dist[z.first], cur = z.first;
      if (cur == "")
        break;
      done[cur] = true;

      // relax neighbours
      for (auto &e : graph[cur])
        if (dist[cur] + e.second < dist[e.first]) {
          dist[e.first] = dist[cur] + e.second;
          prev[e.first] = cur;
        }
    }
  }

public:
  void addPath(string from, string to, int cost) {
    addZone(from);
    addZone(to);
    graph[from].push_back({to, cost});
    graph[to].push_back({from, cost});
    cout << "[+] " << from << " <-> " << to << " (" << cost << "ms)\n";
  }

  void dijkstra(string src, string target) {
    if (!graph.count(src) || !graph.count(target)) {
      cout << "[-] Zone not found.\n";
      return;
    }
    map<string, int> dist;
    map<string, string> prev;
    computeDistances(src, dist, prev);

    if (dist[target] == INT_MAX) {
      cout << "[-] No path.\n";
      return;
    }

    cout << "\n[FAST PASS] " << src << " -> " << target << " : " << dist[target]
         << "ms\nRoute: ";
    vector<string> path;
    for (string s = target; s != src; s = prev[s])
      path.push_back(s);
    path.push_back(src);
    for (int i = path.size() - 1; i >= 0; i--)
      cout << path[i] << (i > 0 ? " -> " : "\n");
  }

  void showAllDistances(string src) {
    if (!graph.count(src)) {
      cout << "[-] Zone not found.\n";
      return;
    }
    map<string, int> dist;
    map<string, string> prev;
    computeDistances(src, dist, prev);
    cout << "\n--- Distances from " << src << " ---\n";
    for (auto &z : dist)
      cout << z.first << " : "
           << (z.second == INT_MAX ? "unreachable" : to_string(z.second) + "ms")
           << "\n";
  }

  void loadSampleNetwork() {
    addPath("Internet", "Firewall", 1);
    addPath("Firewall", "DMZ", 2);
    addPath("Firewall", "WAF", 3);
    addPath("DMZ", "AppServer", 4);
    addPath("WAF", "AppServer", 2);
    addPath("AppServer", "Database", 5);
    cout << "[+] Sample network loaded.\n";
  }

  void run() {
    int choice, cost;
    string z1, z2;
    cout << "\n===== FAST PASS (Dijkstra) =====\n";
    do {
      cout << "\n1. Load sample network\n2. Add zone\n3. Add path\n"
              "4. Find fastest path\n5. Show all distances\n0. Back\nChoice: ";
      cin >> choice;
      if (choice == 1)
        loadSampleNetwork();
      else if (choice == 2) {
        cout << "Zone: ";
        cin >> z1;
        addZone(z1);
        cout << "[+] Zone added.\n";
      } else if (choice == 3) {
        cout << "From: ";
        cin >> z1;
        cout << "To: ";
        cin >> z2;
        cout << "Cost: ";
        cin >> cost;
        addPath(z1, z2, cost);
      } else if (choice == 4) {
        cout << "Source: ";
        cin >> z1;
        cout << "Target: ";
        cin >> z2;
        dijkstra(z1, z2);
      } else if (choice == 5) {
        cout << "Source: ";
        cin >> z1;
        showAllDistances(z1);
      }
    } while (choice != 0);
  }
};

#endif
