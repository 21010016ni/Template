#pragma once
#include <DxLib.h>
#include <unordered_map>
#include "Particle.hpp"
#include "Draw.hpp"

class Effect
{
	class Template
	{
		friend Effect;

		struct Pixel
		{
			unsigned char mode;
			short start;
			std::vector<uint32_t> func;
			Pixel(unsigned char mode, unsigned short start) :mode(mode), start(start) {}
		};

		struct Circle :public Pixel
		{
			int num;
			bool fill;
			Circle(unsigned char mode, unsigned short start, int num, bool fill) :Pixel(mode, start), num(num), fill(fill) {}
		};

		struct Polygon :public Pixel
		{
			int num;
			Polygon(unsigned char mode, unsigned short start, int num) :Pixel(mode, start), num(num) {}
		};

		struct Line :public Pixel
		{
			Line(unsigned char mode, unsigned short start) :Pixel(mode, start) {}
		};

		short duration;
		std::vector<std::unique_ptr<Pixel>> shape;

		class Instance :public Snowflake
		{
			// Ç±ÇÃï”Ç…ê}å`Ç∆ÇªÇÃä÷êîÇÇµÇ‹Ç¢Ç±Çﬁç\ë¢ëÃ

			Point<float> pos;
			int t;
			int buffer[8];

		public:
			Instance(int duration, float x, float y) :Snowflake(duration), pos(y, x), buffer(), t(0) {}
			void update()override;
			void draw()const override;
		};

	public:
		Template() :duration(0) {}
		Template(int duration) :duration(duration) {}
	};

	static inline std::unordered_map<int, Template> data;

public:
	static int load(const char* FileName);
	static void TestWrite();
};

