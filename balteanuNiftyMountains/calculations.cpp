
#include "main.h"
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

using namespace std;

//return the minimum value in the map
short findMin(apmatrix<short> &map){

    short num = map[0][0];
    //going through each short in a array and comparing it to the smallest array value (stored in num)
    for (int j = 0; j < map.numrows(); j++) {
        for (int i =0 ; i<map.numcols(); i++) {
            if (map[j][i] < num){
                //if next array value is smaller than what is currently stored in num, num gets replaced by smaller value
                num = map[j][i];
            }
        }
    }
    //cout << "Min altitutde is: " << num << endl;
    return num;
}

//return the max value in the map
short findMax(apmatrix<short> &map){

    short num = map[0][0];
    //going through each short in a array and comparing it to the largest array value (stored in num)
    for (int j = 0; j < map.numrows(); j++) {
        for (int i = 0 ; i < map.numcols(); i++) {
            if (map[j][i] > num){
                //if next array value is larger than what is currently stored in num, num gets replaced by larger value
                num = map[j][i];
            }
        }
    }
    //cout << "Max altitutde is: " << num << endl;
    return num;
}

//draw the lowest elevation path starting from the given row
// return total elev change from the path
int drawLowestElevPath(apmatrix<short> map, int startRow, ALLEGRO_COLOR colour) {

    srand(time(0));
    int option[3];
    int displacement = 0;
    int row = startRow;


    for (int cols = 0; cols < map.numcols()-1; cols++){

        //prints pixel before the rest of for loop decides where next pixel will be (optimal choice)
        al_draw_filled_rectangle (cols, row, cols+1, row+1, colour);

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


int indexOfLowestElevPath(apmatrix<short> map){
    //This function goes through each row and finds the one with the lowest elevation path
    //It takes note of the row where it calculated the smallest elevaion path, and that is its return value
    int index;
    int smallestDisplacement = INT_MAX;
    //does path optimization for each row
    for (int i = 0; i < 480; i++){
        int displacement = drawLowestElevPath(map, i, PIGGYPINK);
        //cout << displacement << endl;
        //finds smallest displacement number and index at which it occurs
        if (displacement < smallestDisplacement){
            smallestDisplacement = displacement;
            index = i;
        }
    }

    return index;
}

