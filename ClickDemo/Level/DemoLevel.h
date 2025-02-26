#pragma once

#include "Level/Level.h"
#include "Algorithm/AStar.h"

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	virtual void Draw();
	virtual void Update(float deltaTime);
	void ResetGrid();

private:
	AStar astar;
	Actor* startActor;
	Actor* playerActor;
	bool pathFind = false;
	//std::vector<Node*> path;
	std::vector<std::vector<int>> grid;
};