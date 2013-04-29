#ifndef __subject_h
#define __subject_h

#include <iostream>
#include <string>

namespace lpoo {
  
  class Subject {
    public:
      Subject(std::string id_out, std::string nm) : id(id_out), name(nm) {};
      ~Subject() {};

      void Print() const {
        std::cout << id << ' ' << name << std::endl;
      }

      std::string id, name;
  };

};

#endif
