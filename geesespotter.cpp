#include "geesespotter_lib.h"
#include "geesespotter.h"
#include <iostream>
/*
int main();

int main(){
    // createBoard(5, 5);
    // std::cout << char('1' + 1) << std::endl;
    // std::cout << '8' - '0' << std::endl;
    std::size_t xdim = 8;
    std::size_t ydim = 8;
    char *board = createBoard(xdim, ydim);
    // board[0] = 0x09;
    // board[1] = 0x09;
    // board[2] = 0x09;
    // board[3] = 0x09;
    // board[4] = 0x09;
    // board[6] = 0x09;
    // board[8] = 0x09;
    // board[9] = 0x09;
    // board[10] = 0x09;
    // board[11] = 0x09;
    computeNeighbors(board, xdim, ydim );
    // printBoard(board, xdim, ydim);
    // hideBoard(board, xdim, ydim);
    // mark(board, xdim, ydim, 2, 2);
    // printBoard(board, xdim, ydim);

    // int x = reveal(board, xdim, ydim, 0, 0);
    // printBoard(board, xdim, ydim);
    int y = reveal(board, xdim, ydim, 4, 4);
    printBoard(board, xdim, ydim);
    std::cout << isGameWon(board, xdim, ydim) << std::endl;

    // std::cout << std::endl;
    // std::cout << "The 10th index: " << int(board[10]) << std::endl;

    // mark(board, xdim, ydim, 2, 2);
    // printBoard(board, xdim, ydim);
    // std::cout << std::endl;
    // std::cout << "The 10th index: " << int(board[10]) << std::endl;

    // int n = reveal(board, xdim, ydim, 2, 2);
    // printBoard(board, xdim, ydim);

    // std::cout << std::endl;
    // std::cout << n << std::endl;
    // std::cout << "The 10th index: " << int(board[10]) << std::endl;
    // std::cout << (0x20 & 0x20) << "=" << 0x20 << std::endl;
    
    return 0;
}*/

char *createBoard(std::size_t xdim, std::size_t ydim){

    std::size_t capacity = xdim*ydim;

    char *my_array = new char[capacity];

    for (std::size_t i = 0; i < capacity; ++i){
        my_array[i] = 0;
    }

    return my_array;
}

void check_change(char*board, std::size_t xdim, std::size_t ydim, std::size_t c_xdim, std::size_t c_ydim);

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){

    //find all 9s
    for(std::size_t i  = 0; i < (xdim*ydim); i++){
        //for each nine, compute its neighbors
        if((board[i]&0x09) == 0x09){
        //find the current x & y
        std::size_t current_x = i%xdim;
        std::size_t current_y = i/xdim;
        //locate all the neighbor of 9s
        //for each neighbour, do an algorithm to check and change
        check_change(board, xdim, ydim, current_x, current_y-1);
        check_change(board, xdim, ydim, current_x-1, current_y-1);
        check_change(board, xdim, ydim, current_x+1, current_y-1);

        check_change(board, xdim, ydim, current_x-1, current_y);
        check_change(board, xdim, ydim, current_x+1, current_y);

        check_change(board, xdim, ydim, current_x, current_y+1);
        check_change(board, xdim, ydim, current_x-1, current_y+1);
        check_change(board, xdim, ydim, current_x+1, current_y+1);
                
        }
    }
        
    

}

void check_change(char*board, std::size_t xdim, std::size_t ydim, std::size_t c_xdim, std::size_t c_ydim){
    //check if  0 <= c_xdim < xdim
    //and check if  0 <= c_ydim < ydim
    if((c_xdim >= 0)&&(c_xdim < xdim)&&(c_ydim >= 0)&&(c_ydim < ydim)){
        //if so, 
        //compute the current index and find if current value < 0x08
        std::size_t i = c_ydim*xdim + c_xdim;
        if(board[i] < 0x08){
            //if so, current value += 0x01
            // std::cout << "current x is: " << c_xdim << " current y is: " << c_ydim << std::endl;
            // std::cout << "current value is" << int(board[i]) << std::endl;
            board[i] += 0x01;
            // std::cout << "after value is" << int(board[i]) << std::endl;
        }
    }

}


