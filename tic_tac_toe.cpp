#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#define ff(i,a,b) for(int i=a; i<b; i++)
#define PLAYER 0
#define COMPUTER 1
#define TIME 2
using namespace std;

char board[3][3]; // Declaration of board

void startGame(){
  system("clear");

  ff(i,0,3){
    ff(j,0,3){
      board[i][j]=' ';
    }
  }

    printf("\t\t\t  Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below"
            " and play\n\n");

    printf("\t\t\t  1 | 2  | 3  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  4 | 5  | 6  \n");
    printf("\t\t\t--------------\n");
    printf("\t\t\t  7 | 8  | 9  \n\n");
    printf("Press 'r' to reset the game\n\n");
    printf("Press 'e' to exit the game\n\n");

    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

}

// Check whether any cell in board is empty or not
bool isEmpty(){
  ff(i,0,3){
    ff(j,0,3){
      if(board[i][j]==' ') return true;
    }
  }
  return false;
}


void showBoard(){

  system("clear");

    printf("\t\t\t  Tic-Tac-Toe\n\n");
    printf("Choose a cell numbered from 1 to 9 as below"
            " and play\n\n");

    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("Press 'r' to reset the game\n\n");
    printf("Press 'e' to exit the game\n\n");

    printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

}

int evaluate(){
  // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] &&
            board[row][1]==board[row][2])
        {
            if (board[row][0]=='X')
                return +10;
            else if (board[row][0]=='O')
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] &&
            board[1][col]==board[2][col])
        {
            if (board[0][col]=='X')
                return +10;

            else if (board[0][col]=='O')
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]=='X')
            return +10;
        else if (board[0][0]=='O')
            return -10;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]=='X')
            return +10;
        else if (board[0][2]=='O')
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}


int minimax(int depth, bool isComputer){
  int score = evaluate();

  if(score==10) return score-depth;
  if(score==-10) return score+depth;

  if(!isEmpty()) return 0;

  if(isComputer){
    int best=-100;
    ff(i,0,3){
      ff(j,0,3){
        if(board[i][j]==' '){
          board[i][j]='X';
          best = max(best, minimax(depth+1, false));
          board[i][j]=' ';
        }
      }
    }
    return best;
  }
  else{
    int best=100;
    ff(i,0,3){
      ff(j,0,3){
        if(board[i][j]==' '){
          board[i][j]='O';
          best = min(best, minimax(depth+1, true));
          board[i][j]=' ';
        }
      }
    }
    return best;
  }
}

void updateBoardComputer(){
  int bestVal=-100, posi=-1, posj=-1;

  ff(i,0,3){
    ff(j,0,3){
      if(board[i][j]==' '){
        board[i][j]='X';
        int moveVal = minimax(0,false);
        board[i][j]=' ';
        if(moveVal>bestVal){
          bestVal=moveVal;
          posi=i; posj=j;
        }
      }
    }
  }
  board[posi][posj]='X';
  showBoard();
}

bool updateBoardPlayer(char c){
  int posi=(c-'1')/3, posj=(c-'1')%3;
  if((c>='0'&&c<='9')&&board[posi][posj]==' ') board[posi][posj]='O';
  else{
    printf("\t\t\tPlease make a valid move\n\n");
    return true;
  }
  showBoard();
  return false;
}

void winner(int state){
  sleep(TIME);
  system("clear");

  printf("\t\t\t  Tic-Tac-Toe\n\n");

  switch(state){
    case 0:
      printf("\t\t Hurray! You Won.\n\n");
      break;
    case 1:
      printf("\t\t HeeHee! Better luck next time\n\n");
      break;
    case 2:
      printf("\t\t\t Its a tie\n\n");
      break;
  }
}

bool playgame(){

  // Show instructions to play the game
  startGame();

  char c; // Input from player from 0-9, 'r' or 'e'
   while(isEmpty()){
     cin>>c;

     // Reset game
     if(c=='r'){
       return true;
     }

     //Exit game
     else if(c=='e') return false;

     // Update the board after player's turn
     bool invalidMove = updateBoardPlayer(c);

    // if its an invalid move
     if(invalidMove){
       sleep(TIME);
       showBoard();
       continue;
     }

     if(evaluate()==-10){
      winner(0); // 0->player wins
      return false;
    }
     else if(!isEmpty()){
       winner(2); // 2->tie
      return false;
     }

     // Pause the program for computer's turn
     sleep(TIME);

     //Update the board after computer's turn
     updateBoardComputer();
     if(evaluate()==10){
       winner(1); // 1->computer wins
       return false;
     }
   }
   winner(2);
   return false;
}

int main(){
  bool reset =  playgame();
  while(reset) reset = playgame();


  return 0;
}
