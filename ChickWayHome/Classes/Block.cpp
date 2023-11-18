#include "Block.h"

USING_NS_CC;

using namespace Common;

// シーン生成
Block* Block::create(BlockType pm_Type) {
    Block* w_pRet = new Block();
    if (w_pRet && w_pRet->init(pm_Type)) {
        w_pRet->autorelease();
        return w_pRet;
    } else {
        delete w_pRet;
        w_pRet = nullptr;
        return nullptr;
    }
}

// ブロックの初期化
bool Block::init(BlockType pm_Type) {
    if (!Sprite::initWithFile(fileName(pm_Type)))
        return false;

    if (pm_Type == Goal){
        auto w_GoalText = Sprite::create("goal.png");
        w_GoalText->setPosition(Vec2(getContentSize().width / 2, getContentSize().height - 5));
        auto w_MoveUp = MoveBy::create(1, Vec2(0, 10));
        auto w_MoveDown = MoveBy::create(1, Vec2(0, -10));
        auto w_Seq = Sequence::create(w_MoveUp, w_MoveDown, nullptr);
        auto w_Repeat = RepeatForever::create(w_Seq);
        w_GoalText->runAction(w_Repeat);
        addChild(w_GoalText , Z_Goal);
    }

    if (!setPhyscs(pm_Type))
        return false;

    if (!setBlockTag(pm_Type))
        return false;

    setAction(pm_Type);
    
    return true;
}

// アニメーションをセット
void Block::setAction(BlockType type) {
    // 変数を宣言
    FiniteTimeAction* w_RotateOne;
    FiniteTimeAction* w_RotateTwo;
    MoveBy* w_MoveFrom;
    MoveBy* w_MoveTo;
    Sequence* w_Seq;
    RepeatForever* w_Repeat;
;
    // 動きをセット
    switch (type) {
        case Warp:
        case WarpTo:
            w_RotateOne = RotateTo::create(3.0f, 180.0f);
            w_RotateTwo = RotateTo::create(3.0f, 360.0f);
            w_Seq = Sequence::create(w_RotateOne, w_RotateTwo, nullptr);
            w_Repeat = RepeatForever::create(w_Seq);
            runAction(w_Repeat);
            break;
        case Block4:
            w_MoveFrom = MoveBy::create(3, Vec2(100, 0));
            w_MoveTo   = MoveBy::create(3, Vec2(-100, 0));
            w_Seq = Sequence::create(w_MoveFrom, w_MoveTo, nullptr);
            w_Repeat = RepeatForever::create(w_Seq);
            runAction(w_Repeat);
            break;
        case Block5:
            w_MoveFrom = MoveBy::create(3, Vec2(100, 0));
            w_MoveTo   = MoveBy::create(3, Vec2(-100, 0));
            w_Seq = Sequence::create(w_MoveFrom, w_MoveTo, nullptr);
            w_Repeat = RepeatForever::create(w_Seq);
            runAction(w_Repeat);
            break;
        case Block6:
            w_MoveFrom = MoveBy::create(3, Vec2(100, 0));
            w_MoveTo   = MoveBy::create(3, Vec2(-100, 0));
            w_Seq = Sequence::create(w_MoveFrom, w_MoveTo, nullptr);
            w_Repeat = RepeatForever::create(w_Seq);
            runAction(w_Repeat);
            break;
        default: 
            break;
    }
}

// 画像のテキストを取得
std::string Block::fileName(BlockType type) {
    // 画像名を取得
    switch (type) {
        case Block1: 
        case Block4: return "block.png";
        case Block2: 
        case Block5: return "iceBlock.png";
        case Block3:
        case Block6: return "bounBlock.png";
        case Warp:   return "warp.png";
        case WarpTo: return "warpTo.png";
        case Key:    return "key.png";
        case Lock:   return "ori.png";
        case Goal:   return "chicken.png";
        default:     return "chicken.png";
    }
}

// 物理演算
bool Block::setPhyscs(BlockType pm_Type) {
    // 衝突オブジェクトオプション
    PhysicsMaterial w_Material;

    // 衝突オブジェクトのオプションを設定
    switch (pm_Type) {
        case Block1:
        case Block4:
            w_Material = PhysicsMaterial(0.0, 0.0, 3.0);
            break;
        case Block2:
        case Block5:
            w_Material = PhysicsMaterial(0.8, 0.3, 0.0);
            break;
        case Block3:
        case Block6:     
            w_Material = PhysicsMaterial(0.0, 2.0, 0.7);
            break;
        default:
            break;
    }

    // 衝突オブジェクトを設定
    PhysicsBody* w_Body;
    switch (pm_Type) {
        case Block1:
        case Block2:
        case Block3:
        case Block4:
        case Block5:
        case Block6:
        case Key:
            w_Body = PhysicsBody::createBox(getContentSize(), w_Material);
            break;
        case Lock:
            w_Body = PhysicsBody::createEdgeBox(getContentSize(), w_Material);
            break;
        case Goal:
            w_Body = createGoalBody(w_Material);
            break;
        default: 
            w_Body = nullptr;
    }

    // 物理判定がないブロックは貫通ブロックとみなす
    if (w_Body) {
        w_Body->setDynamic(false);
        w_Body->setContactTestBitmask(0x01);
        setPhysicsBody(w_Body);
    }

    return true;
}

// ブロックにタグをセット
bool Block::setBlockTag(BlockType pm_Type) {
    switch (pm_Type) {
        case Block1:
        case Block2: 
        case Block5: setTag(T_Block);  return true;
        case Block3:
        case Block6: setTag(T_Bounce); return true;
        case Warp:   setTag(T_Warp);   return true;
        case Goal:   setTag(T_Clear);  return true;
        case Key:    setTag(T_Key);    return true;
        case Lock:   setTag(T_Lock);   return true;
        default: return true;
    }

    return false;
}

// ゴールの衝突オブジェクトをセット
PhysicsBody* Block::createGoalBody(PhysicsMaterial pm_Material) {
    std::vector<Vec2>w_Vecs;
    w_Vecs.push_back(Vec2(-30, 20));
    w_Vecs.push_back(Vec2(-30, -30));
    w_Vecs.push_back(Vec2(30 , -30));
    w_Vecs.push_back(Vec2(30 , 20));

    PhysicsBody* w_Body = PhysicsBody::createPolygon(&w_Vecs[0], 4, pm_Material);

    return w_Body;
}

// ワープの宛先情報をセット
void Block::setWarpTo(Vec2 pm_WarptToPosition) {
    _WarpTo = pm_WarptToPosition;
}

// ワープの宛先情報を取得
Vec2 Block::getWarpTo() {
    return _WarpTo;
}