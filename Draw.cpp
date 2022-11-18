#include "Draw.hpp"
#include <DxLib.h>
#include <cmath>
#include "Config.hpp"
#include "convert_string.hpp"

Draw::Shake::Shake()
{
	count = 0;
	mode = 0;
	time = 0;
	power = 0.0f;
	lvmx = 0;
	lvmn = 0;
}

void Draw::Shake::set(int time, float power, int mx, int mn)
{
	count = 0;
	mode = 1;
	this->time = time;
	this->power = power;
	dir = 0;
	lvmx = mx;
	lvmn = mn;
}

void Draw::Shake::set(int time, float x, float y, int mx, int mn)
{
	count = 0;
	mode = 3;
	this->time = time;
	power = 0;
	dir = {y,x};
	lvmx = mx;
	lvmn = mn;
}

void Draw::Shake::update()
{
	if(mode & 1 && count < time)
	{
		++count;
		if(mode & 2)
		{
			// 方向指定
			v = dir * sin(count * common::pi2 / time);
			v.y *= -1;
		}
		else
		{
			// ランダム
			float angle = std::uniform_real_distribution<float>{0.0f,common::pi2}(common::engine);
			v.y = sin(angle);
			v.x = cos(angle);
			v *= power;
		}
	}
}


const Point<int> Draw::GetRef(unsigned char ref, int w, int h)
{
	return {ref & 0x01 ? h / (ref & 0x02 ? 2 : 1) : 0,ref & 0x04 ? w / (ref & 0x08 ? 2 : 1) : 0};
}

void Draw::blend()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Draw::blend(unsigned char mode, unsigned char value)
{
	SetDrawBlendMode(mode, value);
}

void Draw::pixel(int x, int y, unsigned int color)const
{
	DrawPixel(static_cast<int>(shake.x(lv)) + pos.x + x, static_cast<int>(shake.y(lv)) + pos.y + y, color);
}

void Draw::pixel(const Point<int>& dst, unsigned int color)const
{
	DrawPixel(static_cast<int>(shake.x(lv)) + pos.x + dst.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y, color);
}

void Draw::rect(int x, int y, int w, int h, unsigned int color, bool fill)const
{
	DrawBox(static_cast<int>(shake.x(lv)) + pos.x + x, static_cast<int>(shake.y(lv)) + pos.y + y, static_cast<int>(shake.x(lv)) + pos.x + x + w, static_cast<int>(shake.y(lv)) + pos.y + y + h, color, fill);
}

void Draw::rect(const Point<int>& dst, const Point<int>& siz, unsigned int color, bool fill)const
{
	DrawBox(static_cast<int>(shake.x(lv)) + pos.x + dst.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y, static_cast<int>(shake.x(lv)) + pos.x + dst.x + siz.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y + siz.y, color, fill);
}

void Draw::rectAA(float x, float y, float w, float h, unsigned int color, bool fill, float thick)const
{
	DrawBoxAA(shake.x(lv) + pos.x + x, shake.y(lv) + pos.y + y, shake.x(lv) + pos.x + x + w, shake.y(lv) + pos.y + y + h, color, fill, thick);
}

void Draw::rectAA(const Point<float>& dst, const Point<float>& siz, unsigned int color, bool fill, float thick)const
{
	DrawBoxAA(shake.x(lv) + pos.x + dst.x, shake.y(lv) + pos.y + dst.y, shake.x(lv) + pos.x + dst.x + siz.x, shake.y(lv) + pos.y + dst.y + siz.y, color, fill, thick);
}

void Draw::circle(int x, int y, int r, unsigned int color, bool fill, int thick)const
{
	DrawCircle(static_cast<int>(shake.x(lv)) + pos.x + x, static_cast<int>(shake.y(lv)) + pos.y + y, r, color, fill, thick);
}

void Draw::circle(const Point<int>& dst, int r, unsigned int color, bool fill, int thick)const
{
	DrawCircle(static_cast<int>(shake.x(lv)) + pos.x + dst.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y, r, color, fill, thick);
}

