#include "FourRotationBlock.h"
#include <iostream>

//Instantiate a FourRotationBlock, meaning create either a L, J or T Block
FourRotationBlock::FourRotationBlock(int i) {
    x = 192;
    y = 0;
    //Create a L Block
    if(i == 0) {
        int blockArray1[4][4] = {{0,1,0,0},
                                 {0,1,0,0},
                                 {0,1,1,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Create a J Block
    else if(i == 1) {
        int blockArray1[4][4] = {{0,2,0,0},
                                 {0,2,0,0},
                                 {2,2,0,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Create a T Block
    else if(i == 2) {
        int blockArray1[4][4] = {{0,0,0,0},
                                 {3,3,3,0},
                                 {0,3,0,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Default to L Block, this should never occr
    else {
        int blockArray1[4][4] = {{0,1,0,0},
                                 {0,1,0,0},
                                 {0,1,1,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
}

//Reassign the main matrix (blockArray) from a
void FourRotationBlock::reassignArray(int a[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            blockArray[i][j] = a[i][j];
        }
    }
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] clockwise
void FourRotationBlock::rotateRight() {
    transpose();
    switchColumns();
    blockArray_C_Mult();
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] counterclockwise
void FourRotationBlock::rotateLeft() {
    transpose();
    switchRows();
    b_blockArray_Mult();
}

//When called increase the X position by 32 (image width)
void FourRotationBlock::moveRight() {
    x += 32;
}

//When called decrease the X position by 32 (image width)
void FourRotationBlock::moveLeft() {
    x -= 32;
}

//When called increase the Y position by 32 (image height)
void FourRotationBlock::drop() {
    y += 32;
}

//When called decrease the Y position by 32 (image height)
void FourRotationBlock::moveUp() {
    y -= 32;
}

//Transpose matrix (blockArray)
void FourRotationBlock::transpose() {
    int temp = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0+i; j < 4; j++) {
            temp = blockArray[i][j];
            blockArray[i][j] = blockArray[j][i];
            blockArray[j][i] = temp;
        }
    }
}

//Switch rows 1and4 AND 2and3 of blockArray
void FourRotationBlock::switchRows() {
    int row[4];

    //Switch rows 1 and 4
    for(int i = 0; i < 4; i++) {
        row[i] = blockArray[0][i];
        blockArray[0][i] = blockArray[3][i];
    }
    for(int i = 0; i < 4; i++) {
        blockArray[3][i] = row[i];
    }

    //Switch rows 2 and 3
    for(int i = 0; i < 4; i++) {
        row[i] = blockArray[1][i];
        blockArray[1][i] = blockArray[2][i];
    }
    for(int i = 0; i < 4; i++) {
        blockArray[2][i] = row[i];
    }
}

//Switch columns 1and4 AND 2and3 of blockArray
void FourRotationBlock::switchColumns() {
    int columns[4];

    //Switch columns 1 and 4
    for(int i = 0; i < 4; i++) {
        columns[i] = blockArray[i][0];
        blockArray[i][0] = blockArray[i][3];
    }
    for(int i = 0; i < 4; i++) {
        blockArray[i][3] = columns[i];
    }

    //Switch columns 2 and 3
    for(int i = 0; i < 4; i++) {
        columns[i] = blockArray[i][1];
        blockArray[i][1] = blockArray[i][2];
    }
    for(int i = 0; i < 4; i++) {
        blockArray[i][2] = columns[i];
    }
}

//Multiply matrix (B) with matrix (blockArray)
void FourRotationBlock::b_blockArray_Mult() {
    int B[4][4] = {{0,1,0,0},
                   {0,0,1,0},
                   {0,0,0,1},
                   {0,0,0,0}};
    int D[4][4];

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int sum = 0;
            for(int k = 0; k < 4; k++) {
                sum += B[i][k] * blockArray[k][j];
                D[i][j] = sum;
            }
        }
    }
    reassignArray(D);
}

//Multiply matrix (blockArray) with matrix (C)
void FourRotationBlock::blockArray_C_Mult() {
    int C[4][4] = {{0,0,0,0},
                   {1,0,0,0},
                   {0,1,0,0},
                   {0,0,1,0}};
    int D[4][4];

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            int sum = 0;
            for(int k = 0; k < 4; k++) {
                sum += blockArray[i][k] * C[k][j];
                D[i][j] = sum;
            }
        }
    }
    reassignArray(D);
}

//Retrieve number from the ith row and jth column in blockArray
int FourRotationBlock::getNum(int i, int j) {
    return blockArray[i][j];
}

//Return current X position
int FourRotationBlock::getX() {
    return x;
}

//Return current Y position
int FourRotationBlock::getY() {
    return y;
}
