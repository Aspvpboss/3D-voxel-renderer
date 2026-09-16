#include <iostream>
#include "program.hpp"

int main(){
    
    try{
        Program program(500, 500, "This is a window");
        program.loop();
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;        
    }

    return 0;
}