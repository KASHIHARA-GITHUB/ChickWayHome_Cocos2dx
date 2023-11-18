#ifndef __GAMELAYER__H__
#define __GAMELAYER__H__

#include "cocos2d.h"
#include "Common.h"
#include "SelectLayer.h"
#include "Background.h"
#include "Block.h"
#include "Ball.h"

// ゲーム画面クラス
class GameLayer : public cocos2d::Layer {
protected:
    // メンバー変数
    std::vector<Block*> _CollisionImage; // 貫通ブロック変数
    cocos2d::Vec2 _onTouchPosition;      // タッチした位置を保持
    bool          _WallCollision = true; // 衝突変数
    int           _ShotCount = 0;        // 跳躍数保持
    static int    _StageNumber;          // ステージ番号保持

    void createBackground();    // 背景の生成
    void createBlock();         // ブロックの生成
    void createBall();          // ボールの生成
    void showMenu();            // メニュー画面
    void showShotCountLabel();  // スコアラベル
    void showGameClearLabel();  // ゲームクリアラベル
    void update(float dt);      // フレーム処理
    void imageCollision();      // 画像とボール衝突時処理
    void registerSQL();         // SQLiteに登録
    void onClearButtonCallback(cocos2d::Ref* pSender); // クリアボタンコールバック関数
    void onRestartCallback(cocos2d::Ref* pSender);     // 戻るボタンコールバック関数
    void moveWarp(Vec2 pm_WarpTo);  // 宛先ワープへ移動
    virtual bool init();    //初期化

    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    //衝突イベント
    bool onContactBegin(cocos2d::PhysicsContact& contact);


public:
    static cocos2d::Scene* createScene();   //シーンの生成
    virtual void onEnter(); //レイヤー表示処理
    CREATE_FUNC(GameLayer); //Create関数生成マクロ
    static void StageNumberSet(int pm_Count); // ステージ番号をセット
};

#endif // __GAMELAYER__H__
