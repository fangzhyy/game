#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	mMoveSpeed = 1.0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    initBlocks();
    return true;
}

void HelloWorld::moveCallback(Node* block)
{

}

void HelloWorld::cleanCallback(Node* block)
{
	removeChild(block);
}



void HelloWorld::dividScreen()
{
    Size displaySize = Director::getInstance()->getOpenGLView()->getVisibleSize();
    
}

//使用一个node来容纳整个屏幕的内容。
void HelloWorld::makeWholeBlock()
{
    
    
}

void HelloWorld::moveBlockTest()
{
    //新建一个block，放在屏幕中间下部
    auto director = Director::getInstance();
    Size displaySize = director->getOpenGLView()->getVisibleSize();
    float offsetH = displaySize.width/4.0;
    float offsetV = displaySize.height/4.0;
    auto block = Block::create(Color3B(0xff,0xff,0xff), Size(displaySize.width/4, displaySize.height/4));
    block->setPosition(Vec2(offsetH, offsetV));
    this->addChild(block);
    auto action = MoveTo::create(2, Vec2(-100,-100));
    block->runAction(action);
    // pBlock =
   // Block* pBlock = Block::initWithArgs(Color3B(0,0,0), Size(offsetH/2.0, offsetV));
}

void HelloWorld::moveMutiBlockTest()
{
    auto director = Director::getInstance();
    Size displaySize = director->getOpenGLView()->getVisibleSize();
    float singleBlockWidth = displaySize.width/4.0 - 4;
    float singleBlockHeight = displaySize.height/4.0 - 4;
    //建立16个block。
	int offsetV = singleBlockHeight * -1;
	float duration = 3;
    for(int n = 0; n <5; n++){
		for(int i = 0; i < 4; i++){
			auto block = Block::create(Color3B(0xff, 0xff, 0xff), Size(singleBlockWidth, singleBlockHeight));
			float offsetH = i * (singleBlockWidth + 2) + 2;
			block->setPosition(offsetH, offsetV);
			this->addChild(block);
			float action_duration = duration * (displaySize.height - offsetV) / displaySize.height;
			auto act = MoveTo::create(action_duration, Vec2(offsetH, displaySize.height));
			
			block->runAction(act);
			
		}
		offsetV += singleBlockHeight + 2;
    }
    
    
}

void HelloWorld::initBlockAction(Node* block)
{
	float startV = block->getPosition().y;
	float blockH = block->getPosition().x;
	float displayTop = Director::getInstance()->getVisibleSize().height;
	float distance = displayTop - startV;
	float duration = mMoveSpeed/(displayTop/distance);
	auto act = MoveTo::create(duration, Vec2(blockH, displayTop));
	//auto callBack = CallFunc::create(CC_CALLBACK_1(HelloWorld::cleanCallback, this));
	//auto seq = Sequence::create(act, callBack);
	//block->runAction(seq);
	
}

void HelloWorld::initBlocks()
{
	auto director = Director::getInstance();
	Size displaySize = director->getOpenGLView()->getVisibleSize();
	float singleBlockWidth = displaySize.width/kBlockCountInRow;
	float singleBlockHeight = displaySize.height/kBlockCountInColumn;
	const float kBottomV = -1 * singleBlockHeight;
	int totalCountInColumn = kBlockCountInColumn + 1;
	float blockBottom = kBottomV;
	for(int i = 0; i < totalCountInColumn; i++){
		float offsetH = 0;
		for(int j = 0; j < kBlockCountInRow; j++){
			auto block = Block::create(Color3B(0xff, 0xff, 0xff), Size(singleBlockWidth, singleBlockHeight));
			block->setPosition(Vec2(offsetH ,blockBottom));
			offsetH += singleBlockWidth;
			addChild(block);
			initBlockAction(block);

		}
		blockBottom += singleBlockHeight;
	}
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
