#ifndef TODO_H
#define TODO_H
#include <string>
#include <vector>
enum states{
ADD,LIST,DONE,UNKNOWN_state
};
enum sort_states{
    TITEL,DEADLINE,PRIO,UNKNOWN_sort
};

struct todo{
    std::string titel;
    unsigned id;
    int prioritaet;
    std::string deadline;
};

void add_todo(std::vector<todo> todo_);
std::vector<todo> list_todo();
std::vector<todo> sort_todo(std::vector<todo> liste,std::string g);
void del_todo(std::vector<todo> liste,unsigned loeschen);
states state_to_enum(std::string n);

#endif
