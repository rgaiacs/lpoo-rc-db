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
    ReadSubjects();
    ReadAchievements();
    ReadMembers();
  }

  void Interface::ReadSubjects() {
    ifstream file("database/subjects.db");

    string id, name;
    while (getline(file, id, c_separator)) {
      getline(file, name);

      Subject subject(id, name);
      subjects.push_back(subject);
    }
  }

  void Interface::ReadAchievements() {
    ifstream file("database/achievements.db");

    string id, description, line;
    int difficulty;
    stringstream aux;
    while (getline(file, id, c_separator)) {
      getline(file, description, c_separator);
      getline(file, line);

      aux << line; aux >> difficulty;
      Achievement achievement(id, description, difficulty);
      achievements.push_back(achievement);
    }
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
        case 1: ListMembers(); break;
        case 2: AddMember(); break;
        case 3: ListSubjects(); break;
        case 4: ListAchievements(); break;
        case 9: done = true; break;
        default: cout << "Invalid option" << endl; break;
      }

    }
  }

  void Interface::PrintMenu() const {
    cout  
          << c_menu_color 
            << "                                " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "                            " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "   1 - Listar membros       " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "   2 - Adicionar membro     " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "   3 - Listar assuntos      " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "   4 - Listar realizações   " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "   9 - Sair                 " << c_menu_color << "  " << endl
          << c_menu_color << "  " << c_menu_text_color 
                    << "                            " << c_menu_color << "  " << endl
          << c_menu_color 
            << "                                " << endl
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

  void Interface::ListSubjects() const {
    list<Subject>::const_iterator iter, iter_end;
    iter = subjects.begin();
    iter_end = subjects.end();

    while (iter != iter_end) {
      cout << c_blue_bg + ' ' + c_no_color + c_white_fg;
      iter->Print();
      iter++;
    }
    cout << c_no_color << endl;
  }

  void Interface::ListAchievements() const {
    list<Achievement>::const_iterator iter, iter_end;
    iter = achievements.begin();
    iter_end = achievements.end();

    while (iter != iter_end) {
      cout << c_blue_fg;
      iter->Print();
      cout << endl;
      iter++;
    }
    cout << c_no_color << endl;
  }

  void Interface::AddMember() {
    char ra[256], name[256], email[256];
    cout << c_blue_fg + "RA: " + c_no_color;
    cin >> ra;
    cin.ignore();
    cout << c_blue_fg + "Nome: " + c_no_color;
    cin.getline(name,128,'\n');
    cout << c_blue_fg + "E-mail: " + c_no_color;
    cin >> email;
    Member member(ra,name,email,0);
    members.push_back(member);

    std::ofstream file("database/members.db",std::ofstream::app);
    file << ra << c_separator << name << c_separator <<
      email << c_separator << 0 << endl;
  }

};

