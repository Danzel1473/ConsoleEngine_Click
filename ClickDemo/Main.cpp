#include "Engine/Engine.h"
#include "Level/DemoLevel.h"

int main()
{
	Engine engine;
	engine.LoadLevel(new DemoLevel());
	engine.Run();
}