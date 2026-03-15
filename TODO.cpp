#include "TODO.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>


void save_todo(const std::vector<todo>& todo_){
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

sort_states sort_to_enum(const std::string& n){
    if (n=="titel") return TITEL;
    if (n=="prio") return PRIO;
    if (n=="deadline" or n=="dl") return DEADLINE;
    return UNKNOWN_sort;
}

std::vector<todo> sort_todo(std::vector<todo>& liste,const std::string& g){
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

std::vector<todo> del_todo(std::vector<todo>& liste,const unsigned& loeschen){
    if (liste.size()<=loeschen){
        std::cout << "Ungueltige ID."<<'\n';
        return liste;
    }
    liste.erase(liste.begin()+loeschen);
    return liste;
}

states state_to_enum(const std::string& n){
    if  (n == "add") return ADD;
    if (n=="list") return LIST;
    if (n=="edit") return EDIT;
    if (n=="done") return DONE;
    return UNKNOWN_state;
}

prio prio_to_enum(const int& var){
    if (var==3) return HOCH;
    if (var==2) return MITTEL;
    if (var==1) return NIEDRIG;
    return UNKNOWN_prio;
}

void print_list(const std::vector<todo>& todos){
    unsigned i = 0;
    while (i<todos.size()){
        prio g = prio_to_enum(todos[i].prioritaet);
        std::string farbe_code;
        switch(g) {
            case HOCH:    farbe_code = farbe::red; break;
            case MITTEL:  farbe_code = farbe::yellow; break;
            case NIEDRIG: farbe_code = farbe::green; break;
            default:      farbe_code = ""; break;
        }
        std::cout << farbe_code << todos[i].titel << ";" << todos[i].prioritaet << ";" << todos[i].deadline << ";" << i << farbe::reset << '\n';
        i++;
    }
}

std::vector<todo> replace_todo(std::vector<todo>& todos,const todo& todo_,const unsigned& i){
    todos = del_todo(todos, i);
    todos.insert(todos.begin()+i,todo_);
    return todos;
}

