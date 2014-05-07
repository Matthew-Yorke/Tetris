#include "TwoRotationBlock.h"
#include <iostream>

//Instantiate a FourRotationBlock, meaning create either a S or Z Block
TwoRotationBlock::TwoRotationBlock(int i) {
    x = 192;
    y = 0;
    turned = false;
    //Create a S Block
    if(i == 3) {
        int blockArray1[4][4] = {{0,4,4,0},
                                 {4,4,0,0},
                                 {0,0,0,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Create a Z Block
    else if(i == 4) {
        int blockArray1[4][4] = {{5,5,0,0},
                                 {0,5,5,0},
                                 {0,0,0,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
    //Default to S Block, this should never occur
    else {
        int blockArray1[4][4] = {{0,4,4,0},
                                 {4,4,0,0},
                                 {0,0,0,0},
                                 {0,0,0,0}};
        reassignArray(blockArray1);
    }
}

//Reassign blockArray from a
void TwoRotationBlock::reassignArray(int a[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            blockArray[i][j] = a[i][j];
        }
    }
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] clockwise
void TwoRotationBlock::rotateRight() {
    //If the matrix has been rotated from original form rotate back to original form
    if(turned == true) {
        transpose();
        switchColumns();
        blockArray_C_Mult();
        turned = !turned;
    }
    //If the matrix is in the original form rotate this way
    else {
        transpose();
        switchRows();
        b_blockArray_Mult();
        turned = !turned;
    }
}

//Rotate the matrix (blockArray) around the point blockArray[1][1] clockwise
void TwoRotationBlock::rotateLeft() {
    //If the matrix has been rotated from original form rotate back to original form
    if(turned == true) {
        transpose();
        switchColumns();
        blockArray_C_Mult();
        turned = !turned;
    }
    //If the matrix is in the original form rotate this way
    else {
        transpose();
        switchRows();
        b_blockArray_Mult();
        turned = !turned;
    }
}

//When called increase the X position by 32 (image width)
void TwoRotationBlock::moveRight() {
    x += 32;
}

//When called decrease the X position by 32 (image width)
void TwoRotationBlock::moveLeft() {
    x -= 32;
}

//When called increase the Y position by 32 (image height)
void TwoRotationBlock::drop() {
    y += 32;
}

//When called decrease the Y position by 32 (image height)
void TwoRotationBlock::moveUp() {
    y -= 32;
}

//Transpose matrix (blockArray)
void TwoRotationBlock::transpose() {
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
void TwoRotationBlock::switchRows() {
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
void TwoRotationBlock::switchColumns() {
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
void TwoRotationBlock::b_blockArray_Mult() {
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
void TwoRotationBlock::blockArray_C_Mult() {
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
int TwoRotationBlock::getNum(int i, int j) {
    return blockArray[i][j];
}

//Return current X position
int TwoRotationBlock::getX() {
    return x;
}

//Return current Y position
int TwoRotationBlock::getY() {
    return y;
}
