#include <iostream>
#include <string>
#include "Colored.h"
#include "FileHandeling.h"
#include "UtilsIO.h"

using namespace std;

const int SCALE_DEFAULT = 11;
const int BOARD_SIZE = 3;


void printBoard(char** board,Colored &board_color, Colored &x_color, Colored &o_color, int scale = SCALE_DEFAULT) {
    const char* TL = "┌";
    const char* TM = "┬";
    const char* TR = "┐";
    const char* ML = "├";
    const char* MM = "┼";
    const char* MR = "┤";
    const char* BL = "└";
    const char* BM = "┴";
    const char* BR = "┘";
    const char* V  = "│";
    const char* H  = "─";
    // Top border
    board_color.print(TL);
    for(int j = 0; j < BOARD_SIZE; j++) {
        for(int s = 0; s < (scale+1)*2+1; s++) board_color.print(H);
        if (j < BOARD_SIZE - 1) board_color.print(TM);
    }
    board_color.println(TR,board_color.reset());

    // Middle rows
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int s = 0; s < scale; s++) {
            board_color.print(V);
            for(int j = 0; j < BOARD_SIZE; j++) {
                for(int sp = 0; sp < (scale+1)*2+1; sp++) {
                    char cell = board[BOARD_SIZE - i - 1][j];
                    if (cell == 'X'){
                        if (s == sp/2 || s == sp/2 -1)
                            x_color.print("𜹱");
                        else if (s == ((scale+1)) - sp/2 -1 || s == ((scale+1)) - sp/2 -2)
                            x_color.print("𜹢");
                        else
                            x_color.print(" ");
                        x_color.print(x_color.reset());
                    }
                    else if (cell == 'O') {
                        int size = (scale + 1) * 2 + 1;
                        int centerX = size / 2;
                        int centerY = scale / 2;
                        int dx = sp - centerX;
                        int dy = s - centerY;
                        int rx = centerX; 
                        int ry = centerY; 

                        // Ellipse formula (thickness 0.5)
                        double val = (dx*dx)/(double)(rx*rx) + (dy*dy)/(double)(ry*ry);
                        if(val >= 0.8 && val <= 1.2)
                            if ( ( (sp < centerX) && (s < centerY) ) || ( (sp > centerX) && (s > centerY) ) )
                                o_color.print("𜹢"); 
                            else
                                 o_color.print("𜹱"); 
                        else
                            o_color.print(" ");
                        o_color.print(o_color.reset());
                    }    
                    else {
                        board_color.print(" ");
                    }
                }
                board_color.print(V);
            }
            board_color.println(board_color.reset());
        }
        if (i < BOARD_SIZE - 1) {
            board_color.print(ML);
            for(int j = 0; j < BOARD_SIZE; j++) {
                for(int s = 0; s < (scale+1)*2+1; s++) board_color.print(H);
                if (j < BOARD_SIZE - 1) board_color.print(MM);
            }
            board_color.println(MR,board_color.reset());
        }
    }
    // Bottom border
    board_color.print(BL);
    for(int j = 0; j < BOARD_SIZE; j++) {
        for(int s = 0; s < (scale+1)*2+1; s++) board_color.print(H);
        if (j < BOARD_SIZE - 1) board_color.print(BM);
    }
    board_color.println(BR,board_color.reset());
}

enum class GameState : int{
    Tied = 2,
    Won = 1,
    OnGoing = 0
};

GameState game_state(char** board) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return GameState::Won;
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return GameState::Won;
    }
    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return GameState::Won;
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return GameState::Won;

    // Check for tie or ongoing game
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') return GameState::OnGoing; 
        }
    }
    return GameState::Tied; 
}

int main() {
    char **game_board = new char*[BOARD_SIZE];
    Colored board_color = Colored(Foreground::BRIGHT_CYAN, Background::BLACK, Attribute::BOLD);
    Colored x_color = Colored(Foreground::BRIGHT_RED, Background::BLACK, Attribute::BOLD);
    Colored o_color = Colored(Foreground::BRIGHT_GREEN, Background::BLACK, Attribute::BOLD);
    Colored prompt_color = Colored(Foreground::YELLOW, Background::BLACK, Attribute::BOLD);
    FileHandeling file;
    string filename = "save.txt";
    string saved_game = "";

    if(file.readFromFile(filename,saved_game)){
        prompt_color.println("Game Loaded! Do you want to play the saved game(y/n)?"); 
    } else {
        prompt_color.println("Could not Load The Game! press any key to continue...");
        saved_game = "NSave\nX\n \n \n \n \n \n \n \n \n \n";
    }
    prompt_color.print(prompt_color.reset());
    char choice = getch();

    bool saved = false;
    if(choice == 'y'){
        saved = saved_game.substr(0,5).compare("Saved") == 0;
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        game_board[i] = new char[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (saved) {
                game_board[i][j] = saved_game[8+(i*BOARD_SIZE + j)*2];
            } else {
                game_board[i][j] = ' ';
            }
        }
    }

    bool game_over = false;
    char turn = 'X';
    if (saved){
        turn  = saved_game[6];
    }
    while (!game_over) {

        for(int r = 0; r < 3;r++){ // to refresh the board display and avoid messing up the background 
            system("clear");
            board_color.print(board_color.bg_reset());
            board_color.println("Tic-Tac-Toe Game (Press 'q' to quit)");
            printBoard(game_board, board_color, x_color, o_color);
        }

        GameState gs = game_state(game_board);
        game_over = static_cast<int>(gs) > 0;

        if (game_over) {

            string winner = turn == 'X' ? "O" : "X";

            if (gs == GameState::Won){
                prompt_color.println(winner," was the winner");
            }
            else if (gs == GameState::Tied){
                prompt_color.println("Game ended in a tie");
            }

            prompt_color.print(prompt_color.reset());
            continue;
        }

        char cell = getch();

        if (cell == 'q') {
            string game = "Saved\n";
            game.push_back(turn);
            game += "\n";

            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    game.push_back(game_board[i][j]);
                    game += "\n";
                }
            }

            if(file.saveToFile(filename,game)){
                prompt_color.println("Game Saved! press any key to continue..."); 
            } else {
                prompt_color.println("Game not Saved! press any key to continue...");
            }

            prompt_color.print(prompt_color.reset());
            getch();
            break;
        } else {
            string input = "";

            if (cell < '1' || cell > '9') {
                prompt_color.println("Invalid move! press any key to continue...");
                prompt_color.print(prompt_color.reset());
                getch();
                continue;
            }

            input += cell;
            int num = stoi(input);
            int row = (num - 1) / BOARD_SIZE;
            int col = (num - 1) % BOARD_SIZE;

            if (num >= 1 && num <= 9 && game_board[row][col] == ' ') {
                if (turn == 'O') {
                    game_board[row][col] = 'O';
                    turn = 'X';
                } else if (turn == 'X') {
                    game_board[row][col] = 'X';
                    turn = 'O';
                }
            } else {
                prompt_color.println("Invalid move! press any key to continue...");
                prompt_color.print(prompt_color.reset());
                getch();
            }
        }
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        delete[] game_board[i];
    }
    delete[] game_board;
    return 0;
}