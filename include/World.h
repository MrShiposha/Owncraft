#ifndef OWNCRAFT_WORLD_H
#define OWNCRAFT_WORLD_H

#include <string>
#include <map>

#include <osg/Geode>

class SkyBox;

class World
{
public:
	World(osg::ref_ptr<SkyBox>, const std::string &file_path);

	const osg::ref_ptr<osg::Node> root() const;

private:
	void load_blocks();

	osg::ref_ptr<SkyBox> skybox;

	std::map<std::string, osg::ref_ptr<osg::Group>> groups;
	std::map<std::string, osg::ref_ptr<osg::Node>> blocks;
};

#endif // OWNCRAFT_WORLD_H