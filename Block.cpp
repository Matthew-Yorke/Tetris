#include "Block.h"
#include "FourRotationBlock.h"
#include "TwoRotationBlock.h"
#include "OneRotationBlock.h"

//Based on the input the type of block that is created will be created here
Block* Block::create(int i) {
    //Four rotational Piece (L, J, and T Block)
    if(i >= 0 && i <= 2) {
        return new FourRotationBlock(i);
    }
    //Two rotational Piece (S and Z Block)
    if(i >= 3 && i <= 4) {
        return new TwoRotationBlock(i);
    }
    //One rotational Piece (I and O Block)
    if(i >= 5 && i <= 6) {
        return new OneRotationBlock(i);
    }
    return 0;
}
