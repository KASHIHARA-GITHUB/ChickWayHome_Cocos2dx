#ifndef __BALL__H__
#define __BALL__H__

#include "cocos2d.h"
#include "Common.h"

class Ball : public cocos2d::Sprite {
protected:
    bool setImage();        // ボールのイメージを取得
    bool setPhyscs();       // 物理演算をセット
    virtual bool init();    // 初期化
public:
    static Ball* create();	// インスタンス生成
};

#endif // __BALL__H__
