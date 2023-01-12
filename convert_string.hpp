#pragma once
#include <string>

namespace ext
{
	// ���UTF-8(char8_t)�^�ƒʏ�̕����^(char)�Ƃ̑��ݕϊ����T�|�[�g����֐��Q�ł�
	// �ꕔ�̊֐��́iSTL�W���ł��I�j������basic_string<char>�����󂯎��Ȃ��ꍇ�����邽�߁A���̕ӂ̒������s���ړI�ł�
	// �����Ƃ��āAShift-JIS�Ȃǂ̕������UTF-8�ɕϊ�����̂ł͂Ȃ��A�����܂�C++��ł̌^��ϊ����邾���ƂȂ��Ă��܂�

	// �w�肵���^�̃|�C���^������ɉ��ߕϊ�
	template<class T, class U>
	const T* to(const std::basic_string<U,std::char_traits<U>,std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	// �w�肵���^�̃|�C���^������ɉ��ߕϊ�
	template<class T, class U>
	const T* to(const U* v)
	{
		return reinterpret_cast<const T*>(v);
	}

	// �w�肵���^������basic_string�ɉ��ߕϊ�
	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> convert(const std::basic_string<U, std::char_traits<U>, std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	// ���l���w�肵���^�̃|�C���^������ɉ��ߕϊ� ����float��double�ł�����
	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> vto(U v)
	{
		return convert<T>(std::to_string(v));
	}
};

