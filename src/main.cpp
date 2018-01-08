#ifdef _MSC_VER
#	pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 

#include <osgViewer/Viewer>

int main()
{
	osgViewer::Viewer viewer;

	return viewer.run();
}