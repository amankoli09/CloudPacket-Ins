#ifndef INSPECTION_LOG_H
#define INSPECTION_LOG_H

#include <iostream>
#include <string>
using namespace std;

struct LogEntry {
  string rule, result, timestamp;
  LogEntry *prev;
  LogEntry *next;
};

class InspectionLog {
private:
  LogEntry *head;
  LogEntry *tail;
  int size;

public:
  InspectionLog() : head(nullptr), tail(nullptr), size(0) {}

  // PUSH — This will add a new log entry at the tail (newest end)
  void push(string rule, string result, string time) {
    LogEntry *e = new LogEntry();
    e->rule = rule;
    e->result = result;
    e->timestamp = time;
    e->prev = tail;    // link back to the current newest
    e->next = nullptr; // nothing newer than this yet

    if (!tail)
      head = tail = e; // first entry in an empty list
    else {
      tail->next = e; // old newest now points forward to e
      tail = e;       // e becomes the new tail
    }
    size++;
    cout << "[+] Log: [" << time << "] " << rule << " → " << result << "\n";
  }

  // POP — This will remove the newest entry from the tail (rollback, LIFO)
  void pop() {
    if (!tail) {
      cout << "[-] Log empty.\n";
      return;
    }
    LogEntry *del = tail;
    tail = tail->prev;
    if (tail)
      tail->next = nullptr;
    else
      head = nullptr;
    cout << "[~] Rolled back: " << del->rule << "\n";
    delete del;
    size--;
  }

  // PEEK — This will just look at the newest entry without removing it
  void peek() {
    if (!tail) {
      cout << "[-] Log empty.\n";
      return;
    }
    cout << "[Latest] [" << tail->timestamp << "] " << tail->rule << " → "
         << tail->result << "\n";
  }

  // Print all entries from newest to oldest (walk backwards via prev)
  void displayAll() {
    if (!tail) {
      cout << "[-] Log empty.\n";
      return;
    }
    cout << "\n--- Inspection Log (newest first) ---\n";
    LogEntry *cur = tail;
    int count = 1;
    while (cur) {
      cout << count++ << ". [" << cur->timestamp << "] " << cur->rule << " → "
           << cur->result << "\n";
      cur = cur->prev;
    }
    cout << "--- Total: " << size << " ---\n";
  }

  void displayChronological() {
    if (!head) {
      cout << "[-] Log empty.\n";
      return;
    }
    cout << "\n--- Inspection Log (oldest first) ---\n";
    LogEntry *cur = head;
    int count = 1;
    while (cur) {
      cout << count++ << ". [" << cur->timestamp << "] " << cur->rule << " → "
           << cur->result << "\n";
      cur = cur->next;
    }
    cout << "--- Total: " << size << " ---\n";
  }

  void run() {
    int choice;
    string rule, result, time;
    int logCount = 1;
    cout << "\n===== INSPECTION LOG (Doubly Linked List) =====\n";

    do {
      cout << "\n1. Add log entry\n"
              "2. Rollback last\n"
              "3. View latest\n"
              "4. View all (newest first)\n"
              "5. View all (oldest first)\n"
              "0. Back\nChoice: ";
      cin >> choice;
      cin.ignore();

      if (choice == 1) {
        cout << "Rule (e.g. BLOCK port 22): ";
        getline(cin, rule);
        cout << "Result (PASSED/BLOCKED): ";
        getline(cin, result);
        push(rule, result, "T+" + to_string(logCount++));
      } else if (choice == 2) {
        pop();
      } else if (choice == 3) {
        peek();
      } else if (choice == 4) {
        displayAll();
      } else if (choice == 5) {
        displayChronological();
      }

    } while (choice != 0);
  }
};

#endif
