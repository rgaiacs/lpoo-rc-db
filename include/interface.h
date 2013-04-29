#ifndef __interface_h
#define __interface_h

#include <list>
#include "subject.h"
#include "achievement.h"
#include "member.h"

namespace lpoo {

  class Interface {
    public:
      Interface() {}
      ~Interface() {}

      void Start();
    private:
      std::list<Member> members;
      std::list<Achievement> achievements;
      std::list<Subject> subjects;

      void ReadDatabase();
      void ReadSubjects();
      void ReadAchievements();
      void ReadMembers();

      void StartInterface();
      void PrintMenu() const;

      void ListSubjects() const;
      void ListAchievements() const;
      void ListMembers() const;
      void AddMember();
  };

};

#endif
