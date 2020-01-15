#pragma once
#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <map>

#include "GeometryPrimitives.h"

//Usage
//------------------------------------------------------------
//To load a texture, simply call the LoadTexture function:
//ModelManager::Inst()->LoadTexture("img\\bg.jpg", BACKGROUND_IMAGE_ID);
//This also binds the loaded texture as the current texture, so after calling it you may make any calls to glTexParameter you may need to specify the properties of the texture.

//When you are rendering, just call the ModelManager's BindImage function instead of glBindImage:
//ModelManager::Inst()->BindTexture(BACKGROUND_IMAGE_ID);
class ModelManager {
public:
    static ModelManager* Inst();

    virtual ~ModelManager();

    //load a model an save it in map
    bool loadModel(const char* filename,    //where to load the file from
        const unsigned int texId,           //arbitrary id you will reference the model by
        int models = 1);                    //amount of models to extract

    //free the memory for a model
    bool unloadModel(const unsigned int texId);

    //set the current model
    //bool bindModel(const unsigned int texID);

    //free all texture memory
    void unloadAllModels();

    // returns model for given id
    Mesh getModel(int modelId);

    // directly draws the given mesh
    void drawMesh(int modelId, int x);

protected:
    ModelManager();

    ModelManager(const ModelManager& tm);

    ModelManager& operator=(const ModelManager& tm);

    static ModelManager* m_inst;
    std::map<unsigned int, Mesh> m_models;
};

#endif // MODEL_MANAGER_H