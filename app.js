'use strict';

const COMPUTER = '&times;';
const PLAYER = '&Omicron;';

var count = ['one', 'two', 'three', 'four', 'five', 'six',
            'seven', 'eight', 'nine'];

var counter=0;
var players = 1; // No of Players
var board = new Array(3); // Declaration of board

// Initialise the board
for(var i=0; i<3; i++) {
    board[i] = new Array(3);
}
for(var i=0; i<3; i++) {
    for(var j=0; j<3; j++) {
        board[i][j] = ' ';
    }
}

// No of players
function no_players(player) {
    players = player;
    startGame();
}

// Check whether any cell in board is empty or not
function isEmpty(){
  for(var i=0; i<3; i++) {
        for(var j=0; j<3; j++) {
            if(board[i][j] == ' ') return true;
        }
    }
  return false;
}

// Function to check state of game
function evaluate(){
  // Checking for Rows for X or O victory.
    for(var row = 0; row<3; row++) {
        if(board[row][0]==board[row][1] &&
            board[row][1]==board[row][2])
        {
            if(board[row][0]=='X')
                return +10;
            else if(board[row][0]=='O')
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for(var col = 0; col<3; col++) {
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

// Function to predict the possible move for computer
function minimax(depth, isComputer){
  var score = evaluate();

  if(score==10) return score-depth;
  if(score==-10) return score+depth;

  if(!isEmpty()) return 0;

  if(isComputer){
    var best=-100;
    for(var i=0; i<3; i++){
      for(var j=0; j<3; j++){
        if(board[i][j]==' '){
          board[i][j]='X';
          best = Math.max(best, minimax(depth+1, false));
          board[i][j]=' ';
        }
      }
    }
    return best;
  }
  else{
    var best=100;
    for(var i=0; i<3; i++){
      for(var j=0; j<3; j++){
        if(board[i][j]==' '){
          board[i][j]='O';
          best = Math.min(best, minimax(depth+1, true));
          board[i][j]=' ';
        }
      }
    }
    return best;
  }
}

// Update the board with computer's move
function updateBoard() {
    var bestVal=-100, posi=-1, posj=-1;

    for(var i=0; i<3; i++){
        for(var j=0; j<3; j++){
            if(board[i][j]==' '){
                board[i][j]='X';
                var moveVal = minimax(0,false);
                board[i][j]=' ';
                if(moveVal>bestVal){
                    bestVal=moveVal;
                    posi=i; posj=j;
                }
            }
        }
    }
    board[posi][posj]='X';
    document.getElementById(count[posi*3+posj]).innerHTML = COMPUTER;

}

// Update the screen with the status of game
function winner(state) {
    var final_result = '';
    switch(state) {
        case 0:
            if(players==1) final_result = 'Hurray! You Won!';
            else final_result = 'Player 1 wins!';
            break;
        case 1:
            if(players==1) final_result = 'Boo! I won!';
            else final_result = 'Player 2 wins!';
            break;
        case 2: final_result = 'It\'s a tie! Play again!'; break;
    }
    alert(final_result);
    startGame();

}

// Start Game
function startGame() {
    // Initialising the board
    for(var i=0; i<3; i++){
        for(var j=0; j<3; j++){
            board[i][j] = ' ';
            document.getElementById(count[i*3+j]).innerHTML = '-';
        }
    }
    counter=0;
}


function fun(row, col) {
    // Update the board with palyer's move
    if(board[row][col]!=' ') {
        alert('Make a valid move');
        return ;
    }

    if(counter%2) {
        board[row][col] = 'X';
        document.getElementById(count[row*3+col]).innerHTML = COMPUTER;
    }
    else {
        board[row][col] = 'O';
        document.getElementById(count[row*3+col]).innerHTML = PLAYER;
    }

    if(evaluate()==-10) {
        winner(0); //0->player wins
        return;
    }

    if(players==2 && evaluate()==10) {
        winner(1); // 1->player 2 wins
        return;
    }
    if(!isEmpty()) {
        winner(2); //2->tie
        return ;
    }

    // Update the board with computer's move
    if(players==1) {
        updateBoard();
        if(evaluate()==10) {
            winner(1); //1->computer wins
            return;
        }
    }
    if(players==2) counter++;
}
