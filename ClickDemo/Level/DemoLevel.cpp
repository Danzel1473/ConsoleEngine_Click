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

	ResetGrid();
}

void DemoLevel::Draw()
{
	// PathFind ��尡 �ƴ϶�� ���� �׸���
	if(!pathFind)
		Level::Draw();

	// PathFind ����� ��� �׸���
	else
	{
		for (int y = 0; y < grid.size(); ++y)
		{
			for (int x = 0; x < grid[0].size(); ++x)
			{
				// ��ֹ�.
				if (grid[y][x] == 1)
				{
					Engine::Get().Draw(Vector2(x, y), "1");
				}

				// ���.
				else if (grid[y][x] == 2)
				{
					Engine::Get().Draw(Vector2(x, y), "*");
				}

				// �� ����.
				else if (grid[y][x] == 0)
				{
					Engine::Get().Draw(Vector2(x, y), "0");
				}
			}
			Engine::Get().Draw(Vector2(grid[0].size(), y), "\n");
		}
	}
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
			pathFind = !pathFind;

			if(!pathFind)
				ResetGrid();
		}
		else
		{
			OutputDebugStringA("��� ��ã��!\n");
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

	for (int i = 0; i <= Engine::Get().ScreenSize().y; ++i)
	{
		for (int j = 0; j <= Engine::Get().ScreenSize().x; ++j)
		{
			grid[i][j] = 0;
		}
	}
}