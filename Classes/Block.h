//
//  Block.h
//  newgame
//
//  Created by fangzh on 15/2/25.
//
//

#ifndef __newgame__Block__
#define __newgame__Block__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Block : public Sprite
{
public:
    static Block* create(Color3B cl, Size sz);
public:
    
    bool initWithArgs(Color3B cl, Size sz);
private:
    static const int KBlockBorder = 2;
            
};

#endif /* defined(__newgame__Block__) */
