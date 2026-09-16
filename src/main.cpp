#include <iostream>
#include "program.hpp"

int main(){
    
    try{
        Program program(500, 500, "This is a window");
        program.loop();
    } catch(std::exception(&e)){
        std::cout << e.what() << std::endl;
    }

    return 0;
}