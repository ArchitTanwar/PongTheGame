#include "raylib.h"

struct Ball {
	float X, Y;
	float SpeedX, SpeedY;
	float Radius;
	void Draw()
	{
		DrawCircle((int)X, (int)Y, Radius, WHITE);
	}
};
struct Paddles {
	float X, Y;
	float Speed;
	float Width, Height;
	Color color;

	Rectangle GetRect()
	{
		return Rectangle{
			X - Width / 2, Y - Height / 2, Width, Height
		};
	}
	void Draw()
	{
		DrawRectangleRec(GetRect(),color);
	}
};
int main()
{
	InitWindow(1900, 1000, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	Ball ball;
	ball.X = GetScreenWidth() / 2.0f;
	ball.Y = GetScreenHeight() / 2.0f;
	ball.Radius = 5;
	ball.SpeedX = 350;
	ball.SpeedY = 350;

	Paddles LeftPaddle;
	LeftPaddle.X = 50;
	LeftPaddle.Y = GetScreenHeight() / 2;
	LeftPaddle.Width = 20;
	LeftPaddle.Height = 100;
	LeftPaddle.Speed = 400;
	LeftPaddle.color = BLUE;
	Paddles RightPaddle;
	RightPaddle.X = GetScreenWidth() - 50;
	RightPaddle.Y = GetScreenHeight() / 2;
	RightPaddle.Width = 20;
	RightPaddle.Height = 100;
	RightPaddle.Speed = 400;
	RightPaddle.color = GREEN;

	const char* WinnerText = nullptr;
	while(!WindowShouldClose())
	{
		ball.X += ball.SpeedX* GetFrameTime();
		ball.Y += ball.SpeedY* GetFrameTime();
		if (ball.Y < 0)
		{
			ball.Y = 0;
			ball.SpeedY *= -1;
		}
		if (ball.Y > GetScreenHeight())
		{
			ball.Y = GetScreenHeight();
			ball.SpeedY *= -1;
		}
		if (IsKeyDown(KEY_W))
		{
			LeftPaddle.Y -= LeftPaddle.Speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			LeftPaddle.Y += LeftPaddle.Speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			RightPaddle.Y -= RightPaddle.Speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			RightPaddle.Y += RightPaddle.Speed * GetFrameTime();
		}
		if (CheckCollisionCircleRec(Vector2{ ball.X, ball.Y }, ball.Radius, LeftPaddle.GetRect()))
		{
			if (ball.SpeedX < 0)
			{
				ball.SpeedX *= -1.1f;
				ball.SpeedY = (ball.Y - LeftPaddle.Y) / (LeftPaddle.Height / 2) * ball.SpeedX;
			}
			
		}
		if (CheckCollisionCircleRec(Vector2{ ball.X, ball.Y }, ball.Radius, RightPaddle.GetRect()))
		{
			if (ball.SpeedX > 0)
			{
				ball.SpeedX *= -1.1f;
				ball.SpeedY = (ball.Y - RightPaddle.Y)/(RightPaddle.Height/2)*-ball.SpeedX;
			}
		}
		if (ball.X < 0)
		{
			WinnerText = "Right Player Wins!";
		}
		if (ball.X>GetScreenWidth())
		{
			WinnerText = "Left Player Wins!";
		}
		if (WinnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.X = GetScreenWidth() / 2;
			ball.Y = GetScreenHeight() / 2;
			ball.SpeedX = 300;
			ball.SpeedY = 300;
		}
		BeginDrawing();
		ClearBackground(ORANGE);
		ball.Draw();
		LeftPaddle.Draw();
		RightPaddle.Draw();
		if (WinnerText)
		{
			int TextWidth = MeasureText(WinnerText,60);
			DrawText(WinnerText, GetScreenWidth()/2-TextWidth/2, GetScreenHeight() / 2 - 30, 60, BLACK);
		}
		
	
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}