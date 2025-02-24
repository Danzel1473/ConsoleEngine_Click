#pragma once

#include "Core.h"
#include "Math/Vector2.h"

// 화면 버퍼에 기록할 정보.
struct Character
{
	// 문자.
	char image;

	// 색상 정보.
	Color color;
};

// 더블 버퍼링 구현에 사용할 화면 버퍼 클래스.
class ScreenBuffer
{
	friend class Engine;

public:
	// 생성자에 크기만 전달하면, 새로운 콘솔 버퍼를 생성.
	ScreenBuffer(const COORD& size);

	// 생성자에 HANDLE을 전달하면, 표준 출력 핸들을 사용해 콘솔 버퍼 생성.
	ScreenBuffer(HANDLE console, const COORD& size);

	// 소멸자.
	~ScreenBuffer();

	// 커서 타입 설정(커서 감추기 가능) 함수.
	void SetCursorType(CursorType cursorType);

	// 버퍼 지우는 함수.
	void Clear();

	// 콘솔 버퍼에 전체 문자열 버퍼를 쓸 때 사용하는 함수.
	void Draw(CHAR_INFO* buffer);

private:
	// 콘솔 핸들.
	HANDLE buffer;

	// 콘솔 화면 크기.
	COORD size;
};