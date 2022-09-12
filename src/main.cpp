#include "headerfiles/header.h"
#include "headerfiles/grid.h"
#include "headerfiles/entity.h"

int main() {
    // Raylib initialization
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(144);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    unsigned int spawn_amount = 1;

    Grid* grid = new Grid();
    std::vector<Entity*> entity_vector;

    // Main loop
    while (!WindowShouldClose())
    {
        // Changes the spawn amount by pressing the Arrow key up or down.
        if (IsKeyPressed(KEY_UP)) {
            spawn_amount++;
        }
        else if (IsKeyPressed(KEY_DOWN)) {
            if (spawn_amount > 1) {
                spawn_amount--;
            }
        }

        // Spawning of the Objects.
        grid->setCollisionInstructions(0);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (!(GetMousePosition().x > 1077 || GetMousePosition().y > 1077 || GetMousePosition().x < 3 || GetMousePosition().y < 3)) {
                for (int i = 0; i < spawn_amount; i++) {
                    Entity* entity = new Entity(grid, GetMousePosition());
                    entity_vector.push_back(entity);
                }
            }
        }

        // Updates the Position of every Object.
        for (int i = 0; i < entity_vector.size(); i++) {
            entity_vector[i]->move();
        }

        // Checks for collision for every Object inside a cell.
        grid->handleCollision();

        BeginDrawing();

        // Draws the Objects.
        ClearBackground(WHITE);
        for (int i = 0; i < entity_vector.size(); i++) {
            DrawCircleV(entity_vector[i]->getPosition(), 6, RED);
        }

        // Draws the background for the text.
        DrawRectangleRounded(Rectangle{ 4, 2, 470, 125}, 0.2f, 8, WHITE);
        DrawRectangleRoundedLines(Rectangle{ 4, 2, 470, 125 }, 0.2f, 8, 2, BLACK);

        // Draws the text and info variables.
        DrawText(TextFormat("Current FPS: %i", GetFPS()), 15, 5, 40, BLACK);
        DrawLineEx(Vector2{ 15, 45 }, Vector2{ 460, 45 }, 2, BLACK);
        DrawText(TextFormat("Number of Objects: %i", entity_vector.size()), 15, 50, 20, BLACK);
        DrawText(TextFormat("Number of Collision Instructions: %i", grid->getCollisionInstructions()), 15, 75, 20, BLACK);
        DrawText(TextFormat("Spawn Objects per Click: %i", spawn_amount), 15, 100, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();  // Close window and OpenGL context

    return EXIT_SUCCESS;
}