void Draw::circleAA(float x, float y, float r, int num, unsigned int color, bool fill, float thick)const
{
	DrawCircleAA(shake.x(lv) + pos.x + x, shake.y(lv) + pos.y + y, r, num, color, fill, thick);
}

void Draw::circleAA(const Point<float>& dst, float r, int num, unsigned int color, bool fill, float thick)const
{
	DrawCircleAA(shake.x(lv) + pos.x + dst.x, shake.y(lv) + pos.y + dst.y, r, num, color, fill, thick);
}

void Draw::triangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color, bool fill)const
{
	DrawTriangle(static_cast<int>(shake.x(lv)) + pos.x + x0, static_cast<int>(shake.y(lv)) + pos.y + y0, static_cast<int>(shake.x(lv)) + pos.x + x1, static_cast<int>(shake.y(lv)) + pos.y + y1, static_cast<int>(shake.x(lv)) + pos.x + x2, static_cast<int>(shake.y(lv)) + pos.y + y2, color, fill);
}

void Draw::triangle(const Point<int>& dst0, const Point<int>& dst1, const Point<int>& dst2, unsigned int color, bool fill)const
{
	DrawTriangle(static_cast<int>(shake.x(lv)) + pos.x + dst0.x, static_cast<int>(shake.y(lv)) + pos.y + dst0.y, static_cast<int>(shake.x(lv)) + pos.x + dst1.x, static_cast<int>(shake.y(lv)) + pos.y + dst1.y, static_cast<int>(shake.x(lv)) + pos.x + dst2.x, static_cast<int>(shake.y(lv)) + pos.y + dst2.y, color, fill);
}

void Draw::triangleAA(float x0, float y0, float x1, float y1, float x2, float y2, unsigned int color, bool fill, float thick)const
{
	DrawTriangleAA(shake.x(lv) + pos.x + x0, shake.y(lv) + pos.y + y0, shake.x(lv) + pos.x + x1, shake.y(lv) + pos.y + y1, shake.x(lv) + pos.x + x2, shake.y(lv) + pos.y + y2, color, fill, thick);
}

void Draw::triangleAA(const Point<float>& dst0, const Point<float>& dst1, const Point<float>& dst2, unsigned int color, bool fill, float thick)const
{
	DrawTriangleAA(shake.x(lv) + pos.x + dst0.x, shake.y(lv) + pos.y + dst0.y, shake.x(lv) + pos.x + dst1.x, shake.y(lv) + pos.y + dst1.y, shake.x(lv) + pos.x + dst2.x, shake.y(lv) + pos.y + dst2.y, color, fill, thick);
}

void Draw::graph(int x, int y, int graph, bool alpha) const
{
	DrawGraph(static_cast<int>(shake.x(lv)) + pos.x + x, static_cast<int>(shake.y(lv)) + pos.y + y, graph, alpha);
}

void Draw::graph(const Point<int>& dst, int graph, bool alpha) const
{
	DrawGraph(static_cast<int>(shake.x(lv)) + pos.x + dst.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y, graph, alpha);
}

int Draw::string(int x, int y, const std::u8string& v, unsigned int color, unsigned char ref, unsigned int edge)const
{
	int w = GetDrawStringWidthToHandle(ext::to<TCHAR>(v), static_cast<int>(v.size()), font);
	auto r = GetRef(ref, w, GetFontSizeToHandle(font));
	DrawStringToHandle(static_cast<int>(shake.x(lv)) + pos.x + x+r.x, static_cast<int>(shake.y(lv)) + pos.y + y + r.y, ext::to<TCHAR>(v), color, font, edge);
	return w;
}

int Draw::string(const Point<int>& dst, const std::u8string& v, unsigned int color, unsigned char ref, unsigned int edge)const
{
	int w = GetDrawStringWidthToHandle(ext::to<TCHAR>(v), static_cast<int>(v.size()), font);
	auto r = GetRef(ref, w, GetFontSizeToHandle(font));
	DrawStringToHandle(static_cast<int>(shake.x(lv)) + pos.x + dst.x + r.x, static_cast<int>(shake.y(lv)) + pos.y + dst.y + r.y, ext::to<TCHAR>(v), color, font, edge);
	return w;
}

