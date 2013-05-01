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

      void WriteSubjects();

      void StartInterface();
      void PrintMenu() const;
      void PrintMenuItem(int, std::string) const;

      void ListSubjects() const;
      void ListAchievements() const;
      void ListMembers() const;
      void AddMember();
      void AddSubject();
      void AddAchievement();
      void AddMemberAchievement();

      std::list<Member>::iterator GetMemberIterFromRa(std::string);
      std::list<Member>::const_iterator GetMemberConstIterFromRa(std::string) const;
      std::list<Achievement>::iterator GetAchievementIterFromId(std::string);
      std::list<Achievement>::const_iterator GetAchievementConstIterFromId(std::string) const;
  };

};

#endif
