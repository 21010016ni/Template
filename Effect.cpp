#include "Effect.hpp"
#include <stack>
#include <fstream>
#include "Config.hpp"

//Effect::Effect(int x, int y) :Snowflake(0), d(x, y, 8), t(0)
//{
//	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(3 - (float)t, 3 + sin(t * 0.2f) * 4); }, [](int t) {return 256 - t * 8; }));
//	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(-2 - (float)t, -8 - sin(t * 0.2f) * 4); }, [](int t) {return 200 - t * 8; }));
//	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(1 - (float)t, 6 + cos(t * 0.2f) * 4); }, [](int t) {return 224 - t * 8; }));
//	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(4 - (float)t, -7 - cos(t * 0.2f) * 4); }, [](int t) {return 160 - t * 8; }));
//	shape.emplace_back(new Circle(blendmode::add, 0xffffffu, 3, 5, true, 1, [](int t) {return Point<float>(0 - (float)t, 1 + sin(t * 0.2f) * 4); }, [](int t) {return 190 - t * 8; }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f)							* 32,	cos(t * 0.0625f)							* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi / 3)			* 32, cos(t * 0.0625f + common::pi / 3)			* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 1 / 3)		* 32,	cos(t * 0.0625f + common::pi * 1 / 3)		* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 2 / 3)		* 32, cos(t * 0.0625f + common::pi * 2 / 3)		* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 2 / 3)		* 32,	cos(t * 0.0625f + common::pi * 2 / 3)		* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi)				* 32, cos(t * 0.0625f + common::pi)				* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi)				* 32,	cos(t * 0.0625f + common::pi)				* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 4 / 3)		* 32, cos(t * 0.0625f + common::pi * 4 / 3)		* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 4 / 3)		* 32,	cos(t * 0.0625f + common::pi * 4 / 3)		* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 5 / 3)		* 32, cos(t * 0.0625f + common::pi * 5 / 3)		* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//	shape.emplace_back(new Line(blendmode::add, 0xff00ffu, 2, [](int t) { return Point<float>(sin(t * 0.0625f + common::pi * 5 / 3)		* 32,	cos(t * 0.0625f + common::pi * 5 / 3)		* 32); }, [](int t) { return Point<float>(sin(t * 0.0625f)							* 32, cos(t * 0.0625f)							* 32); }, [](int t) { return __min(256 - t * 8, 196); }));
//}

enum command
{
	// �ϐ��o�b�t�@
	v0 = 1,
	v1 = 3,
	v2 = 5,
	v3 = 7,
	v4 = 9,
	v5 = 11,
	v6 = 13,
	v7 = 15,

	buf = 16,

	// �Q�ƕϐ�
	t = 17,
	width = 19,
	height = 21,

	var = 32,

	// �萔
	pi = 33,

	num = 64,

	// ���Z�q
	equal = 65,
	ADD = 67,
	SUB = 69,
	MUL = 71,
	DIV = 73,

	// �񍀊֐�
	SIN = 129,
	COS = 131,
	TAN = 133,

	dfunc = 256,

	// �P���֐�

	sfunc = 512,

	// ����t���[
	end = 513,
};