void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(std::size_t i = 0; i < xdim*ydim; ++i ){
        board[i]|= 0x20;
    }
}

void cleanBoard(char *board){
    delete[] board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim){
    for(std::size_t i = 0; i < ydim;++i){
      for(std::size_t j = 0; j < xdim; ++j){
          char current = board[i*xdim + j];
        //   std ::cout << "index num: " << i*xdim + j << " == >" << int(current);
        //marked
        if((current & 0x10) > 0){
            std::cout << "M";
        }else if((current & 0x20) > 0){
            std::cout << "*";
        }
        else{
            // & 0x0F
            std::cout << int(current);
        }
        //   std::cout << std::endl;

      }
      std::cout << std::endl;  
    }
}

void check_change_reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t c_x, std::size_t y_x);

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    char current = board[yloc * xdim + xloc];
    //if marked, return 1
    if( (current & 0x10) > 0){
        return 1;
    }
    // if it is already revealed, return 2
    else if((current & 0x20) != 0x20){
        return 2;
    }
    //if it is a goose, return 9
    else if((current & 0x09) == 0x09){
        board[yloc * xdim + xloc] = board[yloc * xdim + xloc] & 0x0F;
        return 9;
    }else{
        // std::cout << "reveal is working" << std::endl;
        board[yloc * xdim + xloc] = board[yloc * xdim + xloc] & 0x0F;
        if(board[yloc * xdim + xloc] == 0x00){
            std::size_t i = yloc * xdim + xloc;
            check_change_reveal(board, xdim, ydim, xloc-1, yloc-1);
            check_change_reveal(board, xdim, ydim, xloc, yloc-1);
            check_change_reveal(board, xdim, ydim, xloc+1, yloc-1);

            check_change_reveal(board, xdim, ydim, xloc-1, yloc);
            check_change_reveal(board, xdim, ydim, xloc+1, yloc);

            check_change_reveal(board, xdim, ydim, xloc-1, yloc+1);
            check_change_reveal(board, xdim, ydim, xloc, yloc+1);
            check_change_reveal(board, xdim, ydim, xloc+1, yloc+1);
            
        }
    }
    
    return 0;
}

void check_change_reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t c_xdim, std::size_t c_ydim){
    //check if 0 <= c_x < xdim, 0 <= c_y < ydim
    if((c_xdim >= 0)&&(c_xdim < xdim)&&(c_ydim >= 0)&&(c_ydim < ydim)){
        // std::cout << "I reached here !" << std::endl;
        //if so, check if the place is a goose
        std::size_t index = c_ydim * xdim + c_xdim;
        if((board[index] & 0x0F) != 0x09){
            //if not, board[index] &= 0x0F 
            // std::cout << "index:" << index <<std::endl;
            // std::cout << "beofre: "<< int(board[index]) << std::endl;
            board[index] = board[index]&0x0F;
            // std::cout << "adtter: "<< int(board[index]) << std::endl;
        }

    }
        

}

int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,
std::size_t yloc){
    char current = board[yloc * xdim + xloc];
    if( (current >= 0x00) && (current < 0x10)){
        // std::cout << "already revealed" << std::endl;
        // std::cout << "The index is: " << yloc * xdim + xloc << " current value is: " << board[yloc * xdim + xloc] << std::endl;
        return 2;
    }else if((current >= 0x30)&&(current < 0x40)){
        // std::cout << "already marked" << std::endl;
        board[yloc * xdim + xloc] -= 0x10;
    }else{
        // std::cout << "Marking now" << std::endl;
        board[yloc * xdim + xloc] += 0x10;
    }

    return 0;
}

bool isGameWon(char *board, std::size_t xdim, std::size_t ydim){
    std::size_t capacity = xdim*ydim;
    for(std::size_t i = 0; i < capacity; i++){
        //if not a goose
        if ((board[i] & 0x0F) != 0x09){
            // std::cout << "index " << i <<" passed here!" <<std::endl;
            //if hidden or marked, return false
            if (((board[i] & 0x20) > 0) || ((board[i] & 0x10) > 0)){
                return false;
            }
        }
            
    }
    return true;
}