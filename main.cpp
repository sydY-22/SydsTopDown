#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

//DO NOT USE COLLISION! AND RENDER!

int main()
{
    const int window_width = 384;
    const int window_height = 384;
    InitWindow(window_width, window_height, "Syd's Top-Down!");

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // intance of the Character class
    Character knight(window_width, window_height);

    // enemy variables
    Vector2 enemyPos = {window_width, window_height};
    Texture2D idle_enemy = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D run_enemy = LoadTexture("characters/goblin_run_spritesheet.png");

    // instance of the Enemy class
    Enemy goblin(enemyPos, idle_enemy, run_enemy);

    goblin.setTarget(&knight);

    // load the prop textures
    // Prop props[2]{
    //     Prop{Vector2{600.f, 350.f}, LoadTexture("TextureFantasyTopDown/TX Plant.png")},
    //     Prop{Vector2{200.f, 450.f}, LoadTexture("TextureFantasyTopDown/TX Plant.png")}
    // };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // -1.f before change
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);
        

        // draw the props
        // for(auto prop : props)
        // {
        //     prop.Render(knight.getWorldPos());
        // }

        // update character animation frames.
        knight.tick(GetFrameTime());

        // check map bounds.
        if(knight.getWorldPos().x < 0.f || 
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + window_width > map.width * mapScale ||
            knight.getWorldPos().y + window_height > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // for(auto prop : props)
        // {
        //    if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
        //    {
        //         knight.undoMovement();
        //    }
        // }

        // update enemy animation frames.
        goblin.tick(GetFrameTime());

        EndDrawing();
    }
    //UnloadTexture(knight);
    CloseWindow();
}