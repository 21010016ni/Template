#pragma once
#include <compare>
#include <cmath>

template<class T> class Point
{
public:
	T y, x;

	Point(const T& y = 0, const T& x = 0) :y(y), x(x) {}
	~Point() {}

	Point operator+(const Point& v)const noexcept { return {y + v.y,x + v.x}; }
	Point operator-(const Point& v)const noexcept { return {y - v.y,x - v.x}; }
	Point operator*(const Point& v)const noexcept { return {y * v.y,x * v.x}; }
	Point operator/(const Point& v)const noexcept { return {y / v.y,x / v.x}; }

	Point operator*(const T& v)const noexcept { return {y * v,x * v}; }
	Point operator/(const T& v)const noexcept { return {y / v,x / v}; }

	Point& operator+=(const Point& v)noexcept { return y += v.y, x += v.x, *this; }
	Point& operator-=(const Point& v)noexcept { return y -= v.y, x -= v.x, *this; }
	Point& operator*=(const Point& v)noexcept { return y *= v.y, x *= v.x, *this; }
	Point& operator/=(const Point& v)noexcept { return y /= v.y, x /= v.x, *this; }

	Point& operator*=(const T& v)noexcept { return y *= v, x *= v, *this; }
	Point& operator/=(const T& v)noexcept { return y /= v, x /= v, *this; }

	auto operator<=>(const Point&)const = default;

	constexpr Point operator()(const T& t)const noexcept { return {t / x,t % x}; }

	constexpr Point approximate(const Point& siz, int level)const { return {y / (siz.y / level),x / (siz.x / level)}; }

	template<typename U>constexpr U length()const noexcept { return std::sqrt(y * y + x * x); }
	template<typename U>constexpr U distance(Point t)const noexcept { return (t -= *this).length<U>(); }
	template<typename U>constexpr Point& rotate(const U& t)noexcept { return y = y * cos(t) + x * sin(t), x = -y * sin(t) + x * cos(t), *this; }
	template<typename U>constexpr U cross_check(const Point& t, const U& ang)const { return (y - t.y) * cos(ang) - (x - t.x) * sin(ang); }

	template<typename U>constexpr explicit operator Point<U>()const noexcept { return {(U)y,(U)x}; };
};

