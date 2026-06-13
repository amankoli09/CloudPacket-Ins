#ifndef CONNECTION_CHECK_H
#define CONNECTION_CHECK_H

#include <iostream>
#include <string>
using namespace std;

struct Session {
  string sessionID, sourceIP, destIP, status;
  Session *next;
};

class ConnectionCheck {
private:
  static const int TABLE_SIZE = 10; // 10 buckets
  Session *table[TABLE_SIZE];

  // Hash function: sum ASCII values of all chars, then mod by table size
  // This gives a bucket index from 0 to 9
  int hashFunction(string key) {
    int sum = 0;
    for (char ch : key)
      sum += (int)ch;
    return sum % TABLE_SIZE;
  }

public:
  ConnectionCheck() {
    for (int i = 0; i < TABLE_SIZE; i++)
      table[i] = nullptr;
  }

  // This is for adding the new session entery
  void addSession(string id, string src, string dest) {
    int idx = hashFunction(id);

    // Check if it already exists in this bucket
    for (Session *cur = table[idx]; cur; cur = cur->next) {
      if (cur->sessionID == id) {
        cout << "[-] Session " << id << " already exists.\n";
        return;
      }
    }

    // Create and insert at the front of the bucket's chain
    Session *s = new Session();
    s->sessionID = id;
    s->sourceIP = src;
    s->destIP = dest;
    s->status = "ACTIVE";
    s->next = table[idx];
    table[idx] = s;
    cout << "[+] Session " << id << " registered (bucket " << idx << ").\n";
  }

  // Check if a session exists and is still active
  bool verifySession(string id) {
    int idx = hashFunction(id);
    for (Session *cur = table[idx]; cur; cur = cur->next)
      if (cur->sessionID == id)
        return cur->status == "ACTIVE";
    return false; // not found
  }

  // Mark a session as closed
  void closeSession(string id) {
    int idx = hashFunction(id);
    for (Session *cur = table[idx]; cur; cur = cur->next) {
      if (cur->sessionID == id) {
        cur->status = "CLOSED";
        cout << "[~] Session " << id << " closed.\n";
        return;
      }
    }
    cout << "[-] Session " << id << " not found.\n";
  }

  // Print all sessions in all buckets
  void displayAll() {
    cout << "\n--- Connection Table ---\n";
    bool found = false;
    for (int i = 0; i < TABLE_SIZE; i++) {
      if (table[i]) {
        found = true;
        cout << "Bucket " << i << ": ";
        for (Session *cur = table[i]; cur; cur = cur->next)
          cout << "[" << cur->sessionID << "|" << cur->sourceIP << "→"
               << cur->destIP << "|" << cur->status << "] ";
        cout << "\n";
      }
    }
    if (!found)
      cout << "No sessions registered.\n";
    cout << "------------------------\n";
  }

  void run() {
    int choice;
    string id, src, dest;
    cout << "\n===== CONNECTION CHECK (Hash Map) =====\n";

    do {
      cout << "\n1. Register session\n"
              "2. Verify session\n"
              "3. Close session\n"
              "4. Show all sessions\n"
              "0. Back\nChoice: ";
      cin >> choice;

      if (choice == 1) {
        cout << "Session ID: ";
        cin >> id;
        cout << "Source IP: ";
        cin >> src;
        cout << "Dest IP: ";
        cin >> dest;
        addSession(id, src, dest);

      } else if (choice == 2) {
        cout << "Session ID: ";
        cin >> id;
        cout << (verifySession(id) ? "[OK] ACTIVE\n"
                                   : "[!] NOT active or not found.\n");

      } else if (choice == 3) {
        cout << "Session ID: ";
        cin >> id;
        closeSession(id);

      } else if (choice == 4) {
        displayAll();
      }

    } while (choice != 0);
  }
};

#endif