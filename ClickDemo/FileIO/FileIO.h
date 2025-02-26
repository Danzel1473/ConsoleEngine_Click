#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class FileIO
{
public:
	FileIO() = default;
	FileIO(std::string mapName);
	std::vector<std::vector<int>> GetMap();
	void SetFilePath(std::string fileName);
	
private:
	std::string filePath;
};