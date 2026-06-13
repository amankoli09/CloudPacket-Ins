#ifndef SCANNING_LINE_H
#define SCANNING_LINE_H

#include <iostream>
#include <string>
using namespace std;

struct Packet {
  int id;
  string sourceIP, destIP, payload;
  int size;
  Packet *next;
};

class ScanningLine {
private:
  Packet *front;
  Packet *rear;
  int count;

public:
  ScanningLine() : front(nullptr), rear(nullptr), count(0) {}

  // ENQUEUE — new packet arrives, add it to the back of the line
  void enqueue(int id, string src, string dest, int sz, string payload) {
    Packet *p = new Packet();
    p->id = id;
    p->sourceIP = src;
    p->destIP = dest;
    p->size = sz;
    p->payload = payload;
    p->next = nullptr;

    if (!rear)
      front = rear = p;
    else {
      rear->next = p;
      rear = p;
    }
    count++;
    cout << "[+] Packet #" << id << " from " << src << " added to queue.\n";
  }

  // This dequeues the front element
  void dequeue() {
    if (!front) {
      cout << "[-] Queue empty.\n";
      return;
    }
    Packet *p = front;
    front = front->next;
    if (!front)
      rear = nullptr;

    // Show packet details
    cout << "\n[SCANNING] Packet #" << p->id << "\n"
         << "  Source : " << p->sourceIP << "\n"
         << "  Dest   : " << p->destIP << "\n"
         << "  Size   : " << p->size << " bytes\n"
         << "  Payload: " << p->payload << "\n";

    // This checks if the payload has "malware" or "exploit"
    if (p->payload.find("malware") != string::npos ||
        p->payload.find("exploit") != string::npos)
      cout << "  Status : [!] THREAT DETECTED\n";
    else
      cout << "  Status : [OK] Clean\n";

    delete p;
    count--;
  }

  // Show all packets currently waiting (without removing them)
  void viewQueue() {
    if (!front) {
      cout << "[-] Queue empty.\n";
      return;
    }
    cout << "\n--- Packet Queue ---\n";
    Packet *cur = front;
    int pos = 1;
    while (cur) {
      cout << pos++ << ". Packet #" << cur->id << " | " << cur->sourceIP
           << " → " << cur->destIP << " | " << cur->size << " bytes\n";
      cur = cur->next;
    }
    cout << "--- Waiting: " << count << " ---\n";
  }

  void run() {
    int choice, idCounter = 1;
    cout << "\n===== SCANNING LINE (Queue) =====\n";

    do {
      cout << "\n1. Add packet\n"
              "2. Process next packet\n"
              "3. View queue\n"
              "0. Back\nChoice: ";
      cin >> choice;
      cin.ignore();

      if (choice == 1) {
        string src, dest, payload;
        int sz;
        cout << "Source IP: ";
        getline(cin, src);
        cout << "Dest IP: ";
        getline(cin, dest);
        cout << "Size (bytes): ";
        cin >> sz;
        cin.ignore();
        cout << "Payload: ";
        getline(cin, payload);
        enqueue(idCounter++, src, dest, sz, payload);

      }

      else if (choice == 2) {
        dequeue();
      }

      else if (choice == 3) {
        viewQueue();
      }

    } while (choice != 0);
  }
};

#endif