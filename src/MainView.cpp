#include <MainView.h>

#include <osg/Camera>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

#include <World.h>

MainView::MainView(const osg::GraphicsContext::ScreenIdentifier &screen_id)
{
	viewer.setUpViewOnSingleScreen(screen_id.screenNum);
}

void MainView::place_player(const Player &)
{
	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
}

void MainView::place_world(const World &world)
{
	viewer.setSceneData(world.root());
}

int MainView::run()
{
	return viewer.run();
}
