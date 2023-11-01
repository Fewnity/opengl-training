//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_026_Greg_H
#define Scene_026_Greg_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class Scene_026_Greg : public Scene {
public:
    Scene_026_Greg();
    ~Scene_026_Greg();
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


#endif //Scene_007_SpinningCube_H
