// Made by MalTeeez
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>


// Terminal Window needs to be 54 Height and minimum WIDTH wide
#define HEIGHT 40
#define WIDTH  74

#define EMPTY '-';
#define FULL  'O';

int DELAY = 200;

int grid[HEIGHT][WIDTH];

void spew_grid(int itr) {

    // Concatting it all onto 1 string for less term flicker
    char text[(WIDTH + 5) * HEIGHT * 2] = "\n\t\t\t\t\t---- itr ";
    char num[10];
    sprintf(num, "%d", itr);
    strcat(text, num);
    strcat(text, " - delay ");
    sprintf(num, "%d", DELAY);
    strcat(text, num);

    strcat(text, " ----\n");

    
    for ( int i = 0; i < (58 - HEIGHT - 4); i++ ) {
        strcat(text, "\n");
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int o = 0; o < WIDTH; o++)
        {
            char character;
            if ( grid[i][o] == 0 ) {
                character = EMPTY;
            } else {
                character = FULL;
            }
            strcat(text, " ");
            strncat(text, &character, 1);
        }
        strcat(text, "\n");
    }
    printf("%s", text);
}

void update_grid() {
    int temp_grid[HEIGHT][WIDTH];
    for ( int i = 0; i < HEIGHT; i++ ) {
        for ( int o = 0; o < WIDTH; o++ ) {
            int neighboors = 0;
            for ( int x = -1; x < 2; x++ ) {
                for ( int y = -1; y < 2; y++ ) {
                    // Exclude middle since thats not neighboor
                    if ( x == 0 && y == 0) continue;
                    int grid_y = i + y;
                    int grid_x = o + x;

                    // Move to other side of OOB
                    if ( grid_y < 0 ) {
                        grid_y = grid_y + HEIGHT;
                    } else if ( grid_y >= HEIGHT ) {
                        grid_y = grid_y - HEIGHT;
                    }
                    if (grid_x < 0) {
                        grid_x = grid_x + WIDTH;
                    } else if (grid_x >= WIDTH) {
                        grid_x =  grid_x - WIDTH;
                    }
                    if ( grid[grid_y][grid_x] == 1 ) {
                        neighboors++;
                    }
                }
            }
            // This could be much shorter (remove 0s, set as default), but
            // this way all rules are listed and followed cleanly
            int state;
            // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if ( grid[i][o] == 1 && neighboors < 2) {
                state = 0;
            } else 
            // Any live cell with two or three live neighbours lives on to the next generation.
            if ( grid[i][o] == 1 && ( neighboors == 2 || neighboors == 3 ) ) {
                state = 1;
            } else
            // Any live cell with more than three live neighbours dies, as if by overpopulation.
            if ( grid[i][o] == 1 && neighboors > 3 ) {
                state = 0;
            } else
            // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if ( grid[i][o] == 0 && neighboors == 3 ) {
                state = 1;
            } else {
                state = 0;
            }
            temp_grid[i][o] = state;
        }
    }
    memcpy(grid, temp_grid, sizeof(grid));
}

void loop() {
    for ( int i = 0; i < 100000; i++ ) {
        spew_grid(i);
        update_grid();

        struct timespec ts;
        ts.tv_sec = DELAY / 1000;
        ts.tv_nsec = (DELAY % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }
}


void *input_listener()
{
    while (1)
    {
        int input;
        int result = scanf("%d", &input);

        if (result == EOF)
        {
            continue;
        }
        if (result == 0)
        {
            while (fgetc(stdin) != '\n');
        }
        DELAY = input;
    }
}


int main()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int o = 0; o < WIDTH; o++)
        {
            grid[i][o] = 0;
        }
    }

    grid[1][5 + 25] = 1;
    grid[1][6 + 25] = 1;
    grid[2][4 + 25] = 1;
    grid[2][5 + 25] = 1;
    grid[2][6 + 25] = 1;
    grid[2][7 + 25] = 1;
    grid[4][3 + 25] = 1;
    grid[4][4 + 25] = 1;
    grid[4][5 + 25] = 1;
    grid[4][6 + 25] = 1;
    grid[4][7 + 25] = 1;
    grid[4][8 + 25] = 1;
    grid[5][4 + 25] = 1;
    grid[5][5 + 25] = 1;
    grid[5][6 + 25] = 1;
    grid[5][7 + 25] = 1;
    grid[7][3 + 25] = 1;
    grid[7][4 + 25] = 1;
    grid[7][7 + 25] = 1;
    grid[7][8 + 25] = 1;
    grid[8][1 + 25] = 1;
    grid[8][2 + 25] = 1;
    grid[8][4 + 25] = 1;
    grid[8][7 + 25] = 1;
    grid[8][9 + 25] = 1;
    grid[8][10 + 25] = 1;
    grid[9][4 + 25] = 1;
    grid[9][7 + 25] = 1;
    grid[12][5 + 25] = 1;
    grid[12][6 + 25] = 1;
    grid[13][5 + 25] = 1;
    grid[13][6 + 25] = 1;

    /**
        // Starter (Glider Gun)
        grid[4][0] = 1;
        grid[4][1] = 1;
        grid[5][0] = 1;
        grid[5][1] = 1;
        grid[2][13] = 1;
        grid[3][12] = 1;
        grid[3][14] = 1;
        grid[4][11] = 1;
        grid[4][15] = 1;
        grid[4][16] = 1;
        grid[5][11] = 1;
        grid[5][15] = 1;
        grid[5][16] = 1;
        grid[6][11] = 1;
        grid[6][15] = 1;
        grid[6][16] = 1;
        grid[7][12] = 1;
        grid[7][14] = 1;
        grid[8][13] = 1;
        grid[0][25] = 1;
        grid[1][22] = 1;
        grid[1][23] = 1;
        grid[1][24] = 1;
        grid[1][25] = 1;
        grid[2][21] = 1;
        grid[2][22] = 1;
        grid[2][23] = 1;
        grid[2][24] = 1;
        grid[3][21] = 1;
        grid[3][24] = 1;
        grid[4][21] = 1;
        grid[4][22] = 1;
        grid[4][23] = 1;
        grid[4][24] = 1;
        grid[5][22] = 1;
        grid[5][23] = 1;
        grid[5][24] = 1;
        grid[5][25] = 1;
        grid[6][25] = 1;
        grid[4][30] = 1;
        grid[5][30] = 1;
        grid[2][34] = 1;
        grid[2][35] = 1;
        grid[3][34] = 1;
        grid[3][35] = 1;
    **/
    pthread_t thread;
    pthread_create(&thread, NULL, input_listener, NULL);

    loop();

    pthread_join(thread, NULL);
}
