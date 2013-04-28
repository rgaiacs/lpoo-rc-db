#ifndef __member_h
#define __member_h

#include <string>
#include "definitions.h"

namespace lpoo {
  
  class Member {
    public:
      Member(int r, std::string n, std::string e, int xp) : ra(r),
          name(n), email(e), exp(xp) {
//        level = GetLevel(exp);
//        title = GetTitle(title);
        level = 0;
        title = "Exemplo";
      };
      ~Member() {};

      void Print() const;
    private:
      int ra;
      std::string name, email, title;
      int exp, level;
  };

};

#endif
