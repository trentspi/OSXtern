// Challenge 2; NetXtern

#include <iostream>
#include <string>
#include <stdlib.h>

/*
Absoulute URL (url)
Abosulute Path (url + passed in path)
Relative Path (url with path + passed in path)
FORWARD (next node)
BACK (previous node)
*/

class BrowserHistory {
  struct node {
    std::string data;
    std::string type;
    node *prev;
    node *next;
  };
  node *top = NULL; 
    public:
      void getLastAbsoPath();
      void getLastAbsoURL();
      void goBACK();
      void goFORWARD();
      void getBrowserContext();
      void getAllRelativePaths();
      void insertNode(std::string data, std::string type);
};



void BrowserHistory::goBACK() {
  if(top->prev != NULL) {
    top=top->prev;
    getBrowserContext();
  }
}

void BrowserHistory::goFORWARD() {
  if(top->next != NULL) {
    top = top->next;
    getBrowserContext();
  }
}

void BrowserHistory::getBrowserContext() {
  node *n = top;
  if(n->type == "ABSO_PATH") {
    getLastAbsoURL();
    getLastAbsoPath();
    std::cout << std::endl;
  }
  else if (n->type == "ABSO_URL") {
    getLastAbsoURL();
    std::cout << std::endl;
  }
  else if(n->type == "REL_PATH") {
    // go back, locate all relative paths, the first occurence of abs path, the first occurence of abs url
    getLastAbsoURL();
    getLastAbsoPath();
    getAllRelativePaths();
    std::cout << std::endl;
  }
}

void BrowserHistory::getLastAbsoURL() {
  node *n = top;
  bool keepGoing = true;

  while(keepGoing) {
    if(n->type == "ABSO_URL") {
      std::cout << n->data;
      keepGoing = false;
    }
    else {
      n=n->next;
    }
  }
}

void BrowserHistory::getLastAbsoPath() {
  node *n = top;
  bool keepGoing = true;

  while(keepGoing) { 
    if(n->type == "ABSO_PATH") {
      std::cout << n->data;
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

void BrowserHistory::getAllRelativePaths() {
  //insert beginning of string with a forward slash
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

  std::cout << ret;
}

void BrowserHistory::insertNode (std::string data, std::string type) {
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


int main(int argv, char* argc[]) {
  BrowserHistory b;
  std::string line;
  std::string ABSO_URL = "ABSO_URL";
  std::string ABSO_PATH = "ABSO_PATH";
  std::string REL_PATH = "REL_PATH";

  while(std::getline(std::cin, line)) {
    if (line != "\n") {
      if(line.substr(0, 8) == "https://") {
        b.insertNode(line, ABSO_URL);
        b.getBrowserContext();
      }
      else if(line.substr(0,1) == "/") {
        b.insertNode(line, ABSO_PATH);
        b.getBrowserContext();
      }
      else if(line == "BACK") {
        b.goBACK();
      }
      else if(line == "FORWARD") {
        b.goFORWARD();
      }
      else {
        b.insertNode(line, REL_PATH);
        b.getBrowserContext();
      }
    }
  }
}