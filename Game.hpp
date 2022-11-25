#pragma once
#include "Draw.hpp"
#include <vector>

class Game
{
	struct Shape
	{
		char type;
		unsigned char mode;
		short start;
		float preset[8];
		std::vector<uint32_t> func;

		// “_Aü
		Shape(char type, unsigned char mode, unsigned short start) :type(type), mode(mode), start(start)
		{
			for (int i = 0; i < 8; ++i)
				preset[i] = 0;
		}
		// ‰~
		Shape(char type, unsigned char mode, unsigned short start, int num, bool fill) :type(type), mode(mode), start(start)
		{
			for (int i = 0; i < 8; ++i)
				preset[i] = 0;
			preset[5] = fill;
			preset[6] = num;
		}
		// ‘½ŠpŒ`
		Shape(char type, unsigned char mode, unsigned short start, int num) :type(type), mode(mode), start(start)
		{
			for (int i = 0; i < 8; ++i)
				preset[i] = 0;
			preset[6] = num;
		}
	};

public:
	enum class Message
	{
		none,
		quit,
	};

	static Draw main;
	static Draw ui;

	static inline int select = -1;

	static void preset();
	static Message update();
	static void draw();
};

