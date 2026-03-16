#ifndef TODO_H
#define TODO_H
#include <string>
#include <vector>
enum states{
ADD,LIST,EDIT,DONE,UNKNOWN_state
};
enum sort_states{
    TITEL,DEADLINE,PRIO,UNKNOWN_sort
};
enum prio{
    HOCH,MITTEL,NIEDRIG, UNKNOWN_prio
};

namespace farbe {
    const std::string red     = "\033[31m";
    const std::string green   = "\033[32m";
    const std::string yellow  = "\033[33m";
    const std::string reset   = "\033[0m";
}

struct todo{
    std::string titel;
    unsigned id;
    int prioritaet;
    std::string deadline;
};

void save_todo(const std::vector<todo>& todo_);
std::vector<todo> list_todo();
void sort_todo(std::vector<todo>& liste,const std::string& g);
void del_todo(std::vector<todo>& liste,const unsigned& loeschen);
states state_to_enum(const std::string& n);
void print_list(const std::vector<todo>& todos);
prio prio_to_enum(const int& var);
void replace_todo(std::vector<todo>& todos,const todo& todo_,const unsigned& i);
bool titel_exists(const std::vector<todo>& todos, const todo& todo_);
#endif
