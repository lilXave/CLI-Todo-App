#include "TODO.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>


void add_todo(std::vector<todo> todo_){
    std::ofstream outfile("TODO.csv");
    for (unsigned i = 0;i<todo_.size();i++){
        outfile << todo_[i].titel << ";" << todo_[i].prioritaet << ";" << todo_[i].deadline << '\n';
    }
}

std::vector<todo> list_todo(){
    std::vector<todo> out;
    std::string zeile;
    std::ifstream datei("TODO.csv");
    unsigned id = 0;
    while (std::getline(datei,zeile)){
        if (zeile.empty()) continue;
        std::string::size_type n;
        std::string::size_type m;
        todo todo_out;
        std::string const i = ";";
        n = zeile.find(i);
        todo_out.titel = zeile.substr(0,n);
        m=zeile.find(i,n+1);
        todo_out.prioritaet = std::stoi(zeile.substr(n+1,m - (n+1)));
        todo_out.deadline = zeile.substr(m+1);
        todo_out.id = id;
        id++;
        out.push_back(todo_out);
    }
    return out;
}

sort_states sort_to_enum(std::string n){
    if (n=="titel") return TITEL;
    if (n=="prio") return PRIO;
    if (n=="deadline" or n=="dl") return DEADLINE;
    return UNKNOWN_sort;
}

std::vector<todo> sort_todo(std::vector<todo> liste,std::string g){
    sort_states state = sort_to_enum(g);
    switch(state){
        case PRIO:
            std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.prioritaet > b.prioritaet;
                            });
            break;
        case TITEL:
            std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.titel < b.titel;
                            });
            break;
        case DEADLINE:
            std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.deadline < b.deadline;
                            });
            break;
        case UNKNOWN_sort:
            std::cout << "Invalides Sortformat.";
            break;
    }
    return liste;
}

void del_todo(std::vector<todo> liste,unsigned loeschen){
    if (liste.size()<=loeschen){
        std::cout << "Ungültige ID.";
        return;
    }
    std::string titel = liste[loeschen].titel;
    liste.erase(liste.begin()+loeschen);
    std::cout << titel << " erfolgreich abgeschlossen.";
    add_todo(liste);
}

states state_to_enum(std::string n){
    if  (n == "add") return ADD;
    if (n=="list") return LIST;
    if (n=="done") return DONE;
    return UNKNOWN_state;
}
