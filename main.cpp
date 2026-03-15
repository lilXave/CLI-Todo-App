#include "TODO.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]){
    std::string befehl = argv[1];
    states state = state_to_enum(befehl);
    std::vector<todo> todos = list_todo();
    switch(state){
        case ADD:
        {
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
            }
            break;
        }
        case LIST:
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
                        std::cout << "list parameter ist invalide." << '\n';
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
            break;
        case DONE:
            if (argc != 3){
                std::cout << "Ungueltige anzahl an CLI";
            }else{
                unsigned loeschen = std::stoul(argv[2]);
                del_todo(todos,loeschen);
                }
            break;

        case UNKNOWN_state:
            std::cout << "CLI-STATE-Argument ist invalide.";
            break;
            }
};
