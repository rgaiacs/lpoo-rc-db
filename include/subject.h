#ifndef __subject_h
#define __subject_h

#include <iostream>
#include <string>
#include <sstream>

namespace lpoo {
  
  class Subject {
    public:
      Subject(int id_in, std::string nm, int naid = 0) : name(nm) {
        std::stringstream aux;
        aux << id_in; aux >> id;
        if (id_in >= next_valid_id)
          next_valid_id = id_in + 1;
        next_achievement_id = naid + 1;
      };
      Subject(std::string nm) : name(nm) {
        std::stringstream aux;
        aux << next_valid_id; aux >> id;
        next_valid_id++;
        next_achievement_id = 1;
      }
      ~Subject() {};

      void Print() const {
        std::cout << id << ' ' << name << std::endl;
      }

      int GetNextAchievementId() const { return next_achievement_id; }
      void AdvanceAchievementId() { next_achievement_id++; }

      std::string id, name;
    private:
      static int next_valid_id;
      int next_achievement_id;
  };

};

#endif
