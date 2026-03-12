#include "TODO.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]){
    std::string befehl = argv[1];
    std::vector<std::string> valide = {"add","list","done"};
    bool invalide = (valide.end()==(std::find(valide.begin(),valide.end(),befehl)));
    std::vector<todo> todos = list_todo();
    if (invalide){
        std::cout << "CLI-argument ist invalide.";
    }
    else{
        if (befehl=="add"){
            if (argc != 5)
            {
                std::cout << "Ungueltige anzahl an CLI";
            }else{
                todo todo_;
                todo_.titel = argv[2];
                todo_.prioritaet = std::stoi(argv[3]);
                todo_.deadline = argv[4];
                unsigned i = 0;
                while (todo_.titel != todos[i].titel){
                    i++;
                    if (i>=todos.size()){
                        break;
                    }
                }
                if (i>=todos.size()){
                    todos.push_back(todo_);
                    add_todo(todos);
                    std::cout << todo_.titel << " Zu TODO's hinzugefuegt.";
                }else{
                    std::cout << "Titel ist bereits vergeben.";
                }
            }}
        else if (befehl=="list"){
            if (argc != 2 && argc != 4)
            {
                std::cout << "Ungueltige anzahl an CLI";
            }else{
                std::vector<todo> liste = list_todo();
                if (argc==2){
                    int i = 0;
                    while (i<liste.size()){
                        std::cout << liste[i].titel <<";"<< liste[i].prioritaet << ";" << liste[i].deadline <<";"<<i<<'\n';
                        i++;
                    }
                }
                else if (argc == 4){
                    std::string c = argv[2];
                    if (c!="--sort"){
                        std::cout << "list parameter ist invalide.";
                    }
                    std::string sort_by = argv[3];
                    liste = sort_todo(liste,sort_by);
                    for (int i = 0;i<liste.size();i++){
                        std::cout << liste[i].titel <<";"<< liste[i].prioritaet << ";" << liste[i].deadline <<";"<<i<<'\n';
                    }
                    add_todo(liste);
                }
                else{
                    std::cout << "Invalider input.";
                    return 1;
                }}
            }

        else if (befehl=="done"){
            if (argc != 3){
                std::cout << "Ungueltige anzahl an CLI";
            }else{
                unsigned loeschen = std::stoul(argv[2]);
                del_todo(loeschen);
                }
        }
}}