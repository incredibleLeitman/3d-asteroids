#include "ModelManager.h"
#include "TextureManager.h"

// Bly7 OBJ-Loader https://github.com/Bly7/OBJ-Loader
#include "OBJ_Loader.h"

#include <string>
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

ModelManager* ModelManager::m_inst(0);

ModelManager* ModelManager::Inst() {
    if (!m_inst)
        m_inst = new ModelManager();

    return m_inst;
}

ModelManager::ModelManager() {
}

ModelManager::~ModelManager() {
    unloadAllModels();
    m_inst = 0;
}

bool ModelManager::loadModel(const char* filename, const unsigned int modelId, int models) {
    objl::Loader m_loader;
    if (m_loader.LoadFile(filename) == false) {
        fprintf(stderr, "error loading model: %s\n", filename);
        return false;
    }

    //if this model id is in use, unload the current model
    if (m_models.find(modelId) != m_models.end()) {
        // TODO: delete model
        //glDeleteTextures(1, &(m_texID[texID]));
    }

    for (int i = 0; i < models; ++i)
    {
        fprintf(stderr, "loading mesh: %d for modelId %d\n", i, modelId + i);
        m_models[modelId + i] = m_loader.LoadedMeshes[i];
    }
    return true;
}

bool ModelManager::unloadModel (const unsigned int modelId) {
    bool result(true);
    //if this texture ID mapped, unload it's texture, and remove it from the map
    if (m_models.find(modelId) != m_models.end()) {
        // todo delete
        //glDeleteTextures(1, &(m_texID[texID]));
        m_models.erase(modelId);
    }
    //otherwise, unload failed
    else {
        result = false;
    }
    return result;
}

void ModelManager::unloadAllModels() {
    //start at the begginning of the texture map
    std::map<unsigned int, Mesh>::iterator i = m_models.begin();

    //Unload the textures untill the end of the texture map is found
    while (i != m_models.end())
        unloadModel(i->first);

    //clear the texture map
    m_models.clear();
}

Mesh ModelManager::getModel(int modelId)
{
    return m_models[modelId];
}

void ModelManager::drawMesh(int modelId, int x) {

    glPushMatrix();
    glTranslatef(x, 0, 0);

    glEnable(GL_TEXTURE_2D);

    // TODO: move to Renderer
    const GLuint PORCELAIN_IMG_ID = 7;
    TextureManager::Inst()->bindTexture(PORCELAIN_IMG_ID);

    //glDisable(GL_LIGHTING);
    //glColor3f(155, 0, 0);

    glBegin(GL_TRIANGLES);
    for (auto& vertex : m_models[modelId].Vertices)
    {
        glTexCoord2f(vertex.TextureCoordinate.X, vertex.TextureCoordinate.Y);
        glVertex3f(vertex.Position.X, vertex.Position.Y, vertex.Position.Z);
    }
    glEnd();

    glPopMatrix();
}