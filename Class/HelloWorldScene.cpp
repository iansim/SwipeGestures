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
    auto bg = cocos2d::LayerColor::create(Color4B(135, 206, 250, 255));
    this->addChild(bg);
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
    
    auto cclogo = Sprite::create("HelloWorld.png");
    //cclogo->setPosition(Point(visibleSize.width/2, visibleSize.height /2));
    cclogo->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(cclogo, 2);
    cclogo->setName("cclogo"); //set a tag to access it globaly

    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    
    this->scheduleUpdate();
    
    return true;
}


void HelloWorld::update(float dt)
{
    if (true == isTouchDown)
    {
        auto icoTouch = Sprite::create("touch.png");
        icoTouch->setPosition(Point(currentTouchPos[0], currentTouchPos[1]));
        this->addChild(icoTouch,1);
        icoTouch->setTag(25);
        
        FadeOut* fadeOut = FadeOut::create(0.5f);
        
        auto removeIt = CallFunc::create([icoTouch]() {
            icoTouch->removeFromParent();
        });
        
        icoTouch->runAction(Sequence::create(fadeOut, removeIt, nullptr));
        auto deltaX = initialTouchPos[0] - currentTouchPos[0];
        auto deltaY = initialTouchPos[1] - currentTouchPos[1];
        
        if (std::abs(deltaX)>std::abs(deltaY)&&deltaX>0)
        {
            CCLOG("SWIPED LEFT");
            MoveBy *move_down = MoveBy::create(2, Point(currentTouchPos[0] -initialTouchPos[0],  currentTouchPos[1]-initialTouchPos[1]));  // create move up action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
            
        }
        else if (std::abs(deltaX)>std::abs(deltaY)&&deltaX<0)
        {
            CCLOG("SWIPED RIGHT");
            MoveBy *move_down = MoveBy::create(2, Point(currentTouchPos[0] -initialTouchPos[0],  currentTouchPos[1]-initialTouchPos[1]));  // create move up action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
            
        }
        else if (std::abs(deltaX)<std::abs(deltaY)&&deltaY>0)
        {
            CCLOG("SWIPED DOWN");
            MoveBy *move_down = MoveBy::create(2, Point(currentTouchPos[0] -initialTouchPos[0],  currentTouchPos[1]-initialTouchPos[1]));  // create move up action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
            
        }
        else if (std::abs(deltaX)<std::abs(deltaY)&&deltaY<0)
        {
            CCLOG("SWIPED UP");
            MoveBy *move_down = MoveBy::create(2, Point(currentTouchPos[0] -initialTouchPos[0],  currentTouchPos[1]-initialTouchPos[1]));  // create move up action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
        }
        
    }
    
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    CCLOG("onTouchBegan ID: %d, X: %f, Y: %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
