#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <windows.h>

using namespace std;

/* ================== UTF-8 CONSOLE SETUP ================== */
void enableUTF8() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

/* ================== ANSI COLORS ================== */
const string RED         = "\033[31m";
const string GREEN       = "\033[32m";
const string YELLOW      = "\033[33m";
const string BLUE        = "\033[34m";   // standard blue
const string BRIGHT_BLUE = "\033[94m";   // greish/light blue for walls
const string MAGENTA     = "\033[35m";
const string CYAN        = "\033[36m";
const string WHITE       = "\033[37m";
const string RESET       = "\033[0m";
/* ================== GAME RULES ================== */
void showRules() {
    system("cls");
    cout << "========= TREASURE MAZE RULES =========\n\n";
    cout << GREEN  << "🧍  Player\n" << RESET;
    cout << BLUE   << "🟦  Wall (Hit = Lose Life)\n" << RESET;
    cout << YELLOW << "💰  Gold (+10 Score)\n" << RESET;
    cout << WHITE  << "🪙  Silver (+5 Score)\n" << RESET;
    cout << CYAN   << "💎  Diamond (+20 Score)\n" << RESET;
    cout << MAGENTA<< "🚪  Exit (Finish Level)\n\n" << RESET;

    cout << "Controls:\n";
    cout << CYAN    << "↑ W = Up   "    << RESET;
    cout << MAGENTA << "↓ S = Down   "  << RESET;
    cout << YELLOW  << "← A = Left   "  << RESET;
    cout << BLUE    << "→ D = Right\n\n" << RESET;

    cout << "Lives: 3 (Game ends at 0)\n";
    cout << "======================================\n";
    cout << "Press Enter to continue...";
    cin.get();
}

/* ================== DFS MAZE CARVING ================== */
void dfsCarve(int **maze, int x, int y, int r, int c) {
    int dirs[4][2] = {{-2,0},{2,0},{0,-2},{0,2}};
    for(int i=0;i<4;i++) swap(dirs[i], dirs[rand()%4]);

    for(int i=0;i<4;i++) {
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];

        if(nx>0 && nx<r-1 && ny>0 && ny<c-1 && maze[nx][ny]==1) {
            maze[x + dirs[i][0]/2][y + dirs[i][1]/2] = 0;
            maze[nx][ny] = 0;
            dfsCarve(maze, nx, ny, r, c);
        }
    }
}

/* ================== MAZE GENERATION ================== */
void generateMaze(int **maze, int r, int c) {
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            maze[i][j] = 1;

    maze[1][1] = 0;
    dfsCarve(maze,1,1,r,c);

    maze[r-2][c-2] = 5; // Exit
    maze[r-3][c-2] = 0;
    maze[r-2][c-3] = 0;
}

/* ================== TREASURE ================== */
void placeTreasure(int **maze, int r, int c, int count) {
    int x,y;
    for(int i=0;i<count;i++) {
        do {
            x = rand()%(r-2)+1;
            y = rand()%(c-2)+1;
        } while(maze[x][y] != 0);
        int t = rand()%3 + 2; // 2=Gold,3=Silver,4=Diamond
        maze[x][y] = t;
    }
}

/* ================== RENDER MAZE ================== */
void renderMaze(int **maze, int r, int c, int px, int py) {
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++) {
            if(i==px && j==py) cout << GREEN << "🧍 " << RESET;
            else if(maze[i][j]==1) cout << BRIGHT_BLUE << "🟦 " << RESET; // updated wall color
            else if(maze[i][j]==2) cout << YELLOW << "💰 " << RESET;
            else if(maze[i][j]==3) cout << WHITE << "🪙 " << RESET;
            else if(maze[i][j]==4) cout << CYAN << "💎 " << RESET;
            else if(maze[i][j]==5) cout << MAGENTA << "🚪 " << RESET;
            else cout << "⬜ ";
        }
        cout << endl;
    }
}

/* ================== DIFFICULTY ================== */
void chooseDifficulty(int &size, int &levels) {
    int ch;
    while(true) {
        system("cls");
        cout << "===== SELECT DIFFICULTY =====\n";
        cout << "1. Easy\n2. Medium\n3. Hard\nChoice: ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(ch==1){ size=15; levels=1; break; }
        if(ch==2){ size=20; levels=2; break; }
        if(ch==3){ size=25; levels=3; break; }
    }
}

/* ================== MAIN ================== */
int main() {
    enableUTF8();
    srand(time(0));

    string player;
    cout << "HEY PLAYER::GOOD TO SEE YOU HERE! WHAT'S YOUR NAME? ";
    getline(cin, player);

    bool playAgain = true;

    while(playAgain) {
        showRules();

        int size, levels;
        chooseDifficulty(size, levels);

        int lives = 3, totalScore = 0;
        bool lost = false;

        for(int lvl=1; lvl<=levels; lvl++) {
            int **maze = new int*[size];
            for(int i=0;i<size;i++) maze[i] = new int[size];

            generateMaze(maze, size, size);
            placeTreasure(maze, size, size, 7);

            int px=1, py=1, score=0;
            char move;

            while(true) {
                system("cls");
                cout << "Player: " << player
                     << " | Score: " << totalScore + score
                     << " | Lives: " << lives
                     << " | Level: " << lvl << "\n\n";

                cout << CYAN<<"↑W "<<MAGENTA<<"↓S "<<YELLOW<<"←A "<<BLUE<<"→D\n\n"<<RESET;
                renderMaze(maze, size, size, px, py);

                cout << "\nMove: ";
                cin >> move;

                int nx=px, ny=py;
                if(move=='w'||move=='W') nx--;
                else if(move=='s'||move=='S') nx++;
                else if(move=='a'||move=='A') ny--;
                else if(move=='d'||move=='D') ny++;

                if(maze[nx][ny]==1) {
                    lives--;
                    if(lives==0){ lost=true; break; }
                } else {
                    px=nx; py=ny;
                    // Check treasure
                    if(maze[px][py]==2){ score+=10; maze[px][py]=0; }
                    if(maze[px][py]==3){ score+=5; maze[px][py]=0; }
                    if(maze[px][py]==4){ score+=20; maze[px][py]=0; }
                    // Check exit
                    if(maze[px][py]==5){ totalScore+=score; break; }
                }
            }

            for(int i=0;i<size;i++) delete[] maze[i];
            delete[] maze;
            if(lost) break;
        }

        if(lost)
            cout << RED << "💀 GAME OVER, " << player << "!\nFinal Score: " << totalScore << RESET << endl;
        else
            cout << GREEN << "🏆 YOU WON, " << player << "!\nFinal Score: " << totalScore << RESET << endl;

        char ch;
        cout << "\nPlay again? (Y/N): ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        playAgain = (ch=='y'||ch=='Y');
    }

    cout << "\nThanks for playing!\n"<<player<<", see you next time!\n";
    return 0;
}
