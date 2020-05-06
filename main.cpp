#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string>

using namespace olc;

Sprite *menu = nullptr;
Decal *Menu = nullptr;

std::string station;
std::string song;

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name you application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		menu = new Sprite("mainMenu.png");
		Menu = new Decal(menu);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//Clear Frame
		Clear(WHITE);

		// called once per frame, draws random coloured pixels
		vf2d pos = { 0, 0 };
		vf2d size = { 256, 240 };
		DrawDecal(pos, Menu);

		if (GetKey(olc::Key::ESCAPE).bPressed)
		{
			return 0;
		}

		DrawStringDecal({ 20, 50 }, "Radio Station: ", WHITE, { 1.45f, 1.45f });
		DrawStringDecal({ 20, 80 }, "Song: ", WHITE, { 1.45f, 1.45f });
		if (station == "")
		{
			DrawStringDecal({ 190, 50 }, "! UNKNOWN !", YELLOW, { 1.45f, 1.45f });
		}

		if (song == "")
		{
			DrawStringDecal({ 85, 80 }, "! UNKNOWN !", YELLOW, { 1.45f, 1.45f });
		}
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(400, 240, 2, 2, true))
		demo.Start();
	return 0;
}
