#include <iostream>
#include <iomanip>
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

    int id, naid;
    string line, name;
    while (getline(file, line, c_separator)) {
      std::stringstream aux;
      aux << line; aux >> id;
      getline(file, name, c_separator);
      getline(file, line);
      aux.str("");
      aux.clear();
      aux << line; aux >> naid;

      Subject subject(id, name, naid);
      subjects.push_back(subject);
    }
  }

  void Interface::WriteSubjects() {
    ofstream file("database/subjects.db");

    list<Subject>::const_iterator iter, iter_end;
    iter = subjects.begin();
    iter_end = subjects.end();

    while (iter != iter_end) {
      file << iter->id << c_separator << iter->name << c_separator
        << iter->GetNextAchievementId()-1 << endl;
      iter++;
    }
  }

  void Interface::ReadAchievements() {
    ifstream file("database/achievements.db");

    string id, description, line;
    int difficulty;
    while (getline(file, id, c_separator)) {
      getline(file, description, c_separator);
      getline(file, line);

      stringstream aux;
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

      stringstream aux;

      getline(file, name, c_separator);
      getline(file, email);

      Member member(ra, name, email, achievements);
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
        case  1: ListMembers(); break;
        case  2: ListSubjects(); break;
        case  3: ListAchievements(); break;
        case 10: AddMember(); break;
        case 11: AddSubject(); break;
        case 12: AddAchievement(); break;
        case  0: done = true; break;
        default: cout << "Invalid option" << endl; break;
      }

    }
  }

  void Interface::PrintMenu() const {
    cout  << c_menu_color << setw(40) << " " << endl;
    cout << c_menu_color << "  " << c_menu_text_color 
      << setw(36) << " " << c_menu_color << "  " << endl;
    PrintMenuItem( 1, "Listar membros");
    PrintMenuItem( 2, "Listar assuntos");
    PrintMenuItem( 3, "Listar realizacoes");
    PrintMenuItem(10, "Adicionar membro");
    PrintMenuItem(11, "Adicionar assunto");
    PrintMenuItem(12, "Adicionar realizacao");
    PrintMenuItem( 0, "Sair");
    cout << c_menu_color << "  " << c_menu_text_color 
      << setw(36) << " " << c_menu_color << "  " << endl;
    cout  << c_menu_color << setw(40) << " " << endl;
    cout << c_no_color + c_red_fg << "> " << c_no_color;
  }

  void Interface::PrintMenuItem(int i, string title) const {
    cout << c_menu_color << "  " << c_menu_text_color << setw(5) << right << i 
      << " - " << setw(28) << left << title << c_menu_color << setw(2) << "  " << endl;
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
    Member member(ra,name,email,achievements);
    members.push_back(member);

    ofstream file("database/members.db",std::ofstream::app);
    file << ra << c_separator << name << c_separator <<
      email << c_separator << 0 << endl;
  }

  void Interface::AddSubject() {
    char name[64];
    cout << c_blue_fg + "Novo assunto: " + c_no_color;
    cin.ignore();
    cin.getline(name, 64);

    Subject subject(name);
    subjects.push_back(subject);

    WriteSubjects();
  }

  void Interface::AddAchievement() {
    string subject, id;
    char description[512];
    int difficulty;

    cout << c_blue_fg + "Id do assunto: " + c_no_color;
    cin >> id;

    list<Subject>::iterator iter, iter_end;
    iter = subjects.begin();
    iter_end = subjects.end();
    while (iter != iter_end) {
      if (iter->id == id) {
        subject = iter->name;
        stringstream aux;
        aux << id << setw(4) << setfill('0') << iter->GetNextAchievementId();
        aux >> id;
        iter->AdvanceAchievementId();
        break;
      }
      iter++;
    }
    if (iter == iter_end) {
      cout << "Assunto não encontrado";
      return;
    }

    cout << "Assunto " << c_black_bg + c_green_fg << subject << c_no_color << endl;
    cout << "ID " << id << endl;
    cout << "Confirma (S/N): ";
    char SN;
    cin >> SN;
    while (SN != 's' && SN != 'S' && SN != 'n' && SN != 'N') {
      cout << "S ou N, por favor: ";
      cin >> SN;
    }
    if (SN == 'n' || SN == 'N')
      return;

    cout << "Descrição: ";
    cin.ignore();
    cin.getline(description, 512);
    
    difficulty = 0;

    while (difficulty < 1 || difficulty > 4) {
      cout << "Dificuldade: " << endl;
      for (int i = 0; i < 4; i++)
        cout << "  " << i+1 << " - " << c_name_difficulty[i] << endl;
      cout << "> ";
      cin >> difficulty;
    }

    Achievement achievement(id, description, difficulty);
    achievements.push_back(achievement);

    ofstream file("database/achievements.db", std::ofstream::app);
    file << id << c_separator << description << c_separator << difficulty << endl;
    WriteSubjects();
  }

};

