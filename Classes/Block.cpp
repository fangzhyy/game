//
//  Block.cpp
//  newgame
//
//  Created by fangzh on 15/2/25.
//
//

#include "Block.h"

Block* Block::create(Color3B cl, Size sz)
{
    Block* pBlock = new (std::nothrow)Block;
    if(pBlock && pBlock->initWithArgs(cl,sz)){
        pBlock->autorelease();
        return pBlock;
    }
    delete pBlock;
    return nullptr;
}



bool Block::initWithArgs(Color3B cl, Size sz){
    if(!Sprite::init())
        return false;
    //设置大小
    setContentSize(sz);
    //设置锚点为左下角
    setAnchorPoint(Point::ZERO);
    //设置区域
    setTextureRect(Rect(KBlockBorder, KBlockBorder, sz.width - KBlockBorder, sz.height - KBlockBorder));
    //设置颜色
    setColor(cl);
    return true;
}