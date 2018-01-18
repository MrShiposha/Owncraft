#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: plato block_name plato_size" << std::endl;
		return -1;
	}


	std::stringstream stream;
	auto get_plato_size = [&stream, &argv]() -> size_t
	{
		stream.str(argv[2]);
		size_t plato_size;
		if (!(stream >> plato_size))
		{
			std::cerr << "Invalid plato size" << std::endl;
			return -2;
		}

		return plato_size;
	};

	std::string block_name = argv[1];
	size_t plato_size = get_plato_size();

	for (size_t i = 0, j = 0; i < plato_size; ++i)
		for (j = 0; j < plato_size; ++j)
			std::cout << i << " " << j << " " << 0 << " " << block_name << std::endl;
	
	return 0;
}