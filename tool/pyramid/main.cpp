#include <iostream>
#include <fstream>
#include <locale>

int main()
{
	setlocale(LC_ALL, "russian");

	std::string file_path;

	std::cout << "¬ведите путь к файлу мира: ";
	std::getline(std::cin, file_path);

	std::ofstream out(file_path, std::ios::app);
	if (!out)
	{
		std::cerr << "Can't open file \"" << file_path << "\"" << std::endl;
		return -1;
	}

	int x = 0, y = 0, z = 0;
	std::cout << "¬ведите координаты вершины пирамиды: ";
	std::cin >> x >> y >> z;

	unsigned int height = 0;
	std::cout << "¬ведите высоту пирамиды: ";
	std::cin >> height;

	std::string block_name;
	std::cout << "¬ведите им€ блоков из которых будет состо€ть пирамида: ";
	std::cin >> block_name;

	int line_pos_x = 0, line_pos_y = 0;
	for (int offset = 0, line_length = 1; offset + 1 <= height; ++offset, line_length += 2)
		for (line_pos_x = -offset; line_pos_x <= offset; ++line_pos_x)
			for (line_pos_y = -offset; line_pos_y <= offset; ++line_pos_y)
			{
				out << x + line_pos_x
					<< " " << y + line_pos_y
					<< " " << z - offset
					<< " " << block_name
					<< std::endl;
			}


	return 0;
}