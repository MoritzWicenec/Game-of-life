#include<iostream>
#include<cstdlib>

#ifdef _WIN32
// windows code goes here
  #include <io.h>
  #include <windows.h>
#else
  #include <unistd.h>
#endif

using namespace std;
const int gridSize = 20;

//coordinates (x and y)
struct coord {
        int x;
        int y;
};

//set grid
struct grid {
        bool Grid[gridSize][gridSize] = {};
};


#ifdef _WIN32
//allow the use of usleep in windows
void usleep(__int64_t usec)
{
        HANDLE timer;
        LARGE_INTEGER ft;

        ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

        timer = CreateWaitableTimer(NULL, TRUE, NULL);
        SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
        WaitForSingleObject(timer, INFINITE);
        CloseHandle(timer);
}
#endif

void clear()
{
  #ifdef _WIN32
        system("cls");
  #else
        system("clear");
  #endif
}

//enter number of cells
int numberOfCells() {

        int n;
        cout << "Enter Number of Cells: ";
        cin >> n;
        return n;
}

//enter coordinates of cells
coord coordinates(int i) {

        int x, y;
        cout << "Enter the coordinates of cell " << i << " : ";
        cin >> y >> x;
        return { x,y };
}

//print Grid function
void printGrid(grid myGrid) {
        for (int k = 0; k <= gridSize; k++)
        {
                cout << "---";
        }
        cout << endl;
        for (int x = 0; x < gridSize; x++)
        {
                for (int y = 0; y < gridSize; y++)
                {
                        if (y == 0) {
                                cout << "| ";
                        }
                        if (myGrid.Grid[x][y] == true)
                        {
                                cout << " O ";
                        }
                        else {
                                cout << " . ";
                        }
                }
                cout << " |";
                cout << endl;
        }
        for (int k = 0; k <= gridSize; k++)
        {
                cout << "---";
        }
        cout << endl;
}


//copy grid 1 to grid 2 function
            grid copyGrid(grid myGrid) {
        grid myGrid2;
        for (int x = 0; x < gridSize; x++)
        {
                for (int y = 0; y < gridSize; y++)
                {
                        myGrid2.Grid[x][y] = myGrid.Grid[x][y];
                }
        }
        return myGrid2;
}

//function that tests all rules of the game of life
grid upgradeLiveStatus(grid myGrid) {
        grid myGrid2 = copyGrid(myGrid);
        int count = 0;

        for (int a = 0; a <= gridSize; a++)
        {
                for (int b = 0; b <= gridSize; b++)
                {
                        int alive = 0;
                        for (int c = -1; c < 2; c++)
                        {
                                for (int d = -1; d < 2; d++)
                                {
                                        if (!(c == 0 && d == 0))
                                        {
                                                if (myGrid2.Grid[(a + c + gridSize) % gridSize][(b + d + gridSize) % gridSize])
                                                {
                                                        ++alive;
                                                }
                                        }
                                }
                        }
                        if (alive < 2)
                        {
                                myGrid.Grid[a % gridSize][b % gridSize] = false;
                        }
                        else if (alive == 3)
                        {
                                myGrid.Grid[a % gridSize][b % gridSize] = true;
                        }
                        else if (alive > 3)
                        {
                                myGrid.Grid[a % gridSize][b % gridSize] = false;
                        }
                }
        }
        return myGrid;
}

//run function
void run(grid myGrid, char mode) {
        mode = tolower(mode);
        while (mode == 's' || mode == 'r') {

                myGrid = upgradeLiveStatus(myGrid);
                printGrid(myGrid);
                if (mode == 's') {
                        mode = ' ';
                        while (mode == ' ')
                        {
                                cout << "Step/Run/Stop? (s/r/x): ";
                                cin >> mode;
                        }
                }
                else if (mode == 'r') {
                        cout << "^C to exit!";
                        cout << endl;
                        usleep(200000);
                }
                clear();
        }
}

//main function, combines all functions
int main() {

        char c = 'N'; //should clear grid
        int x, y;
        grid gridOne;

        while (c == 'N' || c == 'n') {
                int n = numberOfCells();
                for (int i = 0; i < n; i++) {
                        coord p = coordinates(i);
                        gridOne.Grid[p.x][p.y] = true;
                }
                clear();
                printGrid(gridOne);

                cout << "Run or Step? (r/s): ";
                cin >> c;

                if (c == 'R' || c == 'r' || c == 'S' || c == 's') {
                        clear();
                        run(gridOne, tolower(c));
                        break;
                }
        }
        return 0;
}
