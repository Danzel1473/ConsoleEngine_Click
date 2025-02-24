#include "DemoLevel.h"
#include "Algorithm/Astar.h"
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
}

DemoLevel::~DemoLevel()
{
}

void DemoLevel::AstarStart()
{
}

void DemoLevel::Update()
{
	
	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		Node* startNode = startNode = new Node(startActor->Position());
		Node* playerNode = new Node(playerActor->Position());
		astar.FindPath(startNode, playerNode, );
	}

}
