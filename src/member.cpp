#include <iostream>
#include <fstream>
#include "member.h"

using namespace std;

namespace lpoo {

  Member::Member(string  r, string n, string e, 
      const list<Achievement> & all_achievements) : ra(r),
      name(n), email(e), exp(0) {
    string filename = "database/member_" + ra+ ".db";
    ifstream file(filename.c_str());
    string line;

    std::list<Achievement>::const_iterator iter, iter_end;
    iter_end = all_achievements.end();
    while (getline(file,line)) {
      achievements.push_back(line);
      iter = all_achievements.begin();
      while (iter != iter_end) {
        if (iter->id == line) {
          exp += c_exp_per_difficulty[iter->difficulty-1];
          break;
        }
        iter++;
      }
      if (iter == iter_end)
        throw("Achivement " + line + " not found in database");
    }

    for (level = 0; level < 8; level++) {
      if (c_levels[level] > exp)
        break;
    }
    title = c_titles[level-1];
  };

  void Member::Print() const {
    cout << ra << ' ' << name << endl
         << title << endl
         << email << endl
         << "Level: " << level << "  Exp: " << exp << endl
         << "Realizações: " << endl;
    list<string>::const_iterator iter, iter_end;
    iter = achievements.begin();
    iter_end = achievements.end();
    while (iter != iter_end) {
      cout << *iter++ << endl;
    }
  }

};
