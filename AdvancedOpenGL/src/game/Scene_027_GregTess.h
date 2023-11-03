//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_027_GregTess_H
#define Scene_027_GregTess_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class Scene_027_GregTess : public Scene {
public:
    Scene_027_GregTess();
    ~Scene_027_GregTess();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    CubeMesh* cubeMesh;

    Matrix4 projection;
    Shader shader;

    vector<CubeObject> cubes;
    float newXPosition { 0 };

    int texNoiseTexture;
    int texNoiseTexture2;
    int texNoiseTexture3;
    int texNoiseTexture4;


    float gameTime = 0;

};


#endif //Scene_027_GregTess
