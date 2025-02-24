#pragma once

#include "Level/Level.h"

class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	~DemoLevel();

	void AstarStart();
	virtual void Update();

private:
	AStar astar;
	Actor* startActor;
	Actor* playerActor;
};