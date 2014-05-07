#ifndef _BLOCK_H
#define _BLOCK_H

//Block class used for static factory pattern to create blocks
class Block {
    public:
        virtual void rotateRight() = 0;   //Clockwise Rotation
        virtual void rotateLeft() = 0;    //Counterclockwise Rotation
        virtual void moveRight() = 0;     //Move block x position Right
        virtual void moveLeft() = 0;      //Move block x position Left
        virtual void drop() = 0;          //Drops block y position
        virtual void moveUp() = 0;        //Raise the block y position
        virtual int getNum(int, int) = 0; //Get number from block's matrix
        virtual int getX() = 0;           //Get blocks x position
        virtual int getY() = 0;           //Get blocks y position
        static Block* create(int i);      //Used for factory pattern to create block
};

#endif
