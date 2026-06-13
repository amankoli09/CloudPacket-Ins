#ifndef THREAT_DICTIONARY_H
#define THREAT_DICTIONARY_H

// Threat Dictionary uses a TRIE
// A Trie is a tree where each node is one character
// So "malware" = m→a→l→w→a→r→e  (7 nodes, very fast lookup)

#include <iostream>
#include <string>
using namespace std;

// Each node holds 26 children (one per letter a-z)
struct TrieNode {

  TrieNode *children[26];
  bool isEndOfWord; // true if a keyword ends here

  TrieNode() {
    for (int i = 0; i < 26; i++)
      children[i] = nullptr;
    isEndOfWord = false;
  }
};

class ThreatDictionary {

private:
  TrieNode *root; // starting point of the trie

public:
  ThreatDictionary() { root = new TrieNode(); }

  // Add a keyword letter by letter into the trie
  void insert(string keyword) {
    TrieNode *cur = root;
    for (char ch : keyword) {
      int idx = ch - 'a'; // convert 'a'→0, 'b'→1, ... 'z'→25
      if (!cur->children[idx])
        cur->children[idx] = new TrieNode();
      cur = cur->children[idx];
    }
    cur->isEndOfWord = true; // mark end of this keyword
  }

  // Search for an exact keyword — walks the trie character by character
  bool search(string keyword) {
    TrieNode *cur = root;
    for (char ch : keyword) {
      int idx = ch - 'a';
      if (!cur->children[idx])
        return false;
      cur = cur->children[idx];
    }
    return cur->isEndOfWord;
  }

  // This is the check if any stored keyword starts with this prefix
  bool startsWith(string prefix) {
    TrieNode *cur = root;
    for (char ch : prefix) {
      int idx = ch - 'a';
      if (!cur->children[idx])
        return false;
      cur = cur->children[idx];
    }
    return true; // prefix path exists
  }

  // Load 10 common threats when the module starts
  void loadDefaultThreats() {
    insert("malware");
    insert("virus");
    insert("trojan");
    insert("ransomware");
    insert("spyware");
    insert("rootkit");
    insert("botnet");
    insert("phishing");
    insert("exploit");
    insert("backdoor");
    cout << "[+] Loaded 10 default threat signatures.\n";
  }

  void run() {
    int choice;
    string keyword;
    cout << "\n===== THREAT DICTIONARY (Trie) =====\n";
    loadDefaultThreats();

    do {
      cout << "\n1. Add threat keyword\n"
              "2. Search exact keyword\n"
              "3. Search by prefix\n"
              "0. Back\nChoice: ";
      cin >> choice;

      if (choice == 1) {
        cout << "Keyword: ";
        cin >> keyword;
        insert(keyword);
        cout << "[+] \"" << keyword << "\" added.\n";

      } else if (choice == 2) {
        cout << "Keyword: ";
        cin >> keyword;
        cout << (search(keyword) ? "[!] THREAT FOUND!\n" : "[-] Not found.\n");

      } else if (choice == 3) {
        cout << "Prefix: ";
        cin >> keyword;
        cout << (startsWith(keyword) ? "[!] PREFIX MATCH found.\n"
                                     : "[-] No match.\n");
      }

    } while (choice != 0);
  }
};

#endif