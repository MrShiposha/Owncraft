#include <World.h>

#include <fstream>
#include <sstream>

#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgUtil/SmoothingVisitor>

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


	int x, y, z;
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


osg::ref_ptr<osg::Node> load_block(const std::string &block_name)
{
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec2Array> texcoords_side = new osg::Vec2Array();

	// front
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));

	// ------ top 
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 1.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));

	// ------ back 
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 1.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));


	// ------ Bottom 
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 0.0f));
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));


	// ------ Left 
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	vertices->push_back(osg::Vec3(0.0f, 1.0f, 1.0f));
	vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));


	// ------ Right 
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 0.0f));
	vertices->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
	vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));

	texcoords_side->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords_side->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 1.0f));
	texcoords_side->push_back(osg::Vec2(1.0f, 0.0f));

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(vertices);
	geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 24));
	osgUtil::SmoothingVisitor::smooth(*geom);

	osg::ref_ptr<osg::Texture2D> texture_side = new osg::Texture2D();
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("assets/blocks/" + block_name + ".png");
	texture_side->setImage(image);

	geom->setTexCoordArray(0, texcoords_side);
	geom->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture_side);
	texture_side->setUnRefImageDataAfterApply(true);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addChild(geom);

	return geode;
}

void World::load_blocks()
{
	using namespace boost::filesystem;

	path blocks_path("assets/blocks");

	auto directory_range = boost::make_iterator_range(directory_iterator(blocks_path), {});

	path block_path;
	std::string block_name;
	for(auto &block_entry : directory_range) 
	{
		block_path = block_entry.path();
		block_name = block_path.stem().string();

		if (is_regular_file(block_path) && block_path.filename().extension() == ".png")
		{
			blocks[block_name] = load_block(block_name);
			groups[block_name] = new osg::Group();
		}
	}
}