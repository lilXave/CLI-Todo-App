#include "TODO.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>

int main(int argc, char const *argv[]){
    std::string befehl = argv[0];
    std::vector<std::string> valide = {"add","list","done"};
    bool invalide = (valide.end()==(std::find(valide.begin(),valide.end(),befehl)));
    if (invalide){
        std::cout << "CLI-argument ist invalide.";
    }
    else
        if (befehl=="add"){
        //check dafür ob alle Parameter da sind
        std::string titel = argv[1];
        int prioritaet = std::stoi(argv[2]);;
        std::string deadline = argv[3];
        }
        if (befehl=="list"){
            
        }
        if (befehl=="done"){
            
        };
    }