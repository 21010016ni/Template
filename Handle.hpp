#pragma once
#include <memory>
#include <string>
#include <unordered_map>

enum class type :char
{
	graph,
	sound,
	font,
};

class Handle
{
	struct Data
	{
		const type t;
		const int handle;
		int duration;
	public:
		Data(type t, int handle, int duration) :t(t), handle(handle), duration(duration) {}
		~Data();
		Data& operator--()noexcept { if(duration != -1)--duration; return *this; }
		constexpr bool operator()()const { return duration > 0 || duration == -1; }
		void set(int value)noexcept { duration = value; }
		constexpr int get()const noexcept { return handle; }
	};
	static inline std::unordered_map<std::u8string, std::unique_ptr<Data>> handle;

public:
	static void update();
	static int get(const std::u8string& key, type t, int value = 3600);
};

