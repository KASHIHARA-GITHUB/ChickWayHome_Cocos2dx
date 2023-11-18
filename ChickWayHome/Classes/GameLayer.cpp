#include "GameLayer.h"

#define WINSIZE Director::getInstance()->getWinSize()
#define SOUNDDELAY 1.0f       // 音楽遅延時間
#define SHOTCOUNTLABELX -480  // ショットカウントラベル位置X
#define SHOTCOUNTLABELY 200   // ショットカウントラベル位置Y
#define SHOTCOUNTLABELSIZE 30 // ショットカウントラベルサイズ
#define BACKBUTTONX -480      // 戻るボタン位置X
#define BACKBUTTONY 250       // 戻るボタン位置Y
#define HOMEBUTTONX -330      // ホームボタン位置X
#define HOMEBUTTONY 245       // ホームボタン位置Y
#define CLEARBUTTONY -100     // クリアボタン位置Y
#define GRAVITYVECT Vect(0, -245) // 重力
#define SHOTCOUNTMAX 999      // 跳躍最大数
#define ARROWMAX 500          // 矢印最大の大きさ
#define ARROWMIN 100          // 矢印最小の大きさ
#define ARROWROTAINIT -90     // 矢印初期角度

USING_NS_CC;

using namespace Common;
using namespace CocosDenshion;

int GameLayer::_StageNumber;

//シーン生成
Scene* GameLayer::createScene() {
    auto w_Scene = Scene::createWithPhysics(); // シーンを生成する
    auto w_Layer = GameLayer::create();        // GameLayerクラスのレイヤーを生成する
    w_Scene->addChild(w_Layer);                // シーンに対してレイヤーを追加する

    return w_Scene; // シーンを返す
}

// ゲームレイヤー初期化処理
bool GameLayer::init() {
    if ( !Layer::init())
        return false;

    Director::getInstance()->getTextureCache()->removeAllTextures();

    // シングルタップイベントの取得
    auto w_TouchListener = EventListenerTouchOneByOne::create();
    w_TouchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    w_TouchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    w_TouchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    w_TouchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(w_TouchListener, this);

    // 衝突イベントの取得
    auto w_ContactListener = EventListenerPhysicsContact::create();
    w_ContactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(w_ContactListener, this);

    // オーディオを再生
    auto w_Audio = Audio::create();
    w_Audio->startAudio(S_Game, SOUNDDELAY);
    addChild(w_Audio);

    return true;
}

// レイヤー表示時処理
void GameLayer::onEnter() {
    Layer::onEnter();

    // 重力をセット
    auto w_Vect = GRAVITYVECT;
    auto w_Scene = dynamic_cast<Scene*>(this->getParent());
    w_Scene->getPhysicsWorld()->setGravity(w_Vect);

    // 物理判定デバッグ
    //w_Scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 背景の生成
    createBackground();

    // ボールの生成
    createBall();

    // ブロックの生成
    createBlock();

    // メニューを表示
    showMenu();
}

// 背景の生成
void GameLayer::createBackground() {
    // 背景の後ろ設定
    auto w_BackBehind = Background::create(L_Game);
    w_BackBehind->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    w_BackBehind->setPosition(Point(WINSIZE / 2));
    addChild(w_BackBehind, Z_BackgroundBehind);

    // 背景をセット
    auto w_Background = Background::create(L_Bg1);
    w_Background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    w_Background->setPosition(Point(WINSIZE/ 2));
    addChild(w_Background, Z_Background, T_Background);
}

// ブロックの生成
void GameLayer::createBlock() {
    // ステージ情報を取得
    std::vector<StageInfo> w_StageInfo;
    w_StageInfo = cStageInfo::getStagePos(_StageNumber);

    // ブロックを配置
    for (int i = 0; i < w_StageInfo.size(); i++) {
        auto w_Block = Block::create((BlockType)w_StageInfo[i].blockType);
        w_Block->setPosition(w_StageInfo[i].position);
        
        // ワープオブジェクトを生成時
        if (w_Block->getTag() == T_Warp) {
            // ワープ先の位置をセット
            w_Block->setWarpTo(w_StageInfo[i].warpTo);

            // フレーム処理で実行するために配列に格納
            _CollisionImage.push_back(w_Block);

            //ワープ先のオブジェクトを生成
            auto w_WarpTo = Block::create(WarpTo);
            w_WarpTo->setPosition(w_Block->getWarpTo());
            addChild(w_WarpTo, Z_Block);

        }

        // クリアオブジェクトを生成且、タグがキーであるオブジェクトが
        // 存在する場合はロックオブジェクトを生成する
        if (w_Block->getTag() == T_Clear && getChildByTag(T_Key)) {
            auto w_Lock = Block::create(Lock);
            w_Lock->setPosition(w_Block->getPosition());
            addChild(w_Lock, Z_Lock);
        }

        // ブロックをセット
        addChild(w_Block, Z_Block);
    }

    // フレーム処理を起動
    this->scheduleUpdate();
}

// フレーム処理
void GameLayer::update(float dt) {
    imageCollision();
}

// 画像当たり判定処理
void GameLayer::imageCollision() {
    // ボールを取得
    auto w_Ball = getChildByTag(T_Ball);

    // ボールオブジェクトが存在しない場合は終了
    if (w_Ball == nullptr) {
        return;
    }

    // ワープの当たり判定
    for (int i = 0; i < _CollisionImage.size(); i++) {
        //if (_CollisionImage[i]->getBoundingBox().intersectsRect(w_Ball->getBoundingBox()) &&
        if (_CollisionImage[i]->getBoundingBox().intersectsCircle(w_Ball->getPosition(),1.0f) &&
            _CollisionImage[i]->getTag() == T_Warp) {
            // ボールをワープ先へ移動
            moveWarp(_CollisionImage[i]->getWarpTo());
        }
    }
}

// ボールをワープ先へ移動
void GameLayer::moveWarp(Vec2 pm_WarpTo) {
    // ボールをワープ先の位置へ移動
    auto w_Ball = getChildByTag(T_Ball);
    w_Ball->setPosition(pm_WarpTo);
}

//ボールの生成
void GameLayer::createBall() {
    // ボールをセット
    auto w_Ball = Ball::create();
    w_Ball->setPosition(cBallPos::getBallPos(_StageNumber));
    addChild(w_Ball, Z_Ball, T_Ball);
}

//メニューを表示
void GameLayer::showMenu() {
    // 背景の位置を取得
    auto w_Background = getChildByTag(T_Background);
    float w_BgPosX = w_Background->getPosition().x;
    float w_BgPosY = w_Background->getPosition().y;

    //メニュー画面へ戻るボタンボタン表示
    auto w_MenuBackButton = (MenuItemImage*)getChildByTag(T_MenuBack);
    if (!w_MenuBackButton) {
        auto w_BeforeButton = "home_be.png";
        auto w_AfterButton = "home_af.png";

        w_MenuBackButton = MenuItemImage::create(
            w_BeforeButton,
            w_AfterButton,
            CC_CALLBACK_1(GameLayer::onClearButtonCallback, this)
        );
        w_MenuBackButton->setAnchorPoint(Point::ANCHOR_MIDDLE);

        Menu* w_Menu = Menu::create(w_MenuBackButton, NULL);
        w_Menu->setPosition(w_BgPosX + BACKBUTTONX, WINSIZE.height / 2 + BACKBUTTONY);
        addChild(w_Menu, Z_Button);
    }

    //ゲームを戻すボタン表示
    auto w_RestartButton = (MenuItemImage*)getChildByTag(T_MenuRestart);
    if (!w_RestartButton) {
        auto w_BeforeButton = "back_be.png";
        auto w_AfterButton = "back_af.png";

        w_RestartButton = MenuItemImage::create(
            w_BeforeButton,
            w_AfterButton,
            CC_CALLBACK_1(GameLayer::onRestartCallback, this)
        );
        w_RestartButton->setAnchorPoint(Point::ANCHOR_MIDDLE);

        Menu* w_Menu = Menu::create(w_RestartButton, NULL);
        w_Menu->setPosition(w_BgPosX + HOMEBUTTONX, WINSIZE.height / 2 + HOMEBUTTONY);
        addChild(w_Menu, Z_Button);
    }

    //ショットカウントを表示
    showShotCountLabel();
}

// ショットカウントラベルの参照
void GameLayer::showShotCountLabel() {
    // ショットカウントを加算
    _ShotCount++;

    // ショットカウントラベルの取得
    auto w_Score = (Label*)getChildByTag(T_ShotCountLabel);
    if (!w_Score) {
        // 背景の位置を取得
        auto w_Background = getChildByTag(T_Background);
        float w_BgPosX = w_Background->getPosition().x;
        float w_BgPosY = w_Background->getPosition().y;

        // ショットカウントラベルの生成
        w_Score = Label::createWithTTF("", cText::getFont(F_Google), SHOTCOUNTLABELSIZE);
        w_Score->setPosition(Point(w_BgPosX + SHOTCOUNTLABELX, w_BgPosY + SHOTCOUNTLABELY));
        w_Score->setTextColor(Color4B::BLACK);
        addChild(w_Score, Z_ShotCountLabel, T_ShotCountLabel);

        _ShotCount = 0;
    }
    
    // 跳躍数が999以上上がらない
    if (_ShotCount > SHOTCOUNTMAX) {
        _ShotCount = SHOTCOUNTMAX;
    }

    // ショットカウントラベルの更新
    w_Score->setString(StringUtils::format("跳躍数 : %d", _ShotCount));
}

// ゲームクリアラベルの参照
void GameLayer::showGameClearLabel() {
    // 効果音再生
    auto w_Audio = SimpleAudioEngine::getInstance();
    w_Audio->playEffect(cSound::getSEName(SE_Cong));

    // クリアの結果をDBに登録
    registerSQL();

    // ゲームクリアを表示
    auto w_Clear = (Sprite*)getChildByTag(T_GameClearLabel);
    if (!w_Clear) {
        w_Clear = Sprite::create("gameClear.png");
        w_Clear->setAnchorPoint(Point::ANCHOR_MIDDLE);
        w_Clear->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
        addChild(w_Clear, Z_Button, T_GameClearLabel);
    }

    // ゲームクリアのボタンを表示
    auto w_ClearButton = (MenuItemImage*)getChildByTag(T_GameClearButton);
    if (!w_ClearButton) {
        auto w_BeforeButton = "home_be.png";
        auto w_AfterButton  = "home_af.png";

        w_ClearButton = MenuItemImage::create(
                        w_BeforeButton,
                        w_AfterButton,
                        CC_CALLBACK_1(GameLayer::onClearButtonCallback,this)
                        );
        w_ClearButton->setAnchorPoint(Point::ANCHOR_MIDDLE);
        w_ClearButton->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2 + CLEARBUTTONY));

        Menu* w_Menu = Menu::create(w_ClearButton, NULL);
        w_Menu->setPosition(Vec2::ZERO);
        addChild(w_Menu, Z_Button);
    }

    _WallCollision = false;
}

// DBにクリア結果を登録
void GameLayer::registerSQL() {
    // ステージ情報をセット
    int w_StageNum = _StageNumber / 10;
    int w_AreaNum = _StageNumber % 10;
    int w_ClearLevel;

    // スコア判定
    w_ClearLevel = cStageInfo::getClearLevel(_StageNumber,_ShotCount);

    // SQLITE3
    sqlite3* w_pDB = NULL;
    char* w_ErrMsg = NULL;
    std::string w_SqlStr;
    //std::string w_dbPath = "D:/db/";
    int w_Result;
    auto w_FilePath = FileUtils::getInstance();
    auto w_dbPath = w_FilePath->getWritablePath();

    w_dbPath.append("StageInfo.db");

    // SQLオープン
    w_Result = sqlite3_open(w_dbPath.c_str(), &w_pDB);
    if (w_Result != SQLITE_OK) {
        CCLOG("OPENING WRONG, %d, MSG:%s", w_Result, w_ErrMsg);
    }
    else {
        CCLOG("OK! %d, %s", w_Result, w_ErrMsg);
    }

    // クリア評価を更新
    w_SqlStr = " update StageTable set CLEARLEVEL = " + std::to_string(w_ClearLevel);
    w_SqlStr = w_SqlStr + " where STAGENUM = " + std::to_string(w_StageNum);
    w_SqlStr = w_SqlStr + " AND AREANUM = " + std::to_string(w_AreaNum);
    w_Result = sqlite3_exec(w_pDB, w_SqlStr.c_str(), NULL, NULL, &w_ErrMsg);

    // DBをクローズ
    sqlite3_close(w_pDB);
}

// クリアボタン押下時のコールバック関数
void GameLayer::onClearButtonCallback(Ref* pm_pSender) {
    //ゲームタイトル画面へ戻る
    auto w_Scene = SelectLayer::createScene();
    Director::getInstance()->replaceScene(w_Scene);
}

// リセットボタン押下時のコールバック関数
void GameLayer::onRestartCallback(Ref* pm_pSender) {
    //ゲームタイトル画面へ戻る
    auto w_Scene = GameLayer::createScene();
    Director::getInstance()->replaceScene(w_Scene);
}

//衝突イベント
bool GameLayer::onContactBegin(PhysicsContact& pm_Contact) {
    // 衝突情報を取得
    auto w_BodyA = pm_Contact.getShapeA()->getBody()->getNode();
    auto w_BodyB = pm_Contact.getShapeB()->getBody()->getNode();

    // ブロック同士が衝突している場合は処理不要
    if ((w_BodyA->getTag() == T_Bounce && w_BodyB->getTag() == T_Bounce) ||
        (w_BodyA->getTag() == T_Block && w_BodyB->getTag() == T_Block)) {
        return true;
    }

    //オブジェクトを取得
    auto w_Ball = getChildByTag(T_Ball);

    // ボールを飛ばすのを許可する
    if (w_Ball) {
        // ボールショット許可フラグを有にセット
        _WallCollision = true;

        // 罰アイコンを非表示
        auto w_Cross = w_Ball->getChildByTag(T_Foot)->getChildByTag(T_Cross);
        w_Cross->setVisible(false);
    }

    if (w_BodyA && w_BodyB) {
        // バウンドブロックと衝突した場合の処理
        if (w_BodyA->getTag() == T_Bounce || w_BodyB->getTag() == T_Bounce) {
            // 効果音再生
            auto w_Audio = SimpleAudioEngine::getInstance();
            w_Audio->playEffect(cSound::getSEName(SE_Bound));
        }

        // 鍵と衝突した場合の処理
        if (w_BodyA->getTag() == T_Key ||
            w_BodyB->getTag() == T_Key) {
            // 鍵とロックを削除
            auto w_key = getChildByTag(T_Key);
            auto w_Lock = getChildByTag(T_Lock);
            removeChild(w_key);
            removeChild(w_Lock);

            // 効果音再生
            auto w_Audio = SimpleAudioEngine::getInstance();
            w_Audio->playEffect(cSound::getSEName(SE_GetKey));

            return true;
        }

        // クリアと衝突した場合の処理
        if (w_BodyA->getTag() == T_Clear ||
            w_BodyB->getTag() == T_Clear) {
            // ボールを削除
            removeChild(w_Ball);

            // クリア画面を表示
            showGameClearLabel();
        }
    }

    return true;
}


// タッチイベント
bool GameLayer::onTouchBegan(Touch* pm_Touch, Event* pm_Unused_event) {
    // タッチポジションを保持
    _onTouchPosition = pm_Touch->getLocation();

    return _WallCollision;
}

// タッチ移動イベント
void GameLayer::onTouchMoved(Touch* pm_Touch, Event* pm_Unused_event) {
    // 矢印を取得
    auto w_Arrow = getChildByTag(T_Ball)->getChildByTag(T_Arrow);

    // 矢印の向きと大きさを計算
    auto w_Angle = CC_RADIANS_TO_DEGREES((_onTouchPosition - pm_Touch->getLocation()).getAngle());
    float w_Distance = pm_Touch->getLocation().getDistance(_onTouchPosition);

    // 矢印の長さによって色を変化する
    if (w_Distance < ARROWMIN ) {
        w_Arrow->setVisible(false);
    } else if (w_Distance > ARROWMAX) {
        w_Distance = ARROWMAX;
        w_Arrow->setVisible(true);
        w_Arrow->setColor(Color3B::RED);
    } else {
        w_Arrow->setVisible(true);
        w_Arrow->setColor(Color3B::ORANGE);
    }

    // 矢印をセット
    w_Arrow->setRotation((w_Angle + ARROWROTAINIT) * -1);
    w_Arrow->setScaleY(w_Distance / 100);
}

// タッチ終了イベント
void GameLayer::onTouchEnded(Touch* pm_Touch, Event* pm_Unused_event) {
    // ボールの情報を取得
    auto w_Ball = getChildByTag(T_Ball);
    auto w_Arrow = w_Ball->getChildByTag(T_Arrow);
    auto w_Cross = w_Ball->getChildByTag(T_Foot)->getChildByTag(T_Cross);

    // ボールが存在する場合に処理
    if (w_Ball) {
        // ボールの弾く力を計算 
        Vec2 w_Vec = _onTouchPosition - pm_Touch->getLocation();

        // 最小引っ張りの長さ
        if (std::abs(w_Vec.x) < ARROWMIN && std::abs(w_Vec.y) < ARROWMIN) {
            w_Arrow->setVisible(false);
            return;
        }

        // ショットカウントラベルを更新
        showShotCountLabel();

        // 最大引っ張りの長さ
        auto w_Hypotence = std::hypot(std::abs(w_Vec.x), std::abs(w_Vec.y));
        if (w_Hypotence > ARROWMAX) {
            // ベクトルの正規化
            float x = w_Vec.x / w_Hypotence;
            float y = w_Vec.y / w_Hypotence;
            w_Vec = Vec2(x, y) * 500000;
        } else {
            // ベクトルの長さ×強さ
            w_Vec = w_Vec * 1000;
        }

        // 矢印非表示 && 罰を表示
        w_Arrow->setVisible(false);
        w_Cross->setVisible(true);

        // ボールショット許可フラグを無にセット
        _WallCollision = false;

        // ボールに力を加える
        w_Ball->getPhysicsBody()->resetForces();
        w_Ball->getPhysicsBody()->applyImpulse(w_Vec);

        // 効果音再生
        auto w_Audio = SimpleAudioEngine::getInstance();
        w_Audio->playEffect(cSound::getSEName(SE_Chick));
    }
}

// タッチキャンセルイベント
void GameLayer::onTouchCanceled(Touch* pm_Touch, Event* pm_Unused_event) {
    onTouchEnded(pm_Touch, pm_Unused_event);
}

// 選択画面から選んだステージの情報を保持
void GameLayer::StageNumberSet(int pm_Count) {
    _StageNumber = pm_Count;
}