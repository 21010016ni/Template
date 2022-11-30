#pragma once
#include <string>

namespace ext
{
	template<class T, class U>
	const T* to(const std::basic_string<U,std::char_traits<U>,std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	template<class T, class U>
	const T* to(const U* v)
	{
		return reinterpret_cast<const T*>(v);
	}

	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> convert(const std::basic_string<U, std::char_traits<U>, std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> vto(U v)
	{
		return convert<T>(std::to_string(v));
	}
};

