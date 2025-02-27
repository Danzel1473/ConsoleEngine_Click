#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/Node.h"

DemoLevel::DemoLevel()
{
	originalGrid = fileIO.LoadMap();

	startActor = new Start();
	playerActor = new Player();

	AddActor(startActor);
	AddActor(playerActor);

	ResetGrid();
}

void DemoLevel::Draw()
{
	// PathFind 모드가 아니라면 액터 그리기
	if (!pathFind)
	{
		for (int y = 0; y < grid.size(); ++y)
		{
			for (int x = 0; x < grid[0].size(); ++x)
			{
				// 장애물.
				if (grid[y][x] == 1)
				{
					Engine::Get().Draw(Vector2(x, y), "1");
				}
				// 빈 공간.
				else if (grid[y][x] == 0)
				{
					Engine::Get().Draw(Vector2(x, y), " ");
				}
			}
		}
		Level::Draw();
		return;
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// 장애물.
			if (grid[y][x] == 1)
			{
				Engine::Get().Draw(Vector2(x, y), "1");
			}

			// 경로.
			else if (grid[y][x] == 2)
			{
				Engine::Get().Draw(Vector2(x, y), "*", Color::Blue);
			}

			// 빈 공간.
			else if (grid[y][x] == 0)
			{
				Engine::Get().Draw(Vector2(x, y), " ");
			}
		}
	}
}

void DemoLevel::Update(float deltaTime)
{
	Level::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_TAB))
	{
		Vector2 position = Engine::Get().MousePosition();
		if (grid[position.y][position.x] == 0)
		{
			grid[position.y][position.x] = 1;
		}
		else if (grid[position.y][position.x] == 1)
		{
			grid[position.y][position.x] = 0;
		}
		originalGrid = grid;
	}

	if (Engine::Get().GetKeyDown(VK_SHIFT))
	{
		fileIO.SaveMap(originalGrid);
	}

	if (pathFind)
	{
		// 타이머 계산
		elapsedTime += deltaTime;
		if (elapsedTime < pathFindTime) return;

		// 타이머 리셋
		elapsedTime = 0.0f;

		if (path.empty())
		{
			ResetGrid();
			pathFind = false;
			return;
		}

		grid[path[0]->Position().y][path[0]->Position().x] = 2;
		path.erase(path.begin());
	}

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Node* startNode = new Node(startActor->Position());
		Node* playerNode = new Node(playerActor->Position());
		
		path = astar.FindPath(startNode, playerNode, grid);
		if (!pathFind)
		{
			if (path.size() > 0)
			{
				pathFind = true;
				if (!pathFind)
				{
					ResetGrid();
				}
			}
			else
			{
				OutputDebugStringA("경로 못찾음!\n");
			}
		}
	}

}

void DemoLevel::ResetGrid()
{
    if (originalGrid.empty()) return;

    // 원본 맵 데이터를 grid에 복사하여 초기화
    grid = originalGrid;

    path.clear();
}
//void DemoLevel::ResetGrid()
//{
//	if (grid.size() == 0)
//	{
//		for (int i = 0; i < Engine::Get().ScreenSize().y; ++i)
//		{
//			std::vector<int> row;
//			row.reserve(Engine::Get().ScreenSize().x);
//			for (int j = 0; j <= Engine::Get().ScreenSize().x; ++j)
//			{
//				row.emplace_back(0);
//			}
//			grid.emplace_back(row);
//		}
//	}
//
//	for (int i = 0; i < Engine::Get().ScreenSize().y; ++i)
//	{
//		for (int j = 0; j < Engine::Get().ScreenSize().x; ++j)
//		{
//			grid[i][j] = 0;
//		}
//	}
//
//	path.clear();
//}