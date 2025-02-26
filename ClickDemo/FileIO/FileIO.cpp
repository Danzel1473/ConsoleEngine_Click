#include "FileIO.h"
#include <iostream>

FileIO::FileIO(std::string fileName)
{
	SetFilePath(fileName);
}

std::vector<std::vector<int>> FileIO::GetMap()
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

	char buffer[1024]; // 한 줄을 저장할 버퍼

	while (fgets(buffer, sizeof(buffer), file)) // 한 줄씩 읽기
	{
		std::vector<int> row;
		char* context = nullptr; // strtok_s에서 사용될 context 변수
		char* token = strtok_s(buffer, ",", &context); // 첫 번째 토큰 추출

		while (token != nullptr)
		{
			row.push_back(atoi(token)); // 문자열을 정수로 변환하여 추가
			token = strtok_s(nullptr, ",", &context); // 다음 토큰 추출
		}

		map.push_back(row);
	}

	fclose(file);
	return map;
}

void FileIO::SetFilePath(std::string fileName)
{
	filePath = "../Maps/" + fileName;
}