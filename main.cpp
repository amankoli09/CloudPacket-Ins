#include "ConnectionCheck.cpp"
#include "Fastpass.cpp"
#include "Firewallmap.cpp"
#include "Inspectionlog.cpp"
#include "Scanninline.cpp"
#include "ThreatDict.cpp"
#include "loadbalancer.cpp"
#include "trafficSort.cpp"

#include <iostream>
#include <string>
using namespace std;

void printBanner() {
  cout << "\n";
  cout << "  Cloud Network Packet Deep Inspection Core\n";
  cout << "  -----------------------------------------\n\n";
}

void printMenu() {
  cout << "\n╔══════════════════════════════════════════╗\n";
  cout << "║           DEEPSCAN MAIN MENU             ║\n";
  cout << "╠══════════════════════════════════════════╣\n";
  cout << "║  1. Threat Dictionary    [Trie]           ║\n";
  cout << "║  2. Inspection Log       [Stack]          ║\n";
  cout << "║  3. Scanning Line        [Queue]          ║\n";
  cout << "║  4. Connection Check     [Hash Map]       ║\n";
  cout << "║  5. Traffic Sorter       [Max Heap]       ║\n";
  cout << "║  6. Firewall Map         [Graph]          ║\n";
  cout << "║  7. Fast Pass            [Dijkstra]       ║\n";
  cout << "║  8. Load Balancer        [Min Heap]       ║\n";
  cout << "╠══════════════════════════════════════════╣\n";
  cout << "║  0. Exit DeepScan                        ║\n";
  cout << "╚══════════════════════════════════════════╝\n";
  cout << "  Select module: ";
}

int main() {
  ThreatDictionary threatDict;
  InspectionLog inspectionLog;
  ScanningLine scanningLine;
  ConnectionCheck connectionCheck;
  TrafficSorter trafficSorter;
  FirewallMap firewallMap;
  FastPass fastPass;
  LoadBalancer loadBalancer;

  printBanner();

  int choice;
  do {
    printMenu();
    cin >> choice;

    switch (choice) {
    case 1:
      threatDict.run();
      break;
    case 2:
      inspectionLog.run();
      break;
    case 3:
      scanningLine.run();
      break;
    case 4:
      connectionCheck.run();
      break;
    case 5:
      trafficSorter.run();
      break;
    case 6:
      firewallMap.run();
      break;
    case 7:
      fastPass.run();
      break;
    case 8:
      loadBalancer.run();
      break;
    case 0:
      cout << "\n[DeepScan] Shutting down. Stay secure!\n\n";
      break;
    default:
      cout << "[-] Invalid choice. Enter 0-8.\n";
    }
  } while (choice != 0);

  return 0;
}