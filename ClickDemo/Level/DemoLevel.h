#pragma once

#include "Level/Level.h"
#include "Algorithm/AStar.h"

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	~DemoLevel();

	void AstarStart();
	virtual void Update(float deltaTime);

private:
	AStar astar;
	Actor* startActor;
	Actor* playerActor;
	std::vector<Node*> path;
	std::vector<std::vector<int>> grid;
};