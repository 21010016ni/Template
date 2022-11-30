#pragma once

class Game
{
public:
	enum class Message
	{
		none,
		quit,
	};

	static void preset();
	static Message update();
	static void draw();
};

