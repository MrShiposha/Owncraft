#include <World.h>

#include <fstream>
#include <sstream>

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

World::World(const std::string & file_path)
{
	load_blocks();

	std::ifstream in(file_path);
	if (!in.is_open())
		throw std::runtime_error("Can't open World file");

	std::string line;
	std::stringstream line_stream;


	double x, y, z;
	std::string block_name;

	while (!in.eof())
	{
		std::getline(in, line);
		line_stream << line;

		line_stream >> x;
		line_stream >> y;
		line_stream >> z;
		line_stream >> block_name;

		if (line_stream.bad())
			throw std::runtime_error("Incorrect World file");

		line_stream.str("");
		line_stream.clear();


		if (blocks.find(block_name) == blocks.end())
			throw std::runtime_error("Block \"" + block_name + "\" is not found");

		auto matrix = osg::Matrix::translate(x, y, z);

		osg::ref_ptr<osg::MatrixTransform> matrix_node = new osg::MatrixTransform();
		matrix_node->setMatrix(matrix);
		matrix_node->addChild(blocks.at(block_name));

		groups.at(block_name)->addChild(matrix_node);
	}
}

const osg::ref_ptr<osg::Node> World::root() const
{
	osg::ref_ptr<osg::Group> root = new osg::Group();

	for (auto &block_group : groups)
		root->addChild(block_group.second);

	return root;
}

void World::load_blocks()
{
	using namespace boost::filesystem;

	path blocks_path("assets/blocks");

	auto directory_range = boost::make_iterator_range(directory_iterator(blocks_path), {});

	path block_path;
	for(auto &block_entry : directory_range) 
	{
		block_path = block_entry.path();

		if (is_regular_file(block_path) && block_path.filename().extension() == ".obj")
		{
			blocks[block_path.stem().string()] = osgDB::readRefNodeFile(block_path.string());
			groups[block_path.stem().string()] = new osg::Group();
		}
	}
}
