#include <iostream>
#include "program.hpp"

int main(){
   
    std::vector<std::string> texture_paths = {"assets/textures/sun.png", "assets/textures/dirt.jpg"};
    std::vector<Voxel> voxels;

    for (int z = 0; z < 16; ++z) {
        int y = z;
        for (int x = 0; x < 16; ++x) {
            
            // Multiply by 2.0f because the voxel vertices span from -1.0 to 1.0 (size of 2)
            vec3 position(x * 2.0f, y * 2.0f, z * -2.0f); 
            
            
            // Create the voxel and push it to the vector
            voxels.push_back(Voxel(position, vec3(0), DIRT_TEX));
        }
    }

    try{
        Program program(900, 900, "This is a window", texture_paths, voxels);
        program.loop();
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;        
    }

    return 0;
}