int Effect::load(const char* FileName)
{
	static int handle = 0;
	
	int16_t buf16 = -1;

	char type = -1;
	unsigned char mode = -1;
	short start = -1;
	int num = -1;
	bool fill = false;
	uint32_t code = -1;

	std::ifstream ifs(FileName, std::ios::binary);

	if(!ifs.is_open())
	{
		return -1;
	}

	// �S�̎����擾
	ifs.read(reinterpret_cast<char*>(&buf16), 2);

	// �e���v���[�g�o�^
	data.emplace(handle, buf16);
	// �o�^�������̂̎擾
	auto& i = data.find(handle)->second;

	// �}�`���擾
	ifs.read(reinterpret_cast<char*>(&buf16), 2);
	// �}�`���o�^
	i.shape.resize(buf16);

	// �o�^�����}�`����������
	for(auto& s : i.shape)
	{
		// �^�C�v�擾
		ifs.read(reinterpret_cast<char*>(&type), 1);

		// �e�l�擾
		ifs.read(reinterpret_cast<char*>(&mode), 1);
		ifs.read(reinterpret_cast<char*>(&start), 2);

		// �^�C�v�ŗL�l�擾�E�o�^
		switch(type)
		{
		case 0:	// Pixel
			s.reset(new Template::Shape(type, mode, start));
			break;
		case 1:	// Circle
			ifs.read(reinterpret_cast<char*>(&num), 4);
			ifs.read(reinterpret_cast<char*>(&fill), 1);
			s.reset(new Template::Shape(type, mode, start, num, fill));
			break;
		case 2:	// Polygon
			ifs.read(reinterpret_cast<char*>(&num), 4);
			s.reset(new Template::Shape(type, mode, start, num));
			break;
		case 3:	// Line
			s.reset(new Template::Shape(type, mode, start));
			break;
		}

		// ���ߐ��擾
		ifs.read(reinterpret_cast<char*>(&buf16), 2);
		// ���ߓo�^
		for(int16_t i = 0; i < buf16; ++i)
		{
			// ���ߓǂݏo��
			ifs.read(reinterpret_cast<char*>(&code), 4);
			// ���ߓo�^
			s->func.emplace_back(code);
		}
	}

	return handle++;
}

void Effect::TestWrite()
{
	std::ofstream ofs("data.bin", std::ios::binary);

	if(!ofs.is_open())
		throw;

	int8_t buf8 = -1;
	int16_t buf16 = -1;
	int32_t buf32 = -1;

	float value = 0;

	// �S�̎���
	buf16 = 128;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);

	// �}�`��
	buf16 = 2;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);

	// �}�`����������
	// �^�C�v�i�~�j
	buf8 = 1;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);

	// �������[�h
	buf8 = blendmode::add;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);
	// �J�n�t���[��
	buf16 = 0;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);

	// �p�̐�
	buf32 = 5;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);
	// �h��Ԃ�
	buf8 = true;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);

	// ���ߐ�
	buf16 = 23;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);
	// ���ߓo�^
	// ����
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v0)), 4);	// v0
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::t)), 4);	// t
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v1)), 4);	// v1
	ofs.write(reinterpret_cast<char*>(&(value = 0xffffff)), 4);	// ffffff
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v2)), 4);	// v2
	ofs.write(reinterpret_cast<char*>(&(value = -20)), 4);	// 0
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v3)), 4);	// v3
	ofs.write(reinterpret_cast<char*>(&(value = 0)), 4);	// 0
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v4)), 4);	// v4
	ofs.write(reinterpret_cast<char*>(&(value = 20)), 4);	// 20
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v7)), 4);	// v7
	ofs.write(reinterpret_cast<char*>(&(value = 2)), 4);	// 2
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =

	// �^�C�v�i�~�j
	buf8 = 1;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);

	// �������[�h
	buf8 = blendmode::add;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);
	// �J�n�t���[��
	buf16 = 0;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);

	// �p�̐�
	buf32 = 5;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);
	// �h��Ԃ�
	buf8 = true;
	ofs.write(reinterpret_cast<char*>(&buf8), 1);

	// ���ߐ�
	buf16 = 25;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);
	// ���ߓo�^
	// ����
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v0)), 4);	// v0
	ofs.write(reinterpret_cast<char*>(&(value = 255)), 4);	// 255
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::t)), 4);	// t
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::SUB)), 4);	// -
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v1)), 4);	// v1
	ofs.write(reinterpret_cast<char*>(&(value = 0xffffff)), 4);	// ffffff
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v2)), 4);	// v2
	ofs.write(reinterpret_cast<char*>(&(value = 20)), 4);	// 20
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v3)), 4);	// v3
	ofs.write(reinterpret_cast<char*>(&(value = 0)), 4);	// 0
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v4)), 4);	// v4
	ofs.write(reinterpret_cast<char*>(&(value = 20)), 4);	// 20
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::end)), 4);	// ;
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::v7)), 4);	// v7
	ofs.write(reinterpret_cast<char*>(&(value = 2)), 4);	// 2
	ofs.write(reinterpret_cast<char*>(&(buf32 = command::equal)), 4);	// =
}

Effect::Instance::Instance(float x, float y, const Template& temp)
	:Snowflake(temp.duration), d(x, y, 8), t(0)
{
	for(const auto& i : temp.shape)
		shape.emplace_back(i->type, i->mode, i->start, i->preset, i->func);
}

void Effect::Instance::update()
{
	for(auto& i : shape)
	{
		static std::stack<float*> stack;
		std::stack<std::unique_ptr<float>> value;
		++t;
		for(auto c : i.func)
		{
			if(c & 1)
			{
				// ����
				if(c < command::buf)
				{
					// �o�b�t�@�̒l
					stack.emplace(&(i.buffer[c >> 1]));
				}
				else if(c < command::num)
				{
					// �萔
					value.emplace(new float);
					switch(c)
					{
					case command::t:
						*value.top() = t;
						break;
					case command::width:
						*value.top() = common::width;
						break;
					case command::height:
						*value.top() = common::height;
						break;

					case command::pi:
						*value.top() = common::pi;
						break;
					}
					stack.emplace(value.top().get());
				}
				else if(c < command::dfunc)
				{
					// �񍀉��Z�q�E�֐�
					auto right = stack.top();
					stack.pop();
					auto left = stack.top();
					switch(c)
					{
						// ���Z�q
					case command::equal:
						*left = *right;
						break;
					case command::ADD:
						*left += *right;
						break;
					case command::SUB:
						*left -= *right;
						break;
					case command::MUL:
						*left *= *right;
						break;
					case command::DIV:
						*left /= *right;
						break;

						// �֐�
					case command::SIN:
						*left = std::sin(*left) * *right;
						break;
					case command::COS:
						*left = std::cos(*left) * *right;
						break;
					case command::TAN:
						*left = std::tan(*left) * *right;
						break;
					}
				}
				else if(c < command::sfunc)
				{
					// �P�����Z�q�E�֐�
					auto v = stack.top();
					switch(c)
					{
					default:
						break;
					}
				}
				else
				{
					switch(c)
					{
					case command::end:
						stack.pop();
						break;
					default:
						// �l
						value.emplace(new float(*reinterpret_cast<float*>(&c)));
						stack.emplace(value.top().get());
					}
				}
			}
			else
			{
				// �l
				auto v = reinterpret_cast<float*>(&c);
				value.push(std::unique_ptr<float>(new float(*v)));
				//value.push(new float(*v));
				stack.emplace(value.top().get());
			}
		}
	}
}

void Effect::Instance::draw()const
{
	for(const auto& i : shape)
	{
		switch(i.type)
		{
		case 0:	// Pixel
			d.blend(i.mode, i.buffer[0]);
			d.pixel(i.buffer[2], i.buffer[3], i.buffer[1]);
			break;
		case 1:	// Circle
			d.blend(i.mode, i.buffer[0]);
			d.circleAA(i.buffer[2], i.buffer[3], i.buffer[4], i.buffer[6], i.buffer[1], i.buffer[5], i.buffer[7]);
			break;
		case 2:	// Polygon
			d.blend(i.mode, i.buffer[0]);
			for(int n = 0, num = i.buffer[6]; n < num; ++n)
				d.lineAA(i.buffer[2] + std::cos(i.buffer[5] + common::pi2 * n / num) * i.buffer[4], i.buffer[3] + std::sin(i.buffer[5] + common::pi2 * n / num) * i.buffer[4], i.buffer[2] + std::cos(i.buffer[5] + common::pi2 * (n + 1) / num) * i.buffer[4], i.buffer[3] + std::sin(i.buffer[5] + common::pi2 * (n + 1) / num) * i.buffer[4], i.buffer[1], i.buffer[7]);
			break;
		case 3:	// Line
			d.blend(i.mode, i.buffer[0]);
			d.lineAA(i.buffer[2], i.buffer[3], i.buffer[4], i.buffer[5], i.buffer[1], i.buffer[7]);
			break;
		}
	}
	d.blend();
}

