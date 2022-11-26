#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define cout std::cout
#define cin std::cin
#define br std::endl

class BinOut
{
	std::ofstream ofs;

public:
	BinOut(const std::string& filename) :ofs(filename, std::ios::binary)
	{
		if (!ofs.is_open())
			throw;
	}
	~BinOut()
	{
		ofs.close();
	}

	template<typename T>
	void write(T value)
	{
		ofs.write(reinterpret_cast<char*>(value), sizeof(value));
	}
};

struct Shape
{
	char type;
	unsigned char mode;
	short start;
	float preset[8] = { 0 };
	std::vector<uint32_t> func;

	Shape() :type(0), mode(0), start(0)
	{

	}
};

int main()
{
	std::string filename;
	short duration = 0;
	std::vector<Shape> shape;

	while (true)
	{
		cout << "�o�̓t�@�C�����iend�ŏI���j" << br << "\t";
		cin >> filename;
		if (filename == "end")
		{
			break;
		}
		BinOut ofs(filename);

		cout << br << "���� : ";
		cin >> duration;
		ofs.write(duration);

		do
		{
			shape.emplace_back();
			auto& i = shape.back();
			cout << "�}�`�^�C�v : ";
			cin >> i.type;
			cout << "�������[�h : ";
			cin >> i.mode;
			cout << "�J�n�t���[�� : ";
			cin >> i.start;
		} while (true);
	}
    return 0;
}

