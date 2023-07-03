#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    virtual void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    virtual Vector2 getScreenPos() = 0; // pure virtual function
    bool getAlive() {return alive;}
    void setAlive(bool isAlive) {alive = isAlive;}

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D running{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float rightLeft{1.f};
    float width{};
    float height{};
    Vector2 worldPosLastFrame{};
    float scale{4.0f};
    Vector2 velocity{};

private:
    bool alive{true};

};

#endif