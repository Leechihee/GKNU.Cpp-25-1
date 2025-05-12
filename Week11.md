# 마우스로 사각형 움직이기
```cpp
#include "raylib.h"

int a = 0, b = 0;

int main()
{
	InitWindow(640, 480, "GKNU");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		Vector2 p = GetMousePosition();
		b = p.x;
		a = p.y;
		BeginDrawing();
		ClearBackground(GRAY);
		DrawRectangle(b-120,a-120,240,240,BLUE);
		DrawCircle(b,a,120, GREEN);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
```
# 2d 그라데이션 무지개 삼각형
```cpp
#include "raylib.h"
#include "rlgl.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib - Rainbow Gradient Triangle");

    Vector2 v1 = { 400, 100 };
    Vector2 v2 = { 200, 500 };
    Vector2 v3 = { 600, 500 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        rlBegin(RL_TRIANGLES);

        rlColor4ub(255, 0, 0, 255);    // 빨강
        rlVertex2f(v1.x, v1.y);

        rlColor4ub(0, 255, 0, 255);    // 초록
        rlVertex2f(v2.x, v2.y);

        rlColor4ub(0, 0, 255, 255);    // 파랑
        rlVertex2f(v3.x, v3.y);

        rlEnd();

        DrawText("Rainbow Gradient Triangle (raylib)", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

```
