#include "PreCompiledHeader.h"
#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(const COORD& size)
	: size(size)
{
	buffer = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (buffer == INVALID_HANDLE_VALUE)
	{
		__debugbreak();
	}

	SetConsoleScreenBufferSize(buffer, size);
	SMALL_RECT rect = { 0, 0, size.X, size.Y };
	SetConsoleWindowInfo(buffer, true, &rect);

	CONSOLE_CURSOR_INFO info{ 1, false };
	SetConsoleCursorInfo(buffer, &info);

	// 마우스 입력도 활성화.
	SetConsoleMode(buffer, ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
}

ScreenBuffer::ScreenBuffer(HANDLE console, const COORD& size)
	: size(size), buffer(console)
{
	CONSOLE_CURSOR_INFO cursorInfo{ 1, false };
	SetConsoleCursorInfo(buffer, &cursorInfo);

	CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo = {};
	GetConsoleScreenBufferInfoEx(buffer, &bufferInfo);
	bufferInfo.dwSize.X = size.X;
	bufferInfo.dwSize.Y = size.Y;
	SetConsoleScreenBufferInfoEx(buffer, &bufferInfo);

	// 마우스 입력도 활성화.
	SetConsoleMode(buffer, ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT);
}

ScreenBuffer::~ScreenBuffer()
{
	CloseHandle(buffer);
}

void ScreenBuffer::SetCursorType(CursorType cursorType)
{
	// 1. 커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	// 타입 별로 구조체 값 설정.
	switch (cursorType)
	{
	case CursorType::NoCursor:
		info.dwSize = 1;
		info.bVisible = FALSE;
		break;

	case CursorType::SolidCursor:
		info.dwSize = 100;
		info.bVisible = TRUE;
		break;

	case CursorType::NormalCursor:
		info.dwSize = 20;
		info.bVisible = TRUE;
		break;
	}

	// 2. 설정.
	SetConsoleCursorInfo(buffer, &info);
}

void ScreenBuffer::Clear()
{
	COORD position = { 0, 0 };
	DWORD writtenCount = 0;
	FillConsoleOutputCharacter(buffer, ' ', (size.X + 1) * size.Y + 1, position, &writtenCount);
}

void ScreenBuffer::Draw(CHAR_INFO* charInfo)
{
	COORD bufferPosition = { 0, 0 };
	COORD bufferSize = { size.X, size.Y };
	SMALL_RECT writeRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };

	WriteConsoleOutputA(buffer, charInfo, bufferSize, bufferPosition, &writeRegion);
}