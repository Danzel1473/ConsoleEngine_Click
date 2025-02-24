#pragma once

#include <vector>

// A* 길찾기 기능을 처리하는 클래스.
class Node;
class AStar
{
private:

	// 방향 처리를 위한 구조체.
	struct Direction
	{
		// 위치.
		int x;
		int y;

		// 이동 비용
		float cost;
	};

public:
	AStar();
	~AStar();

	// 경로 검색 함수.
	std::vector<Node*> FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid);

	// 그리드 출력 함수.
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

private:
	// 탐색을 마친 후 최적 경로를 반환하는 함수.
	// 목표 노드에서 부모 노드를 참조해 시작노드까지 역추적하면 경로를 구할 수 있다.
	std::vector<Node*> ConstructPath(Node* goalNode);

	// hCost 계산 함수.
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	// 탐색하려는 위치가 그리드 범위 안에 있는지 확인하는 함수.
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	// 방문하려는 위치가 이미 방문했던 노드인지 확인하는 함수.
	bool HasVisited(int x, int y, float gCost);

	// 탐색하려는 노드가 목표 노드인지 확인하는 함수.
	bool IsDestination(Node* node);

private:

	// 열린 리스트.
	std::vector<Node*> openList;

	// 닫힌 리스트.
	std::vector<Node*> closedList;

	// 시작 노드.
	Node* startNode;

	// 목표 노드.
	Node* goalNode;
};