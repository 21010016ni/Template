#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <stack>

#define cout std::cout
#define cin std::cin
#define br std::endl

class BinOut
{
public:
	std::ofstream ofs;
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
		ofs.write(reinterpret_cast<char*>(&value), sizeof(value));
	}
};

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
	char type;
	std::string func;
	std::vector<std::string> com;
	std::vector<Shape> shape;
	std::stack<int> value;

	while (true)
	{
		cout << "�o�̓t�@�C�����iend�ŏI���j" << br << "\t";
		cin >> filename;
		cin.ignore();
		if (filename == "end")
		{
			break;
		}
		BinOut ofs(filename);

		cout << br << "���� : ";
		cin >> duration;
		cin.ignore();
		ofs.write(duration);

		while (true)
		{
			shape.emplace_back();
			auto& i = shape.back();
			int buf;
			cout << "�}�`�^�C�v(0:�_ 1:���~ 2:�����p�` 3:�� -1�ŏI��)" << br << "\t";
			cin >> buf;
			cin.ignore();
			type = buf;
			if (type == -1)
				break;
			i.type = type;
			cout << "�������[�h : ";
			cin >> buf;
			cin.ignore();
			i.mode = buf;
			cout << "�J�n�t���[�� : ";
			cin >> i.start;
			cin.ignore();


			switch (i.type)
			{
			case 1:	// Circle
				cout << "���~�`��̊p�� : ";
				cin >> i.preset[6];
				cin.ignore();
				cout << "�h��Ԃ�(t/f) : ";
				cin >> buf;
				cin.ignore();
				if (buf == 't')
					i.preset[5] = true;
				else
					i.preset[5] = false;
				break;
			case 2:	// Polygon
				cout << "�p�̐� : ";
				cin >> i.preset[6];
				cin.ignore();
				break;
			}

			bool functionSucsess = true;
			do
			{
				cout << "�֐���`" << br << "\t";
				std::getline(cin, func);
				boost::split(com, func, boost::is_any_of(" "));

				for (const auto& j : com)
				{
					if (j == "v0")
						i.func.emplace_back(command::v0);
					else if (j == "v1")
						i.func.emplace_back(command::v1);
					else if (j == "v2")
						i.func.emplace_back(command::v2);
					else if (j == "v3")
						i.func.emplace_back(command::v3);
					else if (j == "v4")
						i.func.emplace_back(command::v4);
					else if (j == "v5")
						i.func.emplace_back(command::v5);
					else if (j == "v6")
						i.func.emplace_back(command::v6);
					else if (j == "v7")
						i.func.emplace_back(command::v7);
					else if (j == "t")
						i.func.emplace_back(command::t);
					else if (j == "width")
						i.func.emplace_back(command::width);
					else if (j == "height")
						i.func.emplace_back(command::height);
					else if (j == "pi")
						i.func.emplace_back(command::pi);
					else if (j == "=")
						i.func.emplace_back(command::equal);
					else if (j == "+")
						i.func.emplace_back(command::ADD);
					else if (j == "-")
						i.func.emplace_back(command::SUB);
					else if (j == "*")
						i.func.emplace_back(command::MUL);
					else if (j == "/")
						i.func.emplace_back(command::DIV);
					else if (j == "sin")
						i.func.emplace_back(command::SIN);
					else if (j == "cos")
						i.func.emplace_back(command::COS);
					else if (j == "tan")
						i.func.emplace_back(command::TAN);
					else if (j == ";" || j == "|")
						i.func.emplace_back(command::end);
					else if (j[0] == 'x'||j[0]=='X')
					{
						float v = std::stoi(j.substr(1), nullptr, 16);
						i.func.emplace_back(*reinterpret_cast<uint32_t*>(&v));
					}
					else if ((j[0] >= '0' && j[0] <= '9') || j[0] == '-')
					{
						float v = std::stof(j);
						i.func.emplace_back(*reinterpret_cast<uint32_t*>(&v));
					}
					else
					{
						cout << "ERROR! ��`����Ă��Ȃ����Z�q�ł�" << br;
						i.func.clear();
						functionSucsess = false;
						break;
					}
				}

				try
				{
					for (const auto& j : i.func)
					{
						if (j & 1)
						{
							// ����
							if (j < command::num)
							{
								value.emplace(0);
							}
							else if (j < command::dfunc)
							{
								value.pop();
								value.pop();
								value.emplace(0);
							}
							else if (j < command::sfunc)
							{
								value.pop();
								value.emplace(0);
							}
							else if (j == command::end)
							{
								value.pop();
							}
						}
						else
						{
							// �l
							value.emplace(0);
						}
					}
				}
				catch (...)
				{
					cout << "ERROR! �֐��̃e�X�g�Ɏ��s���܂���" << br;
					functionSucsess = false;
				}
			} while (!functionSucsess);

			// ��
		}

		// �����o��

		short num = shape.size();
		ofs.write(num);
		int polynum = 0;
		bool fill = 0;

		for (const auto& i : shape)
		{
			ofs.write(i.type);
			ofs.write(i.mode);
			ofs.write(i.start);

			switch (i.type)
			{
			case 1:
				polynum = i.preset[6];
				fill = i.preset[5];
				ofs.write(polynum);
				ofs.write(fill);
				break;
			case 2:
				polynum = i.preset[6];
				ofs.write(polynum);
				break;
			}

			num = i.func.size();
			ofs.write(num);
			for (const auto& j : i.func)
			{
				ofs.write(j);
			}
		}

		cout << "�t�@�C���̏o�͂ɐ������܂���" << br << br;
	}
	return 0;
}

