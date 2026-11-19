#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>
#include <entt/entt.hpp>
struct Position{
    int x,y;
};
struct Renderable{
    int r,g,b;
};
void RenderSystem(entt::registry& registry){
    auto view = registry.view<Position, Renderable>();

    for (auto entity : view) {
        const auto& pos = view.get<Position>(entity);
        const auto& render = view.get<Renderable>(entity);
        DrawRectangle(pos.x,pos.y,50,50,Color(render.r,render.g,render.b,255));
    }
}
class FactoryCubes
{
public:
    FactoryCubes(entt::registry& r):registry(r) {}
    void makeCube(int positionx,int positiony,int r,int g,int b){
        auto cubeFactory = registry.create();
        registry.emplace<Position>(cubeFactory, positionx, positiony);
        registry.emplace<Renderable>(cubeFactory, r, g, b);
    }
private:
    entt::registry& registry;
};

int main()
{
    entt::registry registry;
    FactoryCubes factory(registry);

    InitWindow(800, 600, "raygui - controls test suite");
    SetTargetFPS(60);

    bool showMessageBox = false;

    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (GuiButton({ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

        if (showMessageBox) {
            std::cout<<"Eso tilin"<<std::endl;
            factory.makeCube(100,100,255,0,0);
            showMessageBox=false;
        }
        RenderSystem(registry);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}