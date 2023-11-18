#ifndef __SELECTLAYER__H__
#define __SELECTLAYER__H__

#include <array>
#include "cocos2d.h"
#include "cocos/ui/UIScrollView.h"
#include "extensions/cocos-ext.h"
#include "sqlite3.h"
#include "GameLayer.h"
#include "Background.h"
#include "Audio.h"
#include "Tap.h"

// ステージ選択画面クラス
class SelectLayer : public cocos2d::Layer {
protected:
    int _y; // ステージ情報Y
    int _x; // ステージ情報X
    bool _buttonAnim = true;    // ボタンアニメーションフラグ
    bool _slideFlag = true;     // スライドフラグ
    cocos2d::Vec2 _onTouchPoint; // タッチした位置

    // ステージのクリア状態
    struct StageStatus {
        int _StageNumber;
        int _AreaNumber;
        int _ClearLevel;
    };

    void createBackground();    // 背景の生成
    void createScroll();        // スクロールの生成
    void onTouchStageButton(cocos2d::Touch* touch);     // ステージボタン選択時処理
    std::array<SelectLayer::StageStatus, 30> readSQL(); // DBからステージ情報取得
    virtual bool init();        // 初期化

    // シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);

public:
    static cocos2d::Scene* createScene();   // シーンの生成
    virtual void onEnter();     // レイヤー表示処理
    CREATE_FUNC(SelectLayer);   // Create関数生成マクロ
};

#endif // __SELECTLAYER__H__
