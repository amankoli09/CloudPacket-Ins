#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

// Load Balancer uses a MIN HEAP
// A min heap keeps the server with the LOWEST load at index 0
// So we can always instantly find the least busy server
// Rule: parent <= children (every parent has less load than its kids)

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// One security server
struct Server {
    string serverID;
    int load;     // current number of tasks
    int capacity; // maximum tasks it can handle
};

class LoadBalancer {
private:
    vector<Server> heap; // min-heap stored as a flat array

    // After inserting at the end, bubble UP if the new server has less load than its parent
    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heap[(size_t)idx].load < heap[(size_t)parent].load) {
                swap(heap[(size_t)idx], heap[(size_t)parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    // After changing the root, push it DOWN until heap rule is restored
    void heapifyDown(int idx) {
        int n = (int)heap.size();
        while (true) {
            int smallest = idx;
            int left  = 2 * idx + 1;
            int right = 2 * idx + 2;

            if (left  < n && heap[(size_t)left ].load < heap[(size_t)smallest].load)
                smallest = left;
            if (right < n && heap[(size_t)right].load < heap[(size_t)smallest].load)
                smallest = right;

            if (smallest != idx) {
                swap(heap[(size_t)idx], heap[(size_t)smallest]);
                idx = smallest;
            } else {
                break; // already in the right position
            }
        }
    }

public:
    // Register a new server with a given capacity
    void addServer(string id, int capacity) {
        heap.push_back({id, 0, capacity}); // starts with 0 load
        heapifyUp((int)heap.size() - 1);
        cout << "[+] Server " << id << " registered. Capacity: " << capacity << "\n";
    }

    // Assign a task to the least busy server (always at index 0)
    void assignTask(string taskID) {
        if (heap.empty()) { cout << "[-] No servers.\n"; return; }
        if (heap[0].load >= heap[0].capacity) {
            cout << "[!] All servers full. Task " << taskID << " queued.\n";
            return;
        }
        cout << "[→] Task " << taskID << " → " << heap[0].serverID
             << " (load: " << heap[0].load << " → " << heap[0].load + 1 << ")\n";
        heap[0].load++;         // increase server load
        heapifyDown(0);         // this server might no longer be the minimum — fix the heap
    }

    // Mark one task as done on a specific server, reducing its load
    void completeTask(string serverID) {
        for (int i = 0; i < (int)heap.size(); i++) {
            if (heap[(size_t)i].serverID == serverID) {
                if (heap[(size_t)i].load == 0) { cout << "[-] No tasks to complete.\n"; return; }
                heap[(size_t)i].load--;
                cout << "[✓] Task done on " << serverID << ". Load: " << heap[(size_t)i].load << "\n";
                heapifyUp(i); // load dropped — this server might now be the minimum
                return;
            }
        }
        cout << "[-] Server " << serverID << " not found.\n";
    }

    // Show all servers with a visual load bar
    void displayStatus() {
        if (heap.empty()) { cout << "[-] No servers.\n"; return; }
        cout << "\n--- Server Load Status ---\n";
        for (auto &s : heap) {
            int pct = s.capacity > 0 ? (s.load * 100 / s.capacity) : 0;
            cout << s.serverID << " | " << s.load << "/" << s.capacity << " [";
            int bars = pct / 10; // each bar = 10%
            for (int i = 0; i < 10; i++) cout << (i < bars ? "#" : "-");
            cout << "] " << pct << "%\n";
        }
        cout << "Least busy: " << heap[0].serverID << " (" << heap[0].load << " tasks)\n";
        cout << "--------------------------\n";
    }

    void run() {
        int choice;
        string id;
        int cap;
        cout << "\n===== LOAD BALANCER (Min Heap) =====\n";

        do {
            cout << "\n1. Register server\n"
                    "2. Assign task to least busy server\n"
                    "3. Complete a task on a server\n"
                    "4. View all server loads\n"
                    "0. Back\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                cout << "Server ID: "; cin >> id;
                cout << "Capacity: ";  cin >> cap;
                addServer(id, cap);

            } else if (choice == 2) {
                cout << "Task ID: "; cin >> id;
                assignTask(id);

            } else if (choice == 3) {
                cout << "Server ID: "; cin >> id;
                completeTask(id);

            } else if (choice == 4) {
                displayStatus();
            }

        } while (choice != 0);
    }
};

#endif