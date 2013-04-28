#include <iostream>
#include <cstdlib>
#include <fstream>
#include "interface.h"
#include <sstream>

using namespace std;

namespace lpoo {

  void Interface::Start() {
    ReadDatabase();

    StartInterface();
  }

  void Interface::ReadDatabase() {
    ReadMembers();
  }

  void Interface::ReadMembers() {
    ifstream file("database/members.db");

    string line;
    while (getline(file, line, c_separator)) {
      string ra = line, name, email;
      int exp;

      stringstream aux;

      getline(file, name, c_separator);
      getline(file, email, c_separator);
      getline(file, line);
      aux << line; aux >> exp;

      Member member(ra,name,email,exp);
      members.push_back(member);
    }
  }

  void Interface::StartInterface() {
    bool done = false;
    int option = -1;

    system("clear");
    while (!done) {
      PrintMenu();
      cin >> option;
      switch (option) {
        case 1:
          ListMembers();
          break;
        case 9:
          done = true;
          break;
        default:
          cout << "Invalid option" << endl;
          break;
      }

    }
  }

  void Interface::PrintMenu() const {
    cout  
          << c_menu_color << "                          " << endl
          << c_menu_color << "  " << c_menu_text_color 
            << " 1 - Listar membros   " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
            << " 9 - Sair             " << c_menu_color << "  " << endl
          << c_menu_color << "                          " << endl
          << c_no_color+c_red_fg << "> " << c_no_color;
  }

  void Interface::ListMembers() const {
    list<Member>::const_iterator iter, iter_end;
    iter = members.begin();
    iter_end = members.end();

    while (iter != iter_end) {
      cout << c_green_fg << endl;
      iter->Print();
      cout << endl;
      iter++;
    }
    cout << c_no_color << endl << endl;
  }

};

