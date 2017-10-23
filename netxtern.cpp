// Challenge 2; NetXtern

#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>

class NetXternHistory {
  struct node {
    std::string data;
    std::string type;
    node *prev;
    node *next;
  };
  node *top = NULL; 
  std::string browserContext;
  public:
    void getLastAbsoPath();
    void getLastAbsoURL();
    void goBACK();
    void goFORWARD();
    void getBrowserContext();
    void getAllRelativePaths();
    void insertNode(std::string data, std::string type);
    void deleteNodes();
};

void NetXternHistory::goBACK() {
  if(top->next != NULL) {
    top=top->next;
    getBrowserContext();
  }
}

void NetXternHistory::goFORWARD() {
  if(top->prev != NULL) {
    top = top->prev;
    getBrowserContext();    
  }
}

void NetXternHistory::getBrowserContext() {
  node *n = top;
  if(n->type == "ABSO_PATH") {
    getLastAbsoURL();
    getLastAbsoPath();
  }
  else if (n->type == "ABSO_URL") {
    getLastAbsoURL();
  }
  else if(n->type == "REL_PATH") {
    getLastAbsoURL();
    getLastAbsoPath();
    getAllRelativePaths();
  }
  std::cout << browserContext << std::endl;
  browserContext.clear();
}

void NetXternHistory::getLastAbsoURL() {
  node *n = top;
  bool keepGoing = true;

  while(keepGoing) {
    if(n->type == "ABSO_URL") {
      browserContext.append(n->data);
      keepGoing = false;
    }
    else {
      n=n->next;
    }
  }
}

void NetXternHistory::getLastAbsoPath() {
  node *n = top;
  bool keepGoing = true;

  while(keepGoing) { 
    if(n->type == "ABSO_PATH") {
      browserContext.append(n->data);
      keepGoing = false;
    }
    else if(n->type == "ABSO_URL"){
      keepGoing = false;
    }
    else {
      n=n->next;
    }
  }
}

void NetXternHistory::getAllRelativePaths() {
  node *n = top;
  bool keepGoing = true;
  std::string ret;

  while(keepGoing) {
    if(n->type == "REL_PATH") {
      ret.insert(0, "/" + n->data);
      if(n->next == NULL) {
        keepGoing = false;
      }
      else {
        n=n->next;
      }
    }
    else if(n->next != NULL) {
      keepGoing = false;
    }
    else {
      n=n->next;
    }
  }
  browserContext.append(ret);
}


void NetXternHistory::insertNode (std::string data, std::string type) {
  if(top == NULL) {
    top = new node;
    top->data = data;
    top->type = type;
    top->next = NULL;
    top->prev = NULL;
  }
  else {
    node *n = new node;
    n->data = data;
    n->type = type;
    n->next = top;
    n->prev = NULL;
    top->prev = n;
    top = n;   
  }
}

void NetXternHistory::deleteNodes() {
  node *n = top;
  node *next;

  while(n != NULL) {
    next=n->next;
    free(n);
    n = next;
  }

  top = NULL;
}

int main(int argv, char* argc[]) {
  NetXternHistory * b = new NetXternHistory;
  std::string line;
  std::string ABSO_URL = "ABSO_URL";
  std::string ABSO_PATH = "ABSO_PATH";
  std::string REL_PATH = "REL_PATH";

  while(std::getline(std::cin, line)) {
    if (line != "\n") {
      if(line.substr(0, 8) == "https://") {
        b->insertNode(line, ABSO_URL);
        b->getBrowserContext();
      }
      else if(line == "." || line == "..") {
        throw std::invalid_argument("ERROR: found dot segments in input");
      }
      else if(line.substr(0,3) == "../" || line.substr(0, 2) == "./") {
        throw std::invalid_argument("ERROR: found dot segments in input");
      }
      else if(line.substr(0,3) == "/./") {
        line.erase(0,3);  
        line.insert(0, "/");
        b->insertNode(line, ABSO_PATH);
        b->getBrowserContext();
      }
      else if(line.substr(0,2) == "/.") {
        line.erase(0,2);
        line.insert(0, "/");
        b->insertNode(line, ABSO_PATH);
        b->getBrowserContext();
      }
      else if(line.substr(0,1) == "/") {
        b->insertNode(line, ABSO_PATH);
        b->getBrowserContext();
      }
      else if(line == "BACK") {
        b->goBACK();
      }
      else if(line == "FORWARD") {
        b->goFORWARD();
      }
      else {
        b->insertNode(line, REL_PATH);
        b->getBrowserContext();
      }
    }
  }
  b->deleteNodes();
  delete b;
}