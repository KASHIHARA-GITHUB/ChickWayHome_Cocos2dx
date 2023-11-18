#include "Ball.h"

USING_NS_CC;
using namespace Common;

// シーン生成
Ball* Ball::create() {
    Ball* w_pRet = new Ball();
    if (w_pRet && w_pRet->init()) {
        w_pRet->autorelease();
        return w_pRet;
    } else {
        delete w_pRet;
        w_pRet = nullptr;
        return nullptr;
    }
}

// ブロックの初期化
bool Ball::init() {
    // 画像を設定
    if (!setImage())
        return false;

    // 物理演算を設定
    if (!setPhyscs())
        return false;
    
    return true;
}

// ボールの画像をセット
bool Ball::setImage() {
    // ボールの生成
    Sprite::initWithFile("ball.png");

    // 矢印の生成
    auto w_Arrow = Sprite::create("arrow.png");
    auto w_BallPos = getContentSize() / 2;
    w_Arrow->setPosition(Point(w_BallPos));
    w_Arrow->setAnchorPoint(Point::ANCHOR_MIDDLE);
    w_Arrow->setTag(T_Arrow);
    w_Arrow->setVisible(false);
    addChild(w_Arrow);

    // 足アイコンの生成
    auto w_Foot = Sprite::create("foot.png");
    w_Foot->setPosition(Point(0, getContentSize().height));
    w_Foot->setAnchorPoint(Point::ANCHOR_MIDDLE);
    w_Foot->setTag(T_Foot);
    addChild(w_Foot);

    // ばつアイコンの生成
    auto w_Cross = Sprite::create("cross.png");
    auto w_FootPos = w_Foot->getContentSize() / 2;
    w_Cross->setPosition(Point(w_FootPos));
    w_Cross->setAnchorPoint(Point::ANCHOR_MIDDLE);
    w_Cross->setTag(T_Cross);
    w_Cross->setVisible(false);
    w_Foot->addChild(w_Cross);

    return true;
}

// 物理演算
bool Ball::setPhyscs() {
    // 物質的特徴の設定
    PhysicsMaterial w_Material;
    w_Material.density = 0.8;
    w_Material.restitution = 0.5;
    w_Material.friction = 1;

    // 物理構造の設定
    auto w_Body = PhysicsBody::createCircle(getContentSize().width * 0.47, w_Material);
    w_Body->setDynamic(true);
    w_Body->setRotationEnable(false);
    w_Body->setContactTestBitmask(0x01);
    setPhysicsBody(w_Body);

    return true;
}