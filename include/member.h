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
      std::string GetRa() const { return ra; }
      std::string GetName() const { return name; }
      void AddAchievement(std::list<Achievement>::const_iterator);
    private:
      std::string ra, name, email, title;
      int exp, level;
      std::list<std::string> achievements;

  };

};

#endif
