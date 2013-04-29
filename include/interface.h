#ifndef __interface_h
#define __interface_h

#include <list>
#include "member.h"

namespace lpoo {

  class Interface {
    public:
      Interface() {}
      ~Interface() {}

      void Start();
    private:
      std::list<Member> members;

      void ReadDatabase();
      void ReadMembers();

      void StartInterface();
      void PrintMenu() const;

      void ListMembers() const;
      void AddMember();
  };

};

#endif
