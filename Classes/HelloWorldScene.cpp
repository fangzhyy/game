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
	mMoveSpeed = 5.0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	mDisplayHeight = Director::getInstance()->getVisibleSize().height;
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

void HelloWorld::moveToTopCallback(Node* block)
{
	//移动到画面顶端的时候，在尾部创建一个新的block
	const float kBottomV = -1 * mSingleBlockHeight;
	float offsetH = 0.0;
	auto blk = Block::create(Color3B(0xff,0xff,0xff), Size(mSingleBlockWidth, mSingleBlockHeight));
	blk->setPosition(Vec2(block->getPositionX(), kBottomV));
	addChild(blk);
	initBlockAction(blk);
	//继续往画面外面移动
	//需要跟之前的移动速度一样。
	const float moveDistance = mSingleBlockHeight;
	float duration = mMoveSpeed/(mDisplayHeight/moveDistance);
	int posY = block->getPositionY();
	auto act = MoveTo::create(duration, Vec2(block->getPositionX(), mDisplayHeight));
	std::function<void (Node*)> ff = std::bind(&HelloWorld::cleanCallback, this, block);
	auto callBack = CallFuncN::create(ff);
	auto seq = Sequence::create(act, callBack, NULL);
	block->runAction(seq);
}

void HelloWorld::cleanCallback(Node* block)
{
	//移动出屏幕之后清除block
	assert(block != nullptr);
	int posy = block->getPositionY();
	removeChild(block);
}

void HelloWorld::initBlockAction(Node* block)
{
	float startV = block->getPosition().y;
	float blockH = block->getPosition().x;
	float destV = mDisplayHeight - mSingleBlockHeight; 
	float distance = destV - startV;
	float duration = mMoveSpeed/(mDisplayHeight/distance);
	auto act = MoveTo::create(duration, Vec2(blockH, destV));
	std::function<void (Node*)> ff = std::bind(&HelloWorld::moveToTopCallback, this, block);
	auto callBack = CallFuncN::create(ff);
	auto seq = Sequence::create(act, callBack, NULL);
	block->runAction(seq);
	
}

void HelloWorld::initBlocks()
{
	auto director = Director::getInstance();
	Size displaySize = director->getOpenGLView()->getVisibleSize();
	mSingleBlockWidth = displaySize.width/kBlockCountInRow;
	mSingleBlockHeight = displaySize.height/kBlockCountInColumn;
	const float kBottomV = -1 * mSingleBlockHeight * kBlockCountInColumn;
	int totalCountInColumn = kBlockCountInColumn;
	float blockBottom = kBottomV;
	for(int i = 0; i < totalCountInColumn; i++){
		float offsetH = 0;
		for(int j = 0; j < kBlockCountInRow; j++){
			auto block = Block::create(Color3B(0xff, 0xff, 0xff), Size(mSingleBlockWidth, mSingleBlockHeight));
			block->setPosition(Vec2(offsetH ,blockBottom));
			offsetH += mSingleBlockWidth;
			addChild(block);
			initBlockAction(block);

		}
		blockBottom += mSingleBlockHeight;
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
