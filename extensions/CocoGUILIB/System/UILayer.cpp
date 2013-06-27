/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UILayer.h"
#include "UIHelper.h"

NS_CC_EXT_BEGIN

UILayer::UILayer():
m_pRootWidget(NULL),
m_pInputManager(NULL),
m_updateEnableWidget(NULL)
//,
//m_UIType(UILAYER_SCENE)
{
    
}

UILayer::~UILayer()
{
    m_pRootWidget->removeFromParentAndCleanup(true);
    m_pRootWidget = NULL;
    m_updateEnableWidget->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_updateEnableWidget);
    CC_SAFE_DELETE(m_pInputManager);
}

bool UILayer::init()
{
    if (CCLayer::init()) {
        cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
        m_pRootWidget = CocoRootWidget::create();
        m_pRootWidget->setUILayer(this);
        addChild(m_pRootWidget->getContainerNode());
        m_pInputManager = new UIInputManager();
        m_pInputManager->setRootWidget(m_pRootWidget);
        m_updateEnableWidget = CCArray::create();
        m_updateEnableWidget->retain();
        return true;
    }
    return false;
}

UILayer* UILayer::create(void)
{
    UILayer *pRet = new UILayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void UILayer::onEnter()
{
    CCLayer::onEnter();
}

void UILayer::onExit()
{
    CCLayer::onExit();
}

void UILayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void UILayer::addWidget(CocoWidget* widget)
{
    m_pRootWidget->addChild(widget);
}

void UILayer::removeWidgetAndCleanUp(CocoWidget* widget,bool cleanup)
{
    m_pRootWidget->removeChild(widget, cleanup);
}

void UILayer::setVisible(bool visible)
{
    CCLayer::setVisible(visible);
    m_pRootWidget->setVisible(visible);
}

//void UILayer::setUIType(GUITYPE type)
//{
//    this->m_UIType = type;
//    switch (this->m_UIType) {
//        case UILAYER_SCENE:
//            this->m_pRootWidget->setPosition(CCPointZero);
//            break;
//        case UILAYER_MODEL:
//            this->m_pRootWidget->setPosition(ccp(-20, -20));
//            break;
//        default:
//            break;
//    }
//}

void UILayer::update(float dt)
{
    for (int i=0; i<m_updateEnableWidget->count(); i++)
    {
        dynamic_cast<CocoWidget*>(m_updateEnableWidget->objectAtIndex(i))->update(dt);
    }
}

void UILayer::addUpdateEnableWidget(CocoWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (this->m_updateEnableWidget->containsObject(widget))
    {
        return;
    }
    this->m_updateEnableWidget->addObject(widget);
}

void UILayer::removeUpdateEnableWidget(CocoWidget* widget)
{
    if (!widget)
    {
        return;
    }
    if (!this->m_updateEnableWidget->containsObject(widget))
    {
        return;
    }
    this->m_updateEnableWidget->removeObject(widget);
}

CocoWidget* UILayer::getWidgetByTag(int tag)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByTag(m_pRootWidget, tag);
}

CocoWidget* UILayer::getWidgetByName(const char* name)
{
    if (!m_pRootWidget)
    {
        return NULL;
    }
    return CCUIHELPER->seekWidgetByName(m_pRootWidget, name);
}

CocoRootWidget* UILayer::getRootWidget()
{
    return m_pRootWidget;
}

UIInputManager* UILayer::getInputManager()
{
    return this->m_pInputManager;
}

void UILayer::dispose()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeFromParentAndCleanup(true);
}

void UILayer::clear()
{
    this->m_pRootWidget->removeAllChildrenAndCleanUp(true);
}

bool UILayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_pInputManager && m_pInputManager->onTouchPressed(pTouch))
    {
        return true;
    }
//    CCLOG("ui layer began");
    return false;
}

void UILayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_pInputManager->onTouchMoved(pTouch);
//    CCLOG("ui layer move");
}

void UILayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_pInputManager->onTouchReleased(pTouch);
//    CCLOG("ui layer end");
}

void UILayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_pInputManager->onTouchCanceled(pTouch);
//    CCLOG("ui layer cancel");
}

NS_CC_EXT_END