#ifndef _ONE_ROTATION_BLOCK_H
#define _ONE_ROTATION_BLOCK_H
#include "Block.h"

class OneRotationBlock : public Block {
    private:
        int x;                           //X position
        int y;                           //Y position
        int blockArray[4][4];            //the matrix used for the block's representation
        void reassignArray(int a[4][4]); //Used for intialization of the blockArray
        void transpose();                //Transpose blockArray
    public:
        OneRotationBlock(int i);
        void rotateRight();      //Clockwise Rotation
        void rotateLeft();       //Counterclockwise Rotation
        void moveRight();        //Move X position right
        void moveLeft();         //Move X position left
        void drop();             //Move Y position down
        void moveUp();           //Move Y position up
        int getNum(int, int);    //Obtain a number from blockArray
        int getX();              //Returns X position
        int getY();              //Returns Y position
        friend class Block;
};

#endif
