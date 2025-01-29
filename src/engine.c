#include <raylib.h>
typedef struct Particle
{
	Vector2 pos;
	Vector2 speed;
	float size;
	float sizeSpeed;
	float time;
	float maxTime;
} Particle;
void SpawnParticle(Particle* array, int Count,
		Vector2 startPos,
		Vector2 mousePos);
int main(){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE & FLAG_WINDOW_ALWAYS_RUN & FLAG_BORDERLESS_WINDOWED_MODE);
	InitWindow(800,600,"My first raylib window! TY Raysan5!");
	int unitsInWidth = 800 / 16;
	int unitsInHeight = 600 / 9;
	SetTargetFPS(60);
	Color bgColor = {18,18,18,255};

	Vector2 pos = {0,0};
	float rad = 20;
	
	Color green = {18,255,18,255};
	Color red = {255,0,0,255};
	
	float spawnTime = 0.1f;
	float spawn = 0.0f;
	int Count = 0;
	int MaxCount = 32;
	
	Texture2D tilemapTexture = LoadTexture("resources/ground.png");
	Rectangle rect = {0,0,64,64};

	Particle *array = MemAlloc(MaxCount * sizeof(Particle));
	
	//Shader customShader = LoadShader("shaders/vertexShader","shaders/fragmentShader");
	//if(!IsShaderValid(customShader)) printf("Custom Shader is not valid!");
	Camera2D camera = {{0,0},{0,0},0,1.0f};
	while(!WindowShouldClose()){
		BeginMode2D(camera);
		if(IsKeyPressed(KEY_A))
		{
			camera.zoom += 1.0f;
		}else if(IsKeyPressed(KEY_B))
		{
			camera.zoom -= 1.0f;
			if(camera.zoom < 1){
				camera.zoom = 1;
			}
		}
		float dt = GetFrameTime();
		Vector2 mousePos = GetMousePosition();
		ClearBackground(bgColor);
		spawn+= dt;
		Vector2 tilemapPos = {0,0};

		DrawTextureRec(tilemapTexture, rect, tilemapPos, WHITE);
		if(IsMouseButtonDown(0))
		{
			Vector2 speed = {(mousePos.x - pos.x) * dt * 10,(mousePos.y - pos.y) * dt * 10};
			pos.x += speed.x;
			pos.y += speed.y;
			speed.x = - speed.x;
			speed.y = -speed.y;
			if(spawn >= spawnTime && Count < MaxCount){
				SpawnParticle(array, Count, pos, speed);
				Count++;
				spawn = 0;
			}else if(Count >= MaxCount){
				Particle* ptr = array;
				array = MemAlloc(MaxCount * 2 * sizeof(Particle));
				memcpy(array, ptr,MaxCount * sizeof(Particle));
				MaxCount *= 2;
				MemFree(ptr);
				
			}
			
		}
		DrawCircle(pos.x, pos.y, rad, red);
		for(int i = 0; i < Count; i++)
		{			
			if(array[i].size <= 0)
			{
				array[i] = array[--Count];
		       	}
			Vector2 tempPos = {array[i].pos.x + array[i].speed.x * dt, array[i].pos.y + array[i].speed.y * dt};
			array[i].pos = tempPos;
			Vector2 tempSpeed = {array[i].speed.x - dt, array[i].speed.y - dt};
			array[i].speed =tempSpeed;
			array[i].size += array[i].sizeSpeed * dt;
			array[i].sizeSpeed -= dt;
			
			DrawCircle(array[i].pos.x, array[i].pos.y, array[i].size, green);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
void SpawnParticle(Particle* array, int Count,
		Vector2 startPos,
		Vector2 startSpeed)
		{
			Particle particle = 	{
					startPos,
					startSpeed,
					10.0f,
					2.0f,
					0,
					5.0f
				} ;
			array[Count] = particle;
	
}
