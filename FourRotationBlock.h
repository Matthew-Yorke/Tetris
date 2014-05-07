#ifndef _FOUR_ROTATION_BLOCK_H
#define _FOUR_ROTATION_BLOCK_H
#include "Block.h"

class FourRotationBlock : public Block {
    private:
        int x;                           //X position
        int y;                           //Y position
        int blockArray[4][4];            //the matrix used for the block's representation
        void reassignArray(int a[4][4]); //Used for intialization of the blockArray
        void transpose();                //Transpose blockArray
        void switchRows();               //Switch rows 1and4 AND 2and3 of blockArray
        void switchColumns();            //Switch columns 1and4 AND 2and3 of blockArray
        void b_blockArray_Mult();        //Multiply a matrix B with blockArray
        void blockArray_C_Mult();        //Multiply blockArray with a matrix C
    public:
        FourRotationBlock(int i);   //Constructs the type (matrix formation) of Four Rotation Block
        void rotateRight();         //Clockwise Rotation
        void rotateLeft();          //Counterclockwise Rotation
        void moveRight();           //Move X position right
        void moveLeft();            //Move X position left
        void drop();                //Move Y position down
        void moveUp();              //Move Y position up
        int getNum(int, int);       //Obtain a number from blockArray
        int getX();                 //Returns X position
        int getY();                 //Returns Y position
        friend class Block;
};

#endif
