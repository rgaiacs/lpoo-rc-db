#include <iostream>
#include "member.h"

using namespace std;

namespace lpoo {

  void Member::Print() const {
    cout << ra << ' ' << name << endl
         << title << endl
         << email << endl
         << "Level: " << level
           << "Exp: " << exp << endl;
  }

};
