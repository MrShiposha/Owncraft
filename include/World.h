#ifndef OWNCRAFT_WORLD_H
#define OWNCRAFT_WORLD_H

#include <string>
#include <map>

#include <osg/Geode>

class World
{
public:
	World(const std::string &file_path);

	const osg::ref_ptr<osg::Node> root() const;

private:
	void load_blocks();

	std::map<std::string, osg::ref_ptr<osg::Group>> groups;

	std::map<std::string, osg::ref_ptr<osg::Node>> blocks;
};

#endif // OWNCRAFT_WORLD_H