<div align="center">

# DeepScan

### Cloud Network Packet Deep Inspection Core

*A console-based network security simulator where every module is powered by a core Data Structure & Algorithm.*

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Cross--Platform-success?style=for-the-badge&logo=linux&logoColor=white)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen?style=for-the-badge&logo=githubactions&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

![Data Structures](https://img.shields.io/badge/Data_Structures-8-blueviolet?style=flat-square)
![Algorithms](https://img.shields.io/badge/Algorithms-BFS_|_Dijkstra-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Active-success?style=flat-square)

</div>

---

## Table of Contents

1. [Project Title](#1-project-title)
2. [Problem Statement](#2-problem-statement)
3. [Objectives](#3-objectives)
4. [System Overview / Architecture](#4-system-overview--architecture)
5. [Data Structures and Algorithms Used](#5-data-structures-and-algorithms-used)
6. [Implementation Approach](#6-implementation-approach)
7. [Time and Space Complexity Analysis](#7-time-and-space-complexity-analysis)
8. [Execution Steps](#8-execution-steps)
9. [Sample Inputs and Outputs](#9-sample-inputs-and-outputs)
10. [Screenshots](#10-screenshots)
11. [Results and Observations](#11-results-and-observations)
12. [Conclusion](#12-conclusion)

---

## 1. Project Title

**DeepScan — Cloud Network Packet Deep Inspection Core**

A console-based network security simulator in which every functional module is powered by a fundamental Data Structure or Algorithm.

---

## 2. Problem Statement

Modern cloud networks process huge volumes of traffic, and a security system must perform many different tasks at once:

- Detect known **threat signatures** instantly.
- Maintain a **history of firewall rule changes** that can be audited and rolled back.
- Inspect incoming **packets fairly**, in the order they arrive.
- Track **active sessions** and verify them quickly.
- Identify the **highest-volume (most suspicious) traffic** streams.
- Represent the **network topology** of security zones and explore it.
- Route traffic along the **lowest-latency path**.
- Distribute inspection workload across servers to **prevent overload**.

Doing each of these efficiently requires choosing the *right* data structure. A naïve approach (e.g. scanning lists linearly) does not scale. **DeepScan** solves each sub-problem with the data structure best suited to it, demonstrating both a working security tool and the practical value of DSA.

---

## 3. Objectives

1. Build a modular network-inspection tool with a clean menu-driven interface.
2. Implement **8 core data structures / algorithms**, each mapped to a real security task.
3. Demonstrate efficient operations (fast lookup, ordered processing, shortest path, load balancing).
4. Keep each module self-contained, readable, and independently testable.
5. Analyse the time and space complexity of every operation.

---

## 4. System Overview / Architecture

DeepScan is a single C++ program assembled from 9 source files. `main.cpp` is the entry point; it includes the 8 module files and drives a menu loop. Each module is a self-contained class exposing a `run()` method.

```
                        +------------------+
                        |     main.cpp     |
                        |  (Menu + Driver) |
                        +--------+---------+
                                 |
        +------------+-----------+-----------+------------+
        |            |           |           |            |
   ThreatDict   Inspection   Scanning   Connection   TrafficSort
     (Trie)       Log         Line        Check       (Max Heap)
              (Doubly LL)    (Queue)    (Hash Map)
        |            |           |           |            |
        +------------+-----------+-----------+------------+
                                 |
              +------------------+------------------+
              |                  |                  |
        FirewallMap          FastPass          LoadBalancer
        (Graph + BFS)        (Dijkstra)         (Min Heap)
```

**Flow:** User launches the program → main menu appears → user selects a module (1–8) → that module's sub-menu runs until the user chooses `0` to return → user exits with `0`.

---

## 5. Data Structures and Algorithms Used

| # | Module | Data Structure / Algorithm | Role |
|:-:|:-------|:---------------------------|:-----|
| 1 | Threat Dictionary | **Trie** | Store & search threat keywords, prefix matching |
| 2 | Inspection Log | **Doubly Linked List** | Firewall rule history with two-way traversal & rollback |
| 3 | Scanning Line | **Queue (FIFO)** | Process packets in arrival order |
| 4 | Connection Check | **Hash Map (chaining)** | Fast session lookup / verification |
| 5 | Traffic Sorter | **Max Heap** | Rank highest-volume traffic streams |
| 6 | Firewall Map | **Graph (adjacency list) + BFS** | Model zones, traverse the network |
| 7 | Fast Pass | **Dijkstra's Algorithm** | Lowest-latency path between zones |
| 8 | Load Balancer | **Min Heap** | Assign tasks to least-busy server |

---

## 6. Implementation Approach

- **Language:** C++ (C++17), using the Standard Template Library (`map`, `vector`, `queue`, `string`).
- **Modular design:** Each data structure lives in its own file with include guards (`#ifndef … #define … #endif`), and is included into `main.cpp`. This keeps modules independent and easy to test.
- **Uniform interface:** Every module exposes a `run()` method with its own sub-menu, so `main.cpp` only needs to call `module.run()`.
- **Key implementation choices:**
  - **Trie:** each node holds 26 child pointers (a–z) and an `isEndOfWord` flag.
  - **Doubly Linked List:** each node has `prev` and `next`; push/pop at the tail keep rollback LIFO, while `next` links allow chronological (oldest-first) display.
  - **Queue:** linked-list based with `front` and `rear` pointers for O(1) enqueue/dequeue.
  - **Hash Map:** ASCII-sum hash function with **chaining** (linked list per bucket) to resolve collisions.
  - **Heaps:** stored as a flat `vector`, with `heapifyUp` and `heapifyDown` maintaining the heap property.
  - **Graph:** adjacency list (`map<string, vector<pair>>`); BFS uses a queue.
  - **Dijkstra:** repeatedly selects the nearest unvisited zone, relaxes neighbours, and stores `prev[]` to reconstruct the path.

### Project Structure

```
DeepScan/
├── main.cpp            # Entry point + main menu
├── ThreatDict.cpp      # Trie         — threat signatures
├── Inspectionlog.cpp   # Doubly Linked List — rule history
├── Scanninline.cpp     # Queue        — packet scanning line
├── ConnectionCheck.cpp # Hash Map     — active sessions
├── trafficSort.cpp     # Max Heap     — traffic ranking
├── Firewallmap.cpp     # Graph + BFS  — network zones
├── Fastpass.cpp        # Dijkstra     — fastest routing
├── loadbalancer.cpp    # Min Heap     — load balancing
└── README.md
```

---

## 7. Time and Space Complexity Analysis

| Module | Operation | Time | Space |
|:-------|:----------|:----:|:-----:|
| Threat Dictionary (Trie) | Insert / Search / Prefix | `O(L)` | `O(N·L·26)` |
| Inspection Log (Doubly LL) | Push / Pop / Peek | `O(1)` | `O(N)` |
| Scanning Line (Queue) | Enqueue / Dequeue | `O(1)` | `O(N)` |
| Connection Check (Hash Map) | Insert / Verify / Close | `O(1)` avg, `O(N)` worst | `O(N)` |
| Traffic Sorter (Max Heap) | Insert / Extract-Max | `O(log N)` | `O(N)` |
| Traffic Sorter | Peek top | `O(1)` | — |
| Firewall Map (Graph) | Add edge | `O(1)` | `O(V + E)` |
| Firewall Map (BFS) | Traversal | `O(V + E)` | `O(V)` |
| Fast Pass (Dijkstra) | Shortest path | `O(V²)` | `O(V + E)` |
| Load Balancer (Min Heap) | Assign / Complete task | `O(log N)` | `O(N)` |

*(L = keyword length, N = number of items, V = zones, E = connections.)*

---

## 8. Execution Steps

**Prerequisites:** a C++ compiler supporting C++17 (`g++`, `clang++`, or MSVC).

```bash
# 1. Go to the project folder
cd "DSA Sprint 2"

# 2. Compile (main.cpp includes all modules)
g++ -std=c++17 main.cpp -o main

# 3. Run
./main          # On Windows: main.exe
```

Then choose a module (1–8) from the main menu, follow its sub-menu, press `0` to go back, and `0` again to exit.

---

## 9. Sample Inputs and Outputs

### Example A — Fast Pass (Dijkstra)

**Input sequence:** `7` (Fast Pass) → `1` (load sample network) → `4` (find fastest path) → `Internet` → `Database` → `5` (show all distances) → `Internet` → `0` → `0`

**Output:**
```
[+] Internet <-> Firewall (1ms)
[+] Firewall <-> DMZ (2ms)
[+] Firewall <-> WAF (3ms)
[+] DMZ <-> AppServer (4ms)
[+] WAF <-> AppServer (2ms)
[+] AppServer <-> Database (5ms)
[+] Sample network loaded.

[FAST PASS] Internet -> Database : 11ms
Route: Internet -> Firewall -> WAF -> AppServer -> Database

--- Distances from Internet ---
AppServer : 6ms
DMZ : 3ms
Database : 11ms
Firewall : 1ms
Internet : 0ms
WAF : 4ms
```
> Note: Dijkstra correctly chooses `Firewall -> WAF -> AppServer` (1+3+2=6) over `Firewall -> DMZ -> AppServer` (1+2+4=7).

### Example B — Threat Dictionary (Trie)

**Input sequence:** `1` (Threat Dictionary) → `2` (search) → `malware` → `2` → `hello` → `3` (prefix) → `tro` → `0`

**Output:**
```
[+] Loaded 10 default threat signatures.
[!] THREAT FOUND!          (for "malware")
[-] Not found.             (for "hello")
[!] PREFIX MATCH found.    (for "tro" → matches "trojan")
```

### Example C — Load Balancer (Min Heap)

**Input sequence:** register two servers, assign tasks, view status.

**Output (illustrative):**
```
[+] Server S1 registered. Capacity: 5
[+] Server S2 registered. Capacity: 5
[->] Task T1 -> S1 (load: 0 -> 1)
[->] Task T2 -> S2 (load: 0 -> 1)

--- Server Load Status ---
S1 | 1/5 [##--------] 20%
S2 | 1/5 [##--------] 20%
Least busy: S1 (1 tasks)
```

---

## 10. Screenshots

> Add screenshots of the running program here. Suggested captures:
> 1. Main menu after launch.
> 2. Fast Pass module showing the fastest route (Example A).
> 3. Threat Dictionary search result.
> 4. Load Balancer load-status bars.
>
> To insert: put images in a `screenshots/` folder and reference them like:
>
> `![Main Menu](screenshots/main-menu.png)`

---

## 11. Results and Observations

- All 8 modules compile cleanly with `g++ -std=c++17` and run as a single integrated program.
- Each data structure performs its task efficiently:
  - The **Trie** searches in time proportional to keyword length, independent of dictionary size.
  - The **Queue** guarantees fair, in-order packet processing.
  - The **Hash Map** gives near-constant-time session lookup.
  - The **Heaps** always expose the top element (max-volume / least-busy) in O(1).
  - **Dijkstra** correctly finds the lowest-latency path, choosing `WAF` over `DMZ` because the total cost is lower.
- **Observation:** choosing the right data structure dramatically simplifies each problem — e.g. rollback is a single pointer move with a linked list, and finding the least-busy server is instant with a min heap.
- **Trade-off noted:** the Dijkstra implementation uses an O(V²) nearest-zone scan for clarity; a priority-queue version would be O((V+E) log V), which matters only for large networks.

---

## 12. Conclusion

DeepScan successfully demonstrates how **8 fundamental data structures and algorithms** map directly onto the real tasks of a network packet inspection system. By implementing each module independently and analysing its complexity, the project shows not only *how* to build the structures but *why* each one is the right choice for its problem.

The project meets all its objectives: a working, modular, menu-driven tool that is both a practical simulation and a clear educational reference for Trie, Linked List, Queue, Hash Map, Heap, Graph, BFS, and Dijkstra's algorithm.

**Future scope:** persist data to files, upgrade Dijkstra to a priority-queue version, add real packet capture, and build a graphical interface.

---

<div align="center">

## Author

**Aman Koli**

*DSA Sprint Project — demonstrating core data structures through a real-world network security simulation.*

</div>
