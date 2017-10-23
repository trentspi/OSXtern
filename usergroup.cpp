// Challenge 1: User Group Reporting

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <stdlib.h>


class UserGroup {
  std::map <std::string, std::list<std::string> > user_list;
  public: 
    void addUser (std::string user, std::string group);
    void printUsers();
};

void UserGroup::addUser(std::string user, std::string group) {
    user_list[group].push_back(user);
    user_list[group].sort();
}

void UserGroup::printUsers() {
  typedef std::map<std::string, std::list<std::string> >::const_iterator MapIterator; // used for iterating over hash map
  for (MapIterator pos = user_list.begin(); pos != user_list.end(); ++pos) {
    std::cout << std::endl;
    std::cout << pos->first;
    typedef std::list<std::string>::const_iterator ListIterator; // used for iterating lists inside the hash map
    for(ListIterator listpos = pos->second.begin(); listpos != pos->second.end(); ++listpos) {
      std::cout << "," << *listpos;
    }
  }
}

int main(int argv, char* argc[]) {
  UserGroup * u = new UserGroup();
  std::string line, user, group;
  int pos;
  while(std::getline(std::cin, line)){
    if (line != "\n"){
      pos = line.find(' ');
      user = line.substr(0, pos);
      group = line.substr(pos+1);
      u->addUser(user, group);
    }
  }

  u->printUsers();
  delete u;
}

