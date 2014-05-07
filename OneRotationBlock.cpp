#include "OneRotationBlock.h"
#include <iostream>

//Instantiate a FourRotationBlock, meaning create either an I or O Block
OneRotationBlock::OneRotationBlock(int i) {
    x = 192;
    y = 0;
    //Create a I Block
    if(i == 5) {
        int blockArray1[4][4] = {{0,6,0,0},
                                 {0,6,0,0},
                                 {0,6,0,0},
                                 {0,6,0,0}};
        reassignArray(blockArray1);
    }
    //Create a O Block
    else if(i == 6) {
        int blockArray1[4][4] = {{0,0,0,0},
                                 {0,7,7,0},
                                 {0,7,7,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Default to I Block, this should never occur
    else {
        int blockArray1[4][4] = {{0,6,0,0},
                                 {0,6,0,0},
                                 {0,6,0,0},
                                 {0,6,0,0}};
        reassignArray(blockArray1);
    }
}

//Reassign blockArray from a
void OneRotationBlock::reassignArray(int a[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            blockArray[i][j] = a[i][j];
        }
    }
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] clockwise
void OneRotationBlock::rotateRight() {
    transpose();
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] clockwise
void OneRotationBlock::rotateLeft() {
    transpose();
}

//When called increase the X position by 32 (image width)
void OneRotationBlock::moveRight() {
    x += 32;
}

//When called decrease the X position by 32 (image width)
void OneRotationBlock::moveLeft() {
    x -= 32;
}

//When called increase the Y position by 32 (image height)
void OneRotationBlock::drop() {
    y += 32;
}

//When called decrease the Y position by 32 (image height)
void OneRotationBlock::moveUp() {
    y -= 32;
}

//Transpose matrix (blockArray)
void OneRotationBlock::transpose() {
    int temp = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0+i; j < 4; j++) {
            temp = blockArray[i][j];
            blockArray[i][j] = blockArray[j][i];
            blockArray[j][i] = temp;
        }
    }
}

//Retrieve number from the ith row and jth column in blockArray
int OneRotationBlock::getNum(int i, int j) {
    return blockArray[i][j];
}

//Return current X position
int OneRotationBlock::getX() {
    return x;
}

//Return current Y position
int OneRotationBlock::getY() {
    return y;
}
