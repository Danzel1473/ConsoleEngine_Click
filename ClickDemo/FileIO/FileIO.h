#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class FileIO
{
public:
	FileIO() = default;

	std::vector<std::vector<int>> LoadMap();
	bool SaveMap(const std::vector<std::vector<int>>& map);
	
private:
	std::string filePath = "../Maps/Map.txt";
};