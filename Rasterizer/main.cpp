#include "includes/Rendering/Window.h"

using namespace Rendering;

int main(int argc, char* argv[])
{
	{
		Window window;

		window.Setup();
		window.Run();
	}
	//	system("pause");
	return 0;
}
