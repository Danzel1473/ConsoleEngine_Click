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

	char buffer[1024]; // �� ���� ������ ����

	while (fgets(buffer, sizeof(buffer), file)) // �� �پ� �б�
	{
		std::vector<int> row;
		char* context = nullptr; // strtok_s���� ���� context ����
		char* token = strtok_s(buffer, ",", &context); // ù ��° ��ū ����

		while (token != nullptr)
		{
			row.push_back(atoi(token)); // ���ڿ��� ������ ��ȯ�Ͽ� �߰�
			token = strtok_s(nullptr, ",", &context); // ���� ��ū ����
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