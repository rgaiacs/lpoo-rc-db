#ifndef __achievement_h
#define __achievement_h

#include <iostream>
#include <string>
#include "definitions.h"

namespace lpoo {
  
  class Achievement {
    public:
      Achievement(std::string id_out, std::string desc, int d) : id(id_out),
        description(desc), difficulty(d) { };
      ~Achievement() {};

      void Print() const {
        std::cout << id << ' ' 
          << c_name_difficulty[difficulty-1] << std::endl;
        std::cout << description << std::endl;
      }

      std::string id, description;
      int difficulty;
  };

};

#endif
