#ifndef FIREWALL_MAP_H
#define FIREWALL_MAP_H

// Firewall Map uses a GRAPH (adjacency list)
// Nodes = firewall zones (e.g. DMZ, LAN, WAN)
// Edges = connections between zones with a latency cost
// Adjacency list: each zone maps to a list of its neighbours

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// One connection between two zones (an edge)
struct Connection {
    string destination;
    int latency; // cost to travel this edge in ms
};

class FirewallMap {
private:
    // "ZoneA" → [ {ZoneB, 5ms}, {ZoneC, 2ms} ]
    map<string, vector<Connection>> adjList;

public:
    // Add a new zone (node) to the graph
    void addZone(string zone) {
        if (adjList.find(zone) == adjList.end()) {
            adjList[zone] = {};
            cout << "[+] Zone \"" << zone << "\" added.\n";
        } else {
            cout << "[-] Zone \"" << zone << "\" already exists.\n";
        }
    }

    // Add a bidirectional edge between two zones
    void addConnection(string from, string to, int latency) {
        if (!adjList.count(from)) addZone(from);
        if (!adjList.count(to))   addZone(to);
        adjList[from].push_back({to,   latency}); // from → to
        adjList[to  ].push_back({from, latency}); // to → from (bidirectional)
        cout << "[+] " << from << " ↔ " << to << " (" << latency << "ms)\n";
    }

    // Print the full adjacency list
    void displayMap() {
        if (adjList.empty()) { cout << "[-] Map is empty.\n"; return; }
        cout << "\n--- Firewall Map ---\n";
        for (auto &zone : adjList) {
            cout << "[" << zone.first << "] → ";
            if (zone.second.empty()) cout << "(no connections)";
            else for (auto &c : zone.second)
                cout << c.destination << "(" << c.latency << "ms) ";
            cout << "\n";
        }
        cout << "--------------------\n";
    }

    // BFS traversal — visit all zones reachable from start, level by level
    // BFS uses a queue: visit neighbours first, then their neighbours
    void bfsTraversal(string start) {
        if (!adjList.count(start)) { cout << "[-] Zone not found.\n"; return; }

        map<string, bool> visited;
        queue<string> q;
        visited[start] = true;
        q.push(start);

        cout << "\n[BFS from " << start << "]: ";
        while (!q.empty()) {
            string cur = q.front(); q.pop();
            cout << cur << " ";
            for (auto &c : adjList[cur]) {
                if (!visited[c.destination]) {
                    visited[c.destination] = true;
                    q.push(c.destination);
                }
            }
        }
        cout << "\n";
    }

    // Used by FastPass module to run Dijkstra on the same graph
    map<string, vector<Connection>> &getAdjList() { return adjList; }

    void run() {
        int choice;
        string z1, z2;
        int lat;
        cout << "\n===== FIREWALL MAP (Graph) =====\n";

        do {
            cout << "\n1. Add zone\n"
                    "2. Add connection between zones\n"
                    "3. Display map\n"
                    "4. BFS traversal\n"
                    "0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Zone name: "; cin >> z1;
                addZone(z1);

            } else if (choice == 2) {
                cout << "From: ";        cin >> z1;
                cout << "To: ";          cin >> z2;
                cout << "Latency (ms): "; cin >> lat;
                addConnection(z1, z2, lat);

            } else if (choice == 3) {
                displayMap();

            } else if (choice == 4) {
                cout << "Start zone: "; cin >> z1;
                bfsTraversal(z1);
            }

        } while (choice != 0);
    }
};

#endif