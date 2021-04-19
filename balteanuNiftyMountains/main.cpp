/*****************************************************************************
 *	Name:     Ana Balteanu                                                    *
 *	Date:     10/5/2020                                                       *
 *                                                                            *
 *	Description:    Nifty Mountains - A program that reads pixels from a text *
 *                  file, assigns each to a colour and prints them on an      *
 *                  allegro window. It then uses various algorithms to find   *
 *                  the path with the lowest elevation change through the     *
 *                  mountains.                                                *
 *****************************************************************************/


/* RETURNS
return 1 = illegal matrix index (I received this error while debugging, I did not create this return value)
return 4 = cannot open text file
*/

#include "main.h"

ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_FONT *font = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_BITMAP *background = nullptr;
ALLEGRO_BITMAP* menuBackground = nullptr;

using namespace std;

int main(int argc, char *argv[]) {
    /**     Setup      **/

    //initializing allegro
    initializeAllegro();

    // create a display
    createDisplay(title);

    //checking initialization allegro
	checkSetup(display, font);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    cout << "Welcome to Nifty Mountains!";

    /**     Elevation Paths     **/
    bool exit = false;
    while (!exit){

        //Drawing map
        char *fileName = "Colorado.dat";
        apmatrix<short> data(480, 844);
        if (MapDataDrawer(fileName, data) == false) {
            cout << "error, cannot open file" << endl;
            return 4;
        }

        //User interface
        cout << endl;
        int choice = 0;
        int totalDisplacement = 0;
        cout << "What would you like to do!?" << endl
             << "[1] Exit" << endl
             << "[2] See paths for Greedy Algorithm, with best path" << endl
             << "[3] More optimal method (takes a long time to execute)" << endl
             << "[4] Shorter Path Faster Algorithm" << endl;

        cin >> choice;
        cout << endl;

        switch(choice){
            case 1: exit = true;
                break;

            case 2: cout << "The most efficient Greedy path is in blue" << endl;
                //draws the path of the calculated lowest path of elevation
                //within indexOfLowestElevPath, it draws the other paths of elevation from each row.
                drawMap(data);
                al_flip_display();
                totalDisplacement = drawLowestElevPath(data, indexOfLowestElevPath(data), SKYBLUE);
                cout << "The total eleveation change for the shortest path is: " << totalDisplacement << endl;
                al_flip_display();
                break;

            case 3:
                //This algorithm is similar to the previous one (case 2), in that it uses the same code to look at each individual pixel's path
                //This code takes a VERY long time to run (an estimated 15-20 minutes), as it the algorithm for every pixel.
                drawMap(data);
                al_flip_display();
                cout << "finding optimal path from all pixels, with some randomization" << endl;
                int index[2];
                allindexOfLowestElevPath(data, index);
                int row, column;
                row = index[0];
                column  = index[1];
                totalDisplacement = allDrawLowestElevPathEast(data, row, column, GREEN, 'n') + allDrawLowestElevPathWest(data, row, column, GREEN, 'n');
                cout << "The total eleveation change for the shortest path is: " << totalDisplacement << endl;
                al_flip_display();
                break;

            case 4:
                //This Path finding algorithm is the SPFA method, and finds the best possible path in the whole board by using four different
                //matricies and an queue of coordinates
                drawMap(data);
                al_flip_display();
                cout << "the ultimate floyd method" << endl;
                int totalDisplacement;
                totalDisplacement = spfaAlgorithm(data);
                cout << "The shortest path has a change in elevation of: " << totalDisplacement << endl;
                al_flip_display();
                break;

            default: cout << "Invalid number, exiting" << endl;
                exit = true;
                break;
        }
    }

    return 0;
}

//read data from given file into a 2D array (use apmatrix)
bool MapDataDrawer(const char *fname, apmatrix<short> &map) {

    ifstream dataFile(fname);
    //checking if files can open for reading
    if (!dataFile.is_open() ) {
        cout << "Unable to open file" << endl;
        return false;
    } else {
        //reading from file into 2D array
        for (int j = 0; j < map.numrows(); j++) {
            for (int i =0 ; i<map.numcols(); i++) {
                dataFile >> map[j][i];
            }
        }
        return true;
    }
}

