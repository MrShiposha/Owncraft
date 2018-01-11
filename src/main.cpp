#include <system.h>

#include <iostream>

#include <osgWidget/Frame>


#include <MainView.h>
#include <World.h>
#include <Player.h>


int process_exception(const std::runtime_error &);

int process_exception();

static const osg::GraphicsContext::ScreenIdentifier SCREEN_IDENTIFIER = 0;

int main()
{
	try
	{
		MainView main_view(SCREEN_IDENTIFIER);

		World world("assets/world.txt");
		main_view.place_world(world);

		Player player;
		main_view.place_player(player);

		return main_view.run();
	}
	catch (const std::runtime_error &re)
	{
		return process_exception(re);
	}
	catch (...)
	{
		return process_exception();
	}
}

int process_exception()
{
	init_console();

	std::cerr << "Unknown sxception" << std::endl;

#ifdef _WIN32
	system("pause");
#endif // _WIN32
	return -1;
}

int process_exception(const std::runtime_error &re)
{
	init_console();

	std::cerr << "Error: " << re.what() << std::endl;

	system("pause");
	return -2;
}