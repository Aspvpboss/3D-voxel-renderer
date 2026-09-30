#include "voxel.hpp"

Voxel::Voxel(vec3 position, vec3 rotation, TextureIndexes texture_select_index){
    Voxel::position = position;
    Voxel::rotation = rotation;
    Voxel::texture_select_index = texture_select_index;
}

mat4 Voxel::getModelMatrix(){
    return math::translate(mat4(1.0f), position) * math::rotationXYZ(mat4(1.0f), rotation);
}

TextureIndexes Voxel::getTextureSelectionIndex(){
    return Voxel::texture_select_index;
}