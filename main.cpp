#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "./include/fmod.hpp"
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


//Using Geany for programming this software. 
//This is the commands for my setup. Your include and lib locations may differ.
//g++ -o OLCar main.cpp -lX11 -lGL -lpthread -lpng -I/home/pi/Documents/Documents/include -L/home/pi/Documents/Documents/fmodlib -lfmod -lstdc++fs -std=c++17

//making sure that your $LD_LIBRARY_PATH is pointing to your lib locations as well example listed below.
// $ sudo nano /etc/bash.bashrc
// $ export LD_LIBRARY_PATH=/home/pi/Documents/Documents/fmodlib/
// Place the export LD_LIBRARY_PATH at the bottom of the bashrc and your environment variables will be set perminantly
// Then your dynamic library is pointing to the right location.

using namespace olc;


Sprite *menu = nullptr;
Decal *Menu = nullptr;

//Searching directory for music function
//DIR connects to the directory
DIR *list;
//dirent reads the files in the directory
struct dirent *read;
//Read size
int rSize;
std::string sTemp;
int rPos = 30;
float rCol[10];
int rColPos = 0;
float tempCol = 65;

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
		sis->createStream("./music/sample.mp3", FMOD_CREATESTREAM, 0, &sound1);
		//sis->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
		
		// Called once at the start, so create things here
		menu = new Sprite("mainMenu.png");
		Menu = new Decal(menu);

		selection = 0;
		
		rCol[0] = 80;
		rCol[1] = 95;
		rCol[2] = 110;
		rCol[3] = 125;
		rCol[4] = 140;
		rCol[5] = 155;
		rCol[6] = 170;
		rCol[7] = 185;
		rCol[8] = 200;
		rCol[9] = 215;
		
		
		
		
		
		return true;
	}
	
	std::string convertToString(char* a, int size)
	{
			int i;
			std::string s = "";
			for (i=0; i < size; i++)
			{
				s = s + a[i];
			}
		return s;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		//Clear Frame
		Clear(WHITE);

		// called once per frame, draws random coloured pixels
		vf2d pos = { 0, 0 };
		//vf2d size = {256, 240};
		DrawDecal(pos, Menu);

		if (GetKey(olc::Key::ESCAPE).bPressed)
		{
			sis->close();
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
		
			//Search for music in the ./music folder
			list = opendir("./music/");
			if(list != NULL)
			{
				while (read == readdir (list))
				{
					rSize = sizeof(read->d_name) / sizeof(char);
				
					char *sList[rSize] = {read->d_name};
					sTemp = sList[0];
					if(sTemp != ". " || sTemp != ".. ")
					{
						DrawStringDecal({20, rCol[rColPos]}, sTemp, WHITE, {1.45f, 1.45f});
						rColPos++;	
					}
				}
			
			(void) closedir (list);
			}
				else
			{
				return 0;
			}
			
			rColPos = 0;
			

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
	if (demo.Construct(400, 240, 2, 2, false))
		demo.Start();
	return 0;
}
