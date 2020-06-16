#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "fmod.hpp"
#include <string>

using namespace olc;

Sprite *menu = nullptr;
Decal *Menu = nullptr;

std::string station;
std::string song;

//Selection Of Menu
int selection;

FMOD::System *sis;
FMOD::Channel *channel = 0;
FMOD::Sound *sound1;


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
		FMOD::System_Create(&sis);      // Create the main system object.

		sis->init(32, FMOD_INIT_NORMAL, NULL);    // Initialize FMOD.
		sis->createSound("./music/sample.mp3", FMOD_CREATESTREAM, 0, &sound1);

		// Called once at the start, so create things here
		menu = new Sprite("mainMenu.png");
		Menu = new Decal(menu);

		selection = 0;

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
		if (GetKey(olc::Key::K1).bPressed)
		{
			sis->playSound(sound1, 0, false, &channel);
			selection = 0;
		}
		if (GetKey(olc::Key::K2).bPressed)
		{
			selection = 1;
		}
		if (GetKey(olc::Key::K3).bPressed)
		{
			selection = 2;
		}
		if (GetKey(olc::Key::K4).bPressed)
		{
			selection = 3;
		}

		switch (selection)
		{
		case 0:
			DrawStringDecal({ 20, 50 }, "Radio Station: ", WHITE, { 1.45f, 1.45f });
			DrawStringDecal({ 20, 80 }, "Song: ", WHITE, { 1.45f, 1.45f });
			DrawStringDecal({ 20, 110 }, "Word Of The Day", WHITE, { 1.45f, 1.45f });
			if (station == "")
			{
				DrawStringDecal({ 190, 50 }, "! UNKNOWN !", YELLOW, { 1.45f, 1.45f });
			}

			if (song == "")
			{
				DrawStringDecal({ 85, 80 }, "! UNKNOWN !", YELLOW, { 1.45f, 1.45f });
			}


			break;
		case 1:
			DrawStringDecal({ 20, 50 }, "Downloaded Music", WHITE, { 1.45f, 1.45f });




			break;
		case 2:

			break;
		case 3:

			break;
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
