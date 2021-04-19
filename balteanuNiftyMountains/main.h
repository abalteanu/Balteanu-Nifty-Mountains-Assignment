
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>



#include "apmatrix.h"

#include <allegro5/allegro.h>                       // For allegro, must be in compiler search path.
#include <allegro5/allegro_font.h>                  // Font library
#include <allegro5/allegro_ttf.h>                   // For ttf (True Type Font) addon
#include <allegro5/allegro_image.h>                 // For adding images
#include <allegro5/allegro_primitives.h>            // For al_init_primitives_addon()
#include <allegro5/allegro_native_dialog.h> 		// For message box


const float FPS = 60;
const int SCREEN_W = 844;       // screen width
const int SCREEN_H = 480;       // screen height
const char title[30] = "Nifty Mountains";

#define SKYBLUE         al_map_rgb(135, 206, 235)
#define GREEN           al_map_rgb(50, 250,50)
#define PIGGYPINK        al_map_rgb(250, 85, 87)
static ALLEGRO_COLOR shade;
static ALLEGRO_COLOR green;

//prototyping
//display
void initializeAllegro();
void createDisplay (const char title[]);
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font);
void drawMap(apmatrix<short> map);
//calculations
short findMin(apmatrix<short> &map);
short findMax(apmatrix<short> &map);
int drawLowestElevPath(apmatrix<short> map, int startRow, ALLEGRO_COLOR colour);
int indexOfLowestElevPath(apmatrix<short> map);

//everyPixel (everyPixel specific functions have all in front of them)
int allDrawLowestElevPathWest(apmatrix<short> map, int startRow, int cols, ALLEGRO_COLOR colour, bool inFunction);
int allDrawLowestElevPathEast(apmatrix<short> map, int startRow, int cols, ALLEGRO_COLOR colour, bool inFunction);
void allindexOfLowestElevPath(apmatrix<short> map, int index[2]);

//shorter path faster algorithm
int spfaAlgorithm(apmatrix<short> &map);
int spfaIndexOfLowestElevPath(int &x, int y, apmatrix <int> distance);

//main
bool MapDataDrawer(const char *fname, apmatrix<short> &map);


