/*
 * implementacion de:
 * movimiento
 * colision simple
 * cofre que se abre y cierra
*/
#include "raylib.h"
#include "iostream"
struct Cofre{
    Cofre(){
        position={0.0f,0.0f};
        box={ this->position.x,this->position.y , 50, 50 };
        isOpened=false;
    }
    Rectangle box;
    bool isOpened;
    Vector2 position;
    void setPosition(char direction, float newPosition){
        if(direction=='x'){
            position.x=newPosition;
            box.x=newPosition;
        }
        else if (direction=='y') {
            position.y=newPosition;
            box.y=newPosition;
        }
    }
};
struct Wizard{
    Wizard(){
        speed=200.0f;
        position={0.0f,0.0f};
        image=LoadImage("resources/wizard2.png");
        texture=LoadTextureFromImage(image);
        box={ this->position.x,this->position.y , 50, 50 };
    }
    ~Wizard(){
        UnloadImage(image);
        UnloadTexture(texture);
    }
    Rectangle box;

    Vector2 position;
    float speed;

    Image image;
    Texture2D texture;
    void setPosition(char direction, float newPosition){
        if(direction=='x'){
            position.x=newPosition;
            box.x=newPosition;
        }
        else if (direction=='y') {
            position.y=newPosition;
            box.y=newPosition;
        }
    }
};

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //game config
    Wizard wizard;
    Cofre cofre;
    cofre.setPosition('x', (float)screenWidth/2);
    cofre.setPosition('y', (float)screenHeight/2);
    auto mouse = GetMousePosition();
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float dt = GetFrameTime();
        Vector2 velocity = { 0.0f, 0.0f };

        if (IsKeyDown(KEY_D))
            velocity.x += wizard.speed;

        if (IsKeyDown(KEY_A))
            velocity.x -= wizard.speed;

        if (IsKeyDown(KEY_S))
            velocity.y += wizard.speed;

        if (IsKeyDown(KEY_W))
            velocity.y -= wizard.speed;



        //----------------------------------------------------------------------------------
        //Checking Zone
        //----------------------------------------
        //Collision
        //Se realizan los chequeos de x e y separadamente para permitir que el
        //wizard pueda "deslizarse" sobre el otro rectangle.
        //Check y movement en X
        wizard.setPosition('x', wizard.position.x + velocity.x * dt);
        if (CheckCollisionRecs(wizard.box, cofre.box))
        {
            wizard.setPosition('x', wizard.position.x - velocity.x * dt);
        }
        //Check y movement en Y
        wizard.setPosition('y', wizard.position.y + velocity.y * dt);
        if (CheckCollisionRecs(wizard.box, cofre.box))
        {
            wizard.setPosition('y', wizard.position.y - velocity.y * dt);
        }
        //----------------------------------------
        mouse = GetMousePosition();
        //Mouse Detection
        if(CheckCollisionPointRec(mouse, cofre.box)){
            switch (GetGestureDetected()){
            case GESTURE_TAP:
                std::cout<<"TAP"<<std::endl;
                cofre.isOpened=cofre.isOpened ? false: true;
                break;
            default:
                break;
            }
        }

        //----------------------------------------------------------------------------------
        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTextureV(wizard.texture,wizard.position, WHITE);
        DrawRectangle(cofre.position.x,cofre.position.y,50,50,RED);

        //ui
        if (cofre.isOpened) {
            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);
            DrawText("Coso abierto:", 20, 20, 10, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}