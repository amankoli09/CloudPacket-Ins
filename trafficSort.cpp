#ifndef TRAFFIC_SORTER_H
#define TRAFFIC_SORTER_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Stream {
  string streamID, sourceIP;
  int dataVolume; // bytes sent — used for ranking
};

class TrafficSorter {
private:
  vector<Stream> heap;

  void heapifyUp(int i) {
    while (i > 0 && heap[i].dataVolume > heap[(i - 1) / 2].dataVolume) {
      swap(heap[i], heap[(i - 1) / 2]);
      i = (i - 1) / 2;
    }
  }

  // Push a node DOWN while a child is bigger than it
  void heapifyDown(int i) {
    int n = heap.size();
    while (true) {
      int big = i, l = 2 * i + 1, r = 2 * i + 2;
      if (l < n && heap[l].dataVolume > heap[big].dataVolume)
        big = l;
      if (r < n && heap[r].dataVolume > heap[big].dataVolume)
        big = r;
      if (big == i)
        break;
      swap(heap[i], heap[big]);
      i = big;
    }
  }

public:
  // Add a stream, then fix the heap so the biggest stays on top
  void addStream(string id, string src, int volume) {
    heap.push_back({id, src, volume});
    heapifyUp(heap.size() - 1);
    cout << "[+] Stream " << id << " (" << volume << " bytes) added.\n";
  }

  // Look at the highest-volume stream without removing it
  void peekTop() {
    if (heap.empty()) {
      cout << "[-] No streams.\n";
      return;
    }
    cout << "[!] TOP SUSPECT: " << heap[0].streamID << " from "
         << heap[0].sourceIP << " | " << heap[0].dataVolume << " bytes\n";
  }

  // Remove the highest-volume stream (flag it)
  void extractMax() {
    if (heap.empty()) {
      cout << "[-] No streams.\n";
      return;
    }
    cout << "[FLAGGED] " << heap[0].streamID << " | " << heap[0].dataVolume
         << " bytes removed.\n";
    heap[0] = heap.back(); // move last item to the root
    heap.pop_back();
    if (!heap.empty())
      heapifyDown(0);
  }

  // Show all streams from highest to lowest volume
  void displayRanked() {
    if (heap.empty()) {
      cout << "[-] No streams.\n";
      return;
    }
    TrafficSorter temp = *this; // copy so the original stays intact
    cout << "\n--- Streams Ranked by Volume ---\n";
    int rank = 1;
    while (!temp.heap.empty()) {
      cout << rank++ << ". " << temp.heap[0].streamID << " | "
           << temp.heap[0].sourceIP << " | " << temp.heap[0].dataVolume
           << " bytes\n";
      temp.extractMax();
    }
    cout << "--------------------------------\n";
  }

  void run() {
    int choice;
    cout << "\n===== TRAFFIC SORTER (Max Heap) =====\n";

    do {
      cout << "\n1. Add stream\n"
              "2. View top suspect (peek)\n"
              "3. Flag & remove top suspect\n"
              "4. View all ranked\n"
              "0. Back\nChoice: ";
      cin >> choice;
      cin.ignore();

      if (choice == 1) {
        string id, src;
        int vol;
        cout << "Stream ID: ";
        getline(cin, id);
        cout << "Source IP: ";
        getline(cin, src);
        cout << "Data Volume (bytes): ";
        cin >> vol;
        cin.ignore();
        addStream(id, src, vol);
      } else if (choice == 2) {
        peekTop();
      } else if (choice == 3) {
        extractMax();
      } else if (choice == 4) {
        displayRanked();
      }

    } while (choice != 0);
  }
};

#endif
