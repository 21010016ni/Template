#pragma once
#include <list>

class SoundEffect
{
	struct Data
	{
		int handle;
		short pan;
		char volume;

		void Play();
	};

	std::list<std::pair<int, Data>> line;
};

