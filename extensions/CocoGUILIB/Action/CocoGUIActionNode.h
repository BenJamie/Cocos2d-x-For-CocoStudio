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

#ifndef __COCOGUIACTIONNODE_H__
#define __COCOGUIACTIONNODE_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CocoWidget.h"
#include "CocoGUIActionFrame.h"

NS_CC_EXT_BEGIN

class CocoGUIActionNode:public cocos2d::CCObject
{
protected:
	int currentIndex;
	CCSequence* m_action;
	CocoWidget* m_actionNode;
	cocos2d::CCArray* m_ActionFrameList;
public:
    CocoGUIActionNode();
    virtual ~CocoGUIActionNode();

	void SetActionNode(CocoWidget* widget);

	void AddFrame(CocoGUIActionFrame* frame);
	void DeleteFrame(CocoGUIActionFrame* frame);

	void UpdateToFrameByIndex(int index);
	void UpdateToFrame(CocoGUIActionFrame* frame);

	void RunAction(float fUnitTime, bool bloop);
	void StopAction();

};

NS_CC_EXT_END

#endif
