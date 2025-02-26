#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

class FileIO
{
public:
	FileIO(std::string mapName);
	std::vector<std::vector<int>> GetMap();
	
private:
	std::string filePath;
};