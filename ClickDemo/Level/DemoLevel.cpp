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
	ResetGrid();
}

DemoLevel::~DemoLevel()
{
	//playerActor->Destroy();
	//startActor->Destroy();
}

void DemoLevel::Draw()
{
	Level::Draw();

}

void DemoLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Node* startNode = new Node(startActor->Position());
		Node* playerNode = new Node(playerActor->Position());
		
		std::vector<Node*> path = astar.FindPath(startNode, playerNode, grid);
		if (path.size() > 0)
		{
			astar.DisplayGridWithPath(grid, path);
			ResetGrid();
		}
		else
		{
			OutputDebugStringA("경로 못찾음!\n");
		}
	}
}

void DemoLevel::ResetGrid()
{
	if (grid.size() == 0)
	{
		for (int i = 0; i <= Engine::Get().ScreenSize().y; ++i)
		{
			std::vector<int> row;
			row.reserve(Engine::Get().ScreenSize().x);
			for (int j = 0; j <= Engine::Get().ScreenSize().x; ++j)
			{
				row.emplace_back(0);
			}
			grid.emplace_back(row);
		}
	}

	//grid.clear();
	for (int i = 0; i <= Engine::Get().ScreenSize().y; ++i)
	{
		//std::vector<int> row(Engine::Get().ScreenSize().x);
		for (int j = 0; j <= Engine::Get().ScreenSize().x; ++j)
		{
			//row.emplace_back(0);
			grid[i][j] = 0;
		}
		//grid[i] = row;
	}
}