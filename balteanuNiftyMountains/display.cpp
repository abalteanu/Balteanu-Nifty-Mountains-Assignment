
#include "main.h"
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;
using namespace std;


void initializeAllegro()
{
    ///This function initializes allegro and other addons
    // Initialize Allegro
	al_init();
	al_init_font_addon();   //initialize font addon
    al_init_ttf_addon();    //initialize True Type Font addon

}

void createDisplay(const char title [])
{
    ///This function creates the display and names the window
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, title);
    font = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 24, 0);
}

int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font)
{
    ///This function checks all initializations (display, keyboard, etc.) and creates a timer and an event queue
    //checking initialization of allegro
    if(!al_init())
    {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    //check display
	if (!display)
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

   	// Initialize keyboard routines
	if (!al_install_keyboard())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

   	// Initialize mouse
   	if (!al_install_mouse())
    {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// Adding image processor
 	if (!al_init_image_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// Setting up timer
	timer = al_create_timer(1.0 / FPS);

   	if (!timer)
    {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }


    if (!font)
    {
        al_show_native_message_box(display, "Error", "Error", "Could not load font 1.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialize primative add on
 	if (!al_init_primitives_addon())
    {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// set up event queue
	event_queue = al_create_event_queue();

	if (!event_queue)
    {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

	return 0; //WILL THIS RETURN 0 EVEN IF THE ERROR IS REAL??

}


//daws elevation map
void drawMap(apmatrix<short> map){

    //finding min & max altitudes
    short minAlt = findMin(map);
    short maxAlt = findMax(map);
    int colour1[3] = {10, 50, 60};
    int colour2[3] = {253, 60, 25};
    int colour3[3];

    //ALLEGRO_COLOR allegroColour = al_map_rgb(0, 0, 0);
    for (int j = 0; j < map.numrows(); j++) {
        for (int i = 0 ; i < map.numcols(); i++) {
            float opacity = float(map[j][i] - minAlt) / float(maxAlt);
            //allegroColour = al_map_rgb(colour, colour, colour);
            for (int i = 0; i < 3; i++){
                colour3[i] = (colour2[i] - colour1[i]) * opacity + colour1[i];
            }
            shade = al_map_rgb(colour3[0], colour3[1], colour3[2]);
            al_draw_filled_rectangle (i, j, i+1, j+1, shade);

        }
    }
    //cout << "incrementing value is " << increment << endl;
}

