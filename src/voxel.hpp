#pragma once

#include "math.hpp"

class Voxel {
    public:
        Voxel(vec3 position, vec3 rotation, int texture_select_index);
        mat4 getModelMatrix();
        int getTextureSelectionIndex();

    private:
        vec3 position;
        vec3 rotation;
        int texture_select_index;

};