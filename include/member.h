#ifndef __member_h
#define __member_h

#include <string>
#include <list>
#include "definitions.h"
#include "achievement.h"

namespace lpoo {
  
  class Member {
    public:
      Member(std::string, std::string, std::string, 
          const std::list<Achievement> &);
      ~Member() {};

      void Print() const;
    private:
      std::string ra, name, email, title;
      int exp, level;
      std::list<std::string> achievements;

  };

};

#endif
