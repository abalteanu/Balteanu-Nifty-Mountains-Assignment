
#include "main.h"
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;
using namespace std;

//draw the lowest elevation path starting from the given row and column going to the east
// return total elev change from the path
int allDrawLowestElevPathEast(apmatrix<short> map, int startRow, int cols, ALLEGRO_COLOR colour, bool inFunction) {

    srand(time(0));
    int option[3];
    int displacement = 0;
    int row = startRow;

    for (cols; cols < map.numcols()-1; cols++){

        //will only print something to allegro if this function is called in main
        if (inFunction == 'n'){
            //prints pixel before the rest of for loop decides where next pixel will be (optimal choice)
            al_draw_filled_rectangle (cols, row, cols+1, row+1, colour);
        }
        //prints pixel before the rest of for loop decides where next pixel will be (optimal choice)

        ///Determining displacement options from current position
        //if at very top of page, only two options are left
        if (row != 0){
            ///Up-Right
            option[0] = abs(map[row][cols] - map[row-1][cols+1]);
        } else {
            //so that there is no garbage number being compared if up-right is not an option
            option[0] = INT_MAX;
        }
        ///Right
        option[1] = abs(map[row][cols] - map[row][cols+1]);
        //if at very bottom of page, only two options are left
        if (row +1 != map.numrows()){
            ///Down-Right
            option[2] = abs(map[row][cols] - map[row+1][cols+1]);
        } else {
            option[2] = INT_MAX;
        }
        //cout << cols << ", " << " ->  (" << option[0] << ", " << option[1] << ", " << option[2] << ")" << endl;

        ///Determining optimal displacement option
        if (option[0] < option[1] && option[0] < option[2]){
            //if Up-Right is optimal
            row--;
            displacement += option[0];
        } else if (option[1] < option[0] && option[1] < option[2]){
            //if Right is optimal
            displacement += option[1];
        } else if (option[2] < option[0] && option[2] < option[1]){
            //if Down-Right is optimal
            row++;
            displacement += option[2];

        //When two/all options have equal displacements, pick randomly between them to find a direction
        } else if (option[1] == option[0]){
            displacement += option[1];
            if (rand() % 2 == 0){
                row--; //upright is chosen
            }
        } else if (option[1] == option[2]){
            displacement += option[1];
            if (rand() % 2 == 1){
                row++;  //downright is chosen
            }
        } else if (option[0] == option[2]){
            displacement += option[0];
            if (rand() % 2 == 1){
                row++;
            } else {
                row--;
            }
        } else {
            displacement += option[0];
            if (rand() %3 == 2){
                row++;
            } else {
                if(rand() % 2 == 0){
                    row--;
                }
            }
        }
    }
    return displacement;
}

//draw the lowest elevation path starting from the given row and column going to the West
//return total elev change from the path
int allDrawLowestElevPathWest(apmatrix<short> map, int startRow, int cols, ALLEGRO_COLOR colour, bool inFunction) {

    srand(time(0));
    int option[3];
    int displacement = 0;
    int row = startRow;


    for (cols; cols > 1; cols--){
        if (inFunction == 'n'){
            //prints pixel before the rest of for loop decides where next pixel will be (optimal choice)
            al_draw_filled_rectangle (cols, row, cols+1, row+1, colour);
        }
        ///Determining displacement options from current position
        //if at very top of page, only two options are left
        if (row != 0){
            ///Up-Left
            option[0] = abs(map[row][cols] - map[row-1][cols-1]);
        } else {
            //so that there is no garbage number being compared if up-right is not an option
            option[0] = INT_MAX;
        }
        ///Left
        option[1] = abs(map[row][cols] - map[row][cols-1]);
        //if at very bottom of page, only two options are left
        if (row +1 != map.numrows()){
            ///Down-Left
            option[2] = abs(map[row][cols] - map[row+1][cols-1]);
        } else {
            option[2] = INT_MAX;
        }
        //cout << cols << ", " << " ->  (" << option[0] << ", " << option[1] << ", " << option[2] << ")" << endl;

        ///Determining optimal displacement option
        if (option[0] < option[1] && option[0] < option[2]){
            //if Up-Left is optimal
            row--;
            displacement += option[0];
        } else if (option[1] < option[0] && option[1] < option[2]){
            //if Left is optimal
            displacement += option[1];
        } else if (option[2] < option[0] && option[2] < option[1]){
            //if Down-Left is optimal
            row++;
            displacement += option[2];

        //When two/all options have equal displacements, pick randomly between them to find a direction
        } else if (option[1] == option[0]){
            displacement += option[1];
            if (rand() % 2 == 0){
                row--; //upright is chosen
            }
        } else if (option[1] == option[2]){
            displacement += option[1];
            if (rand() % 2 == 1){
                row++;  //downright is chosen
            }
        } else if (option[0] == option[2]){
            displacement += option[0];
            if (rand() % 2 == 1){
                row++;
            } else {
                row--;
            }
        } else {
            displacement += option[0];
            if (rand() %3 == 2){
                row++;
            } else {
                if(rand() % 2 == 0){
                    row--;
                }
            }
        }
    }
    return displacement;
}

void allindexOfLowestElevPath(apmatrix<short> map, int index[2]){
    //This function goes through each row and finds the one with the lowest elevation path
    //It takes note of the row where it calculated the smallest elevaion path, and that is its return value
    int smallestDisplacement = INT_MAX;

    //does path optimization for each row and column
    for (int c = 0; c < 844; c++){
        for (int r = 0; r < 480; r++){
            int displacement = allDrawLowestElevPathWest(map, r, c, PIGGYPINK, 't') + allDrawLowestElevPathEast(map, r, c, PIGGYPINK, 't');
            //cout << displacement << endl;
            //finds smallest displacement number and index at which it occurs
            if (displacement < smallestDisplacement){
                smallestDisplacement = displacement;
                index[0] = r;
                index[1] = c;
            }

        }
        cout << "Smallest displacement recorded until now: " << smallestDisplacement << endl;
    }

    cout << "The total smallest Displacement is: " << smallestDisplacement << endl;
    cout << index[0] << endl;
    cout << index[1] << endl;
}


