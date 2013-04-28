#ifndef __member_h
#define __member_h

#include <string>
#include "definitions.h"

namespace lpoo {
  
  class Member {
    public:
      Member(std::string  r, std::string n, std::string e, int xp) : ra(r),
          name(n), email(e), exp(xp) {
        for (level = 0; level < 8; level++) {
          if (c_levels[level] > exp)
            break;
        }
        title = c_titles[level-1];
      };
      ~Member() {};

      void Print() const;
    private:
      std::string ra, name, email, title;
      int exp, level;

  };

};

#endif
