#include "pause.h"

void draw_pause_screen(const int selectedWidth, const int selectedHeight)
{
    int button = GetGamepadButtonPressed();
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Paused", selectedWidth / 2 - MeasureText("Paused", 20) / 2, selectedHeight / 2 - 100, 20, WHITE);
    DrawText("1: unpause", 200, selectedHeight / 2 + 10, 20, WHITE);
    DrawText("2: toggle shader", 200, selectedHeight / 2 + 30, 20, WHITE);
    DrawText("3: toggle device scale", 200, selectedHeight / 2 + 50, 20, WHITE);
    DrawText("4: toggle debug", 200, selectedHeight / 2 + 70, 20, WHITE);
    DrawText(TextFormat("Button %d", button), 200, selectedHeight / 2 + 100, 20, WHITE);
    EndDrawing();
}
