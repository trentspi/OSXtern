// Challenge 3: Activity Monitor


#include <iostream>
#include <map>
#include <stdlib.h>

class processMonitor {
  std::map<int, int> processMap;
  public:
    void initProcessID(int pid);
    int getProcessID();
};

void processMonitor::initProcessID(int pid) {
  processMap[pid] += 1;
}

int processMonitor::getProcessID() {
  int ret;
  typedef std::map<int, int>::const_iterator processIterator;
  for (processIterator pos = processMap.begin(); pos != processMap.end(); ++pos) {
    if (pos->second % 2 == 0) {
      ret = 0;
    }
    else if (pos->second % 2 != 0) {
      ret = pos->first;
    }
  }

  return ret;
}

int main() {
  processMonitor p;
  int line;
  while(std::cin >> line) {
    p.initProcessID(line);
  }

  int ret = p.getProcessID();
  std::cout << ret << std::endl;

}