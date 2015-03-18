#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void initBlocks();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
    Vector<Block*> mBlocks;
    void initBlockAction(Node* block);
    void cleanCallback(Node* block);
    void moveToTopCallback(Node* block);
    void moveOutOfScreenCallback(Node* block);
private:
	//�����1�����ʾblock����ײ��ƶ�����Ļ���ˣ���Ҫһ���ӵ�ʱ�䡣
    float mMoveSpeed;
	float mSingleBlockHeight;
	float mSingleBlockWidth;
	int mDisplayHeight;
	static const unsigned int kBlockCountInRow = 4;
    static const unsigned int kBlockCountInColumn = 4;
};

#endif // __HELLOWORLD_SCENE_H__
