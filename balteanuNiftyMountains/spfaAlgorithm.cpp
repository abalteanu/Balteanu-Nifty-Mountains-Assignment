
#include "main.h"
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *font;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP  *background;
extern ALLEGRO_BITMAP* menuBackground;

using namespace std;

int spfaAlgorithm(apmatrix<short> &mountains){
    ///This method is a lot more complicated
    //N represents number of Rows, M represents number of columns.
    //ROWS AND COLUMNS
    int N = mountains.numrows();
    int M = mountains.numcols();
    //MOUNTAINS REPRESENTS THE DATA READ IN FROM THE FILE

    //PARENT ARRAYS ARE USED TO STORE THE PREVIOUS LOCATION: (X,Y) came from parentX[x][y] and parentY[x][y]
    apmatrix<short>  parentX(N, M);
    apmatrix<short>  parentY(N, M);
    //Just reading in our example graphs, use the file for the actual ting

    apmatrix<int> distance(N, M);;


    for (int i=0; i<N; i++){
        for (int j=0; j<M; j++){
            //setting all distances to INT_MAX, to be replaced by smaller numbers later
            distance[i][j] = INT_MAX;
        }
    }
    distance[0][0] = 0;

    pair <int, int> start;
    start.first = 0;
    start.second = 0;

    //making a coordinate queue for reading best paths
    queue <pair<int, int>> myQueue;

    myQueue.push(start);

    int x, y;

    while (!myQueue.empty()){

        y = myQueue.front().first;
        x = myQueue.front().second;

        myQueue.pop();

        ///DIRECTIONS: Checking best direction option for most optimized path
        // Up
        if (y - 1 >= 0){
            if (distance[y][x] + abs(mountains[y][x] - mountains[y-1][x]) < distance[y-1][x]){

                distance[y-1][x] = distance[y][x] + abs(mountains[y][x] - mountains[y-1][x]);
                myQueue.push(make_pair(y-1,x));

                parentX[y-1][x] = x;
                parentY[y-1][x] = y;
            }
        }

        // Down
        if (y + 1 <= N-1){
            if (distance[y][x] + abs(mountains[y][x] - mountains[y+1][x]) < distance[y+1][x]){

                distance[y+1][x] = distance[y][x] + abs(mountains[y][x] - mountains[y+1][x]);
                myQueue.push(make_pair(y+1,x));

                parentX[y+1][x] = x;
                parentY[y+1][x] = y;
            }
        }

        // Left

        if (x - 1 >= 0){
            if (distance[y][x] + abs(mountains[y][x] - mountains[y][x-1]) < distance[y][x-1]){

                distance[y][x-1] = distance[y][x] + abs(mountains[y][x] - mountains[y][x-1]);
                myQueue.push(make_pair(y,x-1));

                parentX[y][x-1] = x;
                parentY[y][x-1] = y;
            }
        }


        // Right

        if (x + 1 <= M-1){
            if (distance[y][x] + abs(mountains[y][x] - mountains[y][x+1]) < distance[y][x+1]){

                distance[y][x+1] = distance[y][x] + abs(mountains[y][x] - mountains[y][x+1]);
                myQueue.push(make_pair(y, x+1));

                parentX[y][x+1] = x;
                parentY[y][x+1] = y;

            }
        }


        // Up-Right

        if (y - 1 >= 0 && x + 1 <= M-1){

            if (distance[y][x] + abs(mountains[y][x] - mountains[y-1][x+1]) < distance[y-1][x+1]){

                distance[y-1][x+1] = distance[y][x] + abs(mountains[y][x] - mountains[y-1][x+1]);
                myQueue.push(make_pair(y-1, x+1));

                parentX[y-1][x+1] = x;
                parentY[y-1][x+1] = y;
            }
        }

        // Up-Left

        if (y - 1 >= 0 && x - 1 >= 0){

            if (distance[y][x] + abs(mountains[y][x] - mountains[y-1][x-1]) < distance[y-1][x-1]){

                distance[y-1][x-1] = distance[y][x] + abs(mountains[y][x] - mountains[y-1][x-1]);
                myQueue.push(make_pair(y-1, x-1));

                parentX[y-1][x-1] = x;
                parentY[y-1][x-1] = y;
            }
        }

        // Down-right
        if (y + 1 <= N-1 && x + 1 <= M-1){

            if (distance[y][x] + abs(mountains[y][x] - mountains[y+1][x+1]) < distance[y+1][x+1]){

                distance[y+1][x+1] = distance[y][x] + abs(mountains[y][x] - mountains[y+1][x+1]);
                myQueue.push(make_pair(y+1, x+1));

                parentX[y+1][x+1] = x;
                parentY[y+1][x+1] = y;
            }
        }

        // Down-Left
        if (y + 1 <= N-1 && x - 1 >= 0){

            if (distance[y][x] + abs(mountains[y][x] - mountains[y+1][x-1]) < distance[y+1][x-1]){

                distance[y+1][x-1] = distance[y][x] + abs(mountains[y][x] - mountains[y+1][x-1]);
                myQueue.push(make_pair(y+1, x-1));

                parentX[y+1][x-1] = x;
                parentY[y+1][x-1] = y;
            }
        }
    }

    ///Printing out the most optimized path
    int nextX;
    int nextY = 843;

    int smallestDistance = spfaIndexOfLowestElevPath(nextX, nextY, distance);

    int tempX, tempY;
    cout << nextX <<  endl;

    while (nextY != 0){
        //retraces past steps using parent arrays, that carry the coordinates of the previous pixel
        al_draw_filled_rectangle(nextY, nextX, nextY + 1, nextX + 1, PIGGYPINK);

        tempX = nextX;
        tempY = nextY;

        nextY = parentX[tempX][tempY];
        nextX = parentY[tempX][tempY];

    }
    cout << endl;

    return smallestDistance;
}

int spfaIndexOfLowestElevPath(int &x, int y, apmatrix <int> distance){
    //THIS FUNCTION LOOPS THROUGH THE DISTANCE ARRAY IN THE END COLUMN AND FINDS THE SMALLEST VALUE (AKA BEST PATH)
    int smallestD = INT_MAX;
    y = 843;
    for (int i = 0; i < 480; i++){
        //going through last row of distance array and finding the smallest value
        if(distance[i][843] < smallestD){
            smallestD = distance[i][843];
            x = i;
        }
    }

    return smallestD;
}
