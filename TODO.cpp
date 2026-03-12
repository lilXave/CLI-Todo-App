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
std::vector<todo> sort_todo(std::vector<todo> liste,std::string g){
    if (g=="prio"){
        std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.prioritaet > b.prioritaet;
        });}
    else if(g=="titel"){
        std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.titel < b.titel;
        });
    }
    else if(g=="deadline"){
        std::sort(liste.begin(), liste.end(),[](const todo& a, const todo& b){
                            return a.deadline < b.deadline;
        });
    }
    else{
        std::cout << "Invalides Sortformat.";
        }
        return liste;
}


void del_todo(unsigned loeschen){
    std::vector<todo> liste = list_todo();
    if (liste.size()<loeschen){
        std::cout << "Ungültige ID.";
        return;
    }
    liste.erase(liste.begin()+loeschen);
    std::cout << liste[loeschen].titel << " erfolgreich abgeschlossen.";
    add_todo(liste);
}