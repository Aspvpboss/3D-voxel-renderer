#include <iostream>
#include "program.hpp"

int main(){
    
    try{
        Program program(900, 900, "This is a window");
        program.loop();
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;        
    }

    return 0;
}

