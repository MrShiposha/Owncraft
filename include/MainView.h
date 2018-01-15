#ifndef OWNCRAFT_MAINVIEW_H
#define OWNCRAFT_MAINVIEW_H

#include <osgViewer/Viewer>
#include <osg/GraphicsContext>
#include "Player.h"

class World;

class MainView
{
public:
	MainView(const osg::GraphicsContext::ScreenIdentifier &);

	void place_player(const Player &);

	void place_world(const World &);

	int run();

private:
	osgViewer::Viewer viewer;
};

#endif // OWNCRAFT_MAINVIEW_H