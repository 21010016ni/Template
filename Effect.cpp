#include "Effect.hpp"
#include <fstream>

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

int Effect::load(const char* FileName)
{
	static int handle = 0;

	int8_t buf8 = -1;
	int16_t buf16 = -1;

	unsigned char mode = -1;
	short start = -1;
	int num = -1;
	bool fill = -1;
	uint32_t code = -1;

	std::ifstream ifs(FileName, std::ios::binary);

	if (!ifs.is_open())
	{
		return -1;
	}

	// �S�̎����擾
	ifs.read(reinterpret_cast<char*>(&buf16), 2);

	// �e���v���[�g�o�^
	data.emplace(handle, buf16);
	// �o�^�������̂̎擾�E�n���h�������̂��߂ɃC���N�������g
	auto& i = data[handle];

	// �}�`���擾
	ifs.read(reinterpret_cast<char*>(&buf16), 2);
	// �}�`���o�^
	i.shape.resize(buf16);

	// �o�^�����}�`����������
	for (auto& s : i.shape)
	{
		// �^�C�v�擾
		ifs.read(reinterpret_cast<char*>(&buf8), 1);

		// �e�l�擾
		ifs.read(reinterpret_cast<char*>(&mode), 1);
		ifs.read(reinterpret_cast<char*>(&start), 2);

		// �^�C�v�ŗL�l�擾�E�o�^
		switch (buf8)
		{
		case 0:	// Pixel
			s.reset(new Template::Pixel(mode, start));
			break;
		case 1:	// Circle
			ifs.read(reinterpret_cast<char*>(&num), 4);
			ifs.read(reinterpret_cast<char*>(&fill), 1);
			s.reset(new Template::Circle(mode, start, num, fill));
			break;
		case 2:	// Polygon
			ifs.read(reinterpret_cast<char*>(&num), 4);
			s.reset(new Template::Polygon(mode, start, num));
			break;
		case 3:	// Line
			s.reset(new Template::Line(mode, start));
			break;
		}

		// ���ߐ��擾
		ifs.read(reinterpret_cast<char*>(&buf16), 2);
		// ���ߓo�^
		for (int16_t i = 0; i < buf16; ++i)
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

	if (!ofs.is_open())
		throw;

	int8_t buf8 = -1;
	int16_t buf16 = -1;
	int32_t buf32 = -1;

	float value = 0;

	// �S�̎���
	buf16 = 60;
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
	buf16 = 18;
	ofs.write(reinterpret_cast<char*>(&buf16), 2);
	// ���ߓo�^
	// ����
	buf32 = 1;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v0
	value = 255;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// 255
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
	buf32 = 3;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v1
	value = 0xffffff;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// ffffff
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
	buf32 = 5;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v2
	value = 0;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// 0
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
	buf32 = 7;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v3
	value = 0;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// 0
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
	buf32 = 9;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v4
	value = 20;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// 20
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
	buf32 = 11;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// v5
	value = 2;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// 2
	buf32 = 32;
	ofs.write(reinterpret_cast<char*>(&buf32), 4);	// =
}

