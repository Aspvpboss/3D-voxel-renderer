#pragma once

#include "math.hpp"

enum TextureIndexes{
    LIGHT_TEX,
    DIRT_TEX,
};

class Voxel {
    public:
        Voxel(vec3 position, vec3 rotation, TextureIndexes texture_select_index);
        mat4 getModelMatrix();
        TextureIndexes getTextureSelectionIndex();

    private:
        vec3 position;
        vec3 rotation;
        TextureIndexes texture_select_index;

};