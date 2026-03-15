#include "TODO.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]){
    if (argc == 1){
        std::cout << "Es wurden keine CLI-Args eingegeben!" << '\n';
        return 1;}
    std::string befehl = argv[1];

    states state = state_to_enum(befehl);
    std::vector<todo> todos = list_todo();
    switch(state){
        case ADD:
        {
            if (argc != 5)
            {
                std::cout << "Ungueltige anzahl an CLI"<< '\n';
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
                    save_todo(todos);
                    std::cout << todo_.titel << " Zu TODO's hinzugefuegt."<< '\n';
                }else{
                    std::cout << "Titel ist bereits vergeben."<< '\n';
                }
            }
            break;
        }
        case LIST:
            if (argc != 2 && argc != 4)
            {
                std::cout << "Ungueltige anzahl an CLI"<< '\n';
            }else{
                if (argc==2){
                    int i = 0;
                    print_list(todos);
                }
                else if (argc == 4){
                    std::string c = argv[2];
                    if (c!="--sort"){
                        std::cout << "list parameter ist invalide." << '\n';
                    }
                    std::string sort_by = argv[3];
                    todos = sort_todo(todos,sort_by);
                    print_list(todos);
                    save_todo(todos);
                }
                else{
                    std::cout << "Invalider input."<< '\n';
                    return 1;
                }}
            break;
        case EDIT:
                {unsigned edit = std::stoul(argv[2]);
                todo todo_;
                todo_.titel = argv[3];
                todo_.prioritaet = std::stoi(argv[4]);
                todo_.deadline = argv[5];
                unsigned i = 0;
                while (todo_.titel != todos[i].titel){
                    i++;
                    if (todo_.titel == todos[edit].titel){
                        continue;
                    }
                    if (i>=todos.size()){
                        break;
                    }
                }
                if (i>=todos.size()){
                    todos = replace_todo(todos,todo_, edit);
                    save_todo(todos);
                    std::cout << todo_.titel << " erfolgreich geaendert." << '\n';
                }else{
                    std::cout << "Titel ist bereits vergeben."<< '\n';
                }
            }
            break;

        case DONE:
            if (argc != 3){
                std::cout << "Ungueltige anzahl an CLI"<< '\n';
            }
            else{
                unsigned loeschen = std::stoul(argv[2]);
                std::string titel = todos[loeschen].titel;
                todos = del_todo(todos,loeschen);
                save_todo(todos);
                if (loeschen >= todos.size() || todos[loeschen].titel != titel){
                    std::cout << titel << " erfolgreich abgeschlossen."<< '\n';
                }
                else{
                    std::cout << "Fehler beim Abschluss von " << titel<< '\n';
                }
                }
            break;
        case UNKNOWN_state:
            std::cout << "CLI-STATE-Argument ist invalide."<< '\n';
            break;
    }
}
