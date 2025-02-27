#include "FileIO.h"
#include <iostream>

std::vector<std::vector<int>> FileIO::LoadMap()
{
	std::vector<std::vector<int>> map;
	const char* fp = filePath.c_str();
	FILE* file = nullptr;
	fopen_s(&file, fp, "rt");

	if (file == nullptr)
	{
		__debugbreak();
		return map;
	}

	char buffer[1024];

	while (fgets(buffer, sizeof(buffer), file))
	{
		std::vector<int> row;
		char* context = nullptr;
		char* token = strtok_s(buffer, ",", &context);

		while (token != nullptr)
		{
			row.push_back(atoi(token));
			token = strtok_s(nullptr, ",", &context);
		}

		map.push_back(row);
	}

	fclose(file);
	return map;
}

bool FileIO::SaveMap(const std::vector<std::vector<int>>& map)
{
	FILE* file = nullptr;
	const char* fp = filePath.c_str();
	fopen_s(&file, fp, "wt");

	if (!file || map.size() < 1) 
	{
		__debugbreak();
		return false;
	}

	for (size_t i = 0; i < map.size(); ++i) 
	{
		for (size_t j = 0; j < map[i].size(); ++j) 
		{
			fprintf(file, "%d", map[i][j]);
			if (j < map[i].size() - 1) 
			{
				fprintf(file, ",");
			}
		}
		fprintf(file, "\n");
	}

	fclose(file);
	return true;
}
