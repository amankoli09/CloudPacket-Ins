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

## Overview

**DeepScan** is a network packet inspection engine built as a **DSA Sprint Project**. Each feature of a real-world security system is mapped to a fundamental data structure — so the project doubles as a working tool *and* a hands-on demonstration of how data structures solve real problems.

Pick a module from the menu, and DeepScan shows the data structure in action: detecting threats, queuing packets, balancing server load, routing traffic, and more.

---

## Features & Data Structures

| # | Module | Data Structure | What It Does |
|:-:|:-------|:--------------:|:-------------|
| 1 | **Threat Dictionary** | `Trie` | Lightning-fast threat-signature lookup & prefix search |
| 2 | **Inspection Log** | `Doubly Linked List` | Firewall rule history with two-way audit & rollback |
| 3 | **Scanning Line** | `Queue (FIFO)` | Processes packets fairly, in arrival order |
| 4 | **Connection Check** | `Hash Map` | O(1) session lookup with collision chaining |
| 5 | **Traffic Sorter** | `Max Heap` | Ranks highest-volume (most suspicious) streams |
| 6 | **Firewall Map** | `Graph + BFS` | Models security zones & explores the network |
| 7 | **Fast Pass** | `Dijkstra` | Finds the lowest-latency path between zones |
| 8 | **Load Balancer** | `Min Heap` | Routes tasks to the least-busy server |

---

## Getting Started

### Prerequisites
- A C++ compiler supporting **C++17** (`g++`, `clang++`, or MSVC)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/amankoli/deepscan.git
cd deepscan

# Compile
g++ -std=c++17 main.cpp -o deepscan

# Run
./deepscan
```

> On Windows, run `deepscan.exe` instead of `./deepscan`.

---

## Usage

Once running, you'll see the main menu:

```
  Cloud Network Packet Deep Inspection Core
  -----------------------------------------

╔══════════════════════════════════════════╗
║           DEEPSCAN MAIN MENU             ║
╠══════════════════════════════════════════╣
║  1. Threat Dictionary    [Trie]           ║
║  2. Inspection Log       [Stack]          ║
║  3. Scanning Line        [Queue]          ║
║  4. Connection Check     [Hash Map]       ║
║  5. Traffic Sorter       [Max Heap]       ║
║  6. Firewall Map         [Graph]          ║
║  7. Fast Pass            [Dijkstra]       ║
║  8. Load Balancer        [Min Heap]       ║
╠══════════════════════════════════════════╣
║  0. Exit DeepScan                        ║
╚══════════════════════════════════════════╝
```

Type a number to enter a module, then follow its sub-menu. Type `0` to go back or exit.

---

## Project Structure

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

## Complexity Cheat-Sheet

| Operation | Structure | Time Complexity |
|:----------|:----------|:---------------:|
| Insert / Search keyword | Trie | `O(L)` |
| Push / Pop / Peek log | Doubly Linked List | `O(1)` |
| Enqueue / Dequeue packet | Queue | `O(1)` |
| Add / Verify session | Hash Map | `O(1)` avg |
| Insert / Extract top | Heap | `O(log n)` |
| Shortest path | Dijkstra | `O(V²)` |

---

## Built With

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=cplusplus&logoColor=white)
![STL](https://img.shields.io/badge/STL-Standard_Library-blue?style=flat)
![VS Code](https://img.shields.io/badge/VS_Code-007ACC?style=flat&logo=visualstudiocode&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=flat&logo=git&logoColor=white)

---

## Author

**Aman Koli**

> DSA Sprint Project — demonstrating core data structures through a real-world network security simulation.
