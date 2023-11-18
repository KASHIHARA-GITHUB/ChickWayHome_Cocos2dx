#ifndef __BLOCK__H__
#define __BLOCK__H__

#include "cocos2d.h"
#include "Common.h"

using namespace Common;

// ブロッククラス
class Block : public cocos2d::Sprite
{
protected:
    cocos2d::Vec2 _WarpTo;  // ワープの宛先

    // ゴールの衝突オブジェクトをセット
    cocos2d::PhysicsBody* createGoalBody(cocos2d::PhysicsMaterial pm_Material);
    std::string fileName(BlockType pm_type);   // ファイル名取得
    bool setPhyscs(BlockType pm_type);         // 物理演算をセット
    bool setBlockTag(BlockType pm_type);       // タグをセット
    void setAction(BlockType pm_type);         // 動きをセット
    virtual bool init(BlockType pm_Type);      // 初期化

public:
    static Block* create(BlockType pm_Type);	        // インスタンス生成
    void setWarpTo(cocos2d::Vec2 pm_WarpToPosition);    // ワープの宛先位置をセット
    cocos2d::Vec2 getWarpTo();                          // ワープの宛先位置を取得
};

#endif // __BLOCK__H__
