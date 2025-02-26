#pragma once

#include "Level/Level.h"
#include "Algorithm/AStar.h"
#include "FileIO/FileIO.h"

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	virtual ~DemoLevel()
	{
	}

	virtual void Draw();
	virtual void Update(float deltaTime);
	void ResetGrid();

private:
	float elapsedTime = 0.0f;
	float pathFindTime = 0.2f;
	bool pathFind = false;
	FileIO fileIO;
	AStar astar;
	Actor* startActor;
	Actor* playerActor;

	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> originalGrid;
	std::vector<Node*> path;
	
};