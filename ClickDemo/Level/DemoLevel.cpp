#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/Node.h"

DemoLevel::DemoLevel()
{
	startActor = new Start();
	playerActor = new Player();

	AddActor(startActor);
	AddActor(playerActor);
	//AddActor(new Start());
	//AddActor(new Player());

	for (int i = 0; i < 20; ++i)
	{
		std::vector<int> row;
		for (int j = 0; j < 30; ++j)
		{
			row.emplace_back(0);
		}
		grid.emplace_back(row);
	}
}

DemoLevel::~DemoLevel()
{
	playerActor->Destroy();
	startActor->Destroy();
}

void DemoLevel::AstarStart()
{
}

void DemoLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Node* startNode = startNode = new Node(startActor->Position());
		Node* playerNode = new Node(playerActor->Position());
		
		path = astar.FindPath(startNode, playerNode, grid);
		astar.DisplayGridWithPath(grid, path);
	}
}
