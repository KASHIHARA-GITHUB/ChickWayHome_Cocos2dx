#include "SelectLayer.h"

#define WINSIZE Director::getInstance()->getWinSize()
#define STAGE_X 3        // ステージボタンの列数
#define STAGE_Y 10       // ステージボタンの行数
#define SOUNDDELAY 1.0f  // 音楽遅延時間
#define INITPOSX 200     // ステージボタンの初期位置X
#define DURATIONPOSX 350 // ステージボタンの間隔位置X
#define INITPOSY 150     // ステージボタンの初期位置Y
#define DURATIONPOSY 250 // ステージボタンの間隔位置Y
#define TEXTSIZE 96      // ステージボタンのテキストサイズ
#define STARPOSX 70      // 星の位置X
#define STARPOSY 50      // 星の位置Y
#define TAGY 10          // タグY
#define STAGEBUTTON 30   // ステージボタン数
#define SCROLLINNERSIZE Size(640, 2600) // スクロールの中のサイズ

USING_NS_CC;
USING_NS_CC_EXT;

using namespace Common;
using namespace CocosDenshion;

//セレクトシーン生成
Scene* SelectLayer::createScene() {
    auto w_Scene = Scene::create();         // セレクトシーンを生成する
    auto w_Layer = SelectLayer::create();   // SelectLayerクラスのレイヤーを生成する
    w_Scene->addChild(w_Layer);             // シーンに対してレイヤーを追加する

    return w_Scene; // シーンを返す
}

// セレクトレイヤー初期化処理
bool SelectLayer::init() {
    if ( !Layer::init())
        return false;

    Director::getInstance()->getTextureCache()->removeAllTextures();

    // シングルタップイベントの取得
    auto w_TouchListener = EventListenerTouchOneByOne::create();
    w_TouchListener->onTouchBegan = CC_CALLBACK_2(SelectLayer::onTouchBegan, this);
    w_TouchListener->onTouchMoved = CC_CALLBACK_2(SelectLayer::onTouchMoved, this);
    w_TouchListener->onTouchEnded = CC_CALLBACK_2(SelectLayer::onTouchEnded, this);
    w_TouchListener->setSwallowTouches(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(w_TouchListener, this);

    // オーディオを再生
    auto w_Audio = Audio::create();
    w_Audio->startAudio(S_Select, SOUNDDELAY);
    addChild(w_Audio);

    return true;
}

// レイヤー表示時処理
void SelectLayer::onEnter() {
    Layer::onEnter();

    createBackground(); // 背景を生成
    createScroll();     // スクロールを生成
}

// 背景を生成
void SelectLayer::createBackground() {
    // 背景の後ろ設定
    auto w_BackBehind = Background::create(L_Game);
    w_BackBehind->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    w_BackBehind->setPosition(Point(WINSIZE / 2));
    addChild(w_BackBehind, Z_BackgroundBehind);

    // 背景の設定
    auto w_Background = Background::create(L_Select);
    w_Background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto test = WINSIZE / 2;
    w_Background->setPosition(Vec2(WINSIZE / 2));
    addChild(w_Background, Z_Background, T_Background);
}

// スクロールを生成
void SelectLayer::createScroll() {
    // DBから各ステージの進捗情報を取得
    std::array<SelectLayer::StageStatus, STAGEBUTTON> w_StageStatus;
    w_StageStatus = readSQL();

    //スクロールの生成
    auto w_Background = getChildByTag(T_Background);
    ui::ScrollView* w_Scroll = ui::ScrollView::create();
    w_Scroll->setDirection(ui::ScrollView::Direction::VERTICAL);
    w_Scroll->setContentSize(Size(w_Background->getContentSize()));
    w_Scroll->setInnerContainerSize(SCROLLINNERSIZE);
    w_Scroll->setBounceEnabled(true);
    w_Scroll->setSwallowTouches(false);
    w_Scroll->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    w_Scroll->setPosition(Vec2(WINSIZE/2));

    int w_StarCount = 0;

    //各ステージボタンを生成
    Sprite* w_StageSelect;
    Label*  w_StageName;

    for (int y = 1; y <= STAGE_Y; y++) {
        for (int x = 1; x <= STAGE_X; x++) {
            //ステージボタンの位置を計算
            float w_ScrollX = INITPOSX + (DURATIONPOSX * (x - 1));
            float w_ScrollY = w_Scroll->getInnerContainerSize().height - INITPOSY - (DURATIONPOSY * (y - 1));

            //ステージボタンを生成する
            auto w_StageButton = Sprite::create("StageSelect.png");
            w_StageButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            w_StageButton->setPosition(w_ScrollX, w_ScrollY);

            //ステージボタンのテキストを生成
            Vec2 w_NamePosition = Vec2(w_StageButton->getContentSize().width / 2,
                                       w_StageButton->getContentSize().height / 2 + 30);
            std::string w_StageNum = std::to_string(y) + " - " + std::to_string(x);
            w_StageName = Label::createWithTTF(w_StageNum, cText::getFont(F_Google), TEXTSIZE);
            w_StageName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            w_StageName->setPosition(w_NamePosition);
            w_StageName->setTextColor(Color4B::WHITE);

            // ステージボタンにテキストをセット
            w_StageButton->addChild(w_StageName, Z_Text);

            //　ステージボタンに星をセットする位置を決める
            Vec2 w_StarPosition[3] = {
                Vec2(w_StageButton->getContentSize().width / 2 - STARPOSX, STARPOSY),
                Vec2(w_StageButton->getContentSize().width / 2, STARPOSY),
                Vec2(w_StageButton->getContentSize().width / 2 + STARPOSX, STARPOSY)
            };

            //ステージボタンに星をセット
            for (int i = 0; i < w_StageStatus[w_StarCount]._ClearLevel; i++) {
                auto w_StageStar = Sprite::create("star.png");
                w_StageStar->setPosition(w_StarPosition[i]);
                w_StageButton->addChild(w_StageStar, 3);
            }

            //次のステージへインクリメント
            w_StarCount++;
            
            // ステージボタンをセット
            w_Scroll->addChild(w_StageButton, Z_Button, T_StageButton + y * TAGY + x);
        }
    }
    // スクロールをセット
    addChild(w_Scroll, Z_Scroll, T_Scroll);
}

// DBからステージ情報を取得
std::array<SelectLayer::StageStatus, 30> SelectLayer::readSQL() {
    // SQLITE3変数を宣言
    sqlite3* w_pDB = NULL;
    char* w_ErrMsg = NULL;
    std::string w_SqlStr;
    auto w_FilePath = FileUtils::getInstance();
    auto w_DbPath = w_FilePath->getWritablePath();
    int w_Result;

    w_DbPath.append("StageInfo.db");

    //　ファイルの削除
    // cocos2d::FileUtils::getInstance()->removeFile(w_DbPath.c_str());

    // ファイルの有無
    bool w_SQLFileBool = cocos2d::FileUtils::getInstance()->isFileExist(w_DbPath.c_str());

    // SQLオープン(DBファイルがない場合は作成)
    w_Result = sqlite3_open(w_DbPath.c_str(), &w_pDB);
    if (w_Result != SQLITE_OK) {
        CCLOG("OPENING WRONG, %d, MSG:%s", w_Result, w_ErrMsg);
    } else {
        CCLOG("OK! %d, %s", w_Result, w_ErrMsg);
    }

    // CREATE初期化(テーブルの作成)
    if (w_SQLFileBool) {
        CCLOG("File exists: %s", w_DbPath.c_str());
    } else {
        CCLOG("File does not exist: %s", w_DbPath.c_str());

        // テーブル生成
        w_SqlStr = " create table StageTable(";
        w_SqlStr = w_SqlStr + "ID integer primary key autoincrement,";
        w_SqlStr = w_SqlStr + "STAGENUM int(2),";
        w_SqlStr = w_SqlStr + "AREANUM int(1),";
        w_SqlStr = w_SqlStr + "CLEARLEVEL int(3) DEFAULT 0 ) ";
        w_Result = sqlite3_exec(w_pDB, w_SqlStr.c_str(), NULL, NULL, &w_ErrMsg);

        if (w_Result != SQLITE_OK)
            CCLOG("失敗　:%d ，原因:%s\n", w_Result, w_ErrMsg);

        // データを追加
        for (int y = 1; y <= STAGE_Y; y++) {
            for (int x = 1; x <= STAGE_X; x++) {
                w_SqlStr = " insert into StageTable( STAGENUM,AREANUM ) values (";
                w_SqlStr = w_SqlStr + std::to_string(y) + ",";
                w_SqlStr = w_SqlStr + std::to_string(x) + ") ";
                w_Result = sqlite3_exec(w_pDB, w_SqlStr.c_str(), NULL, NULL, &w_ErrMsg);
                if (w_Result != SQLITE_OK)
                    CCLOG("失敗　:%d ，原因:%s\n", w_Result, w_ErrMsg);
            }
        }
    }

    // SELECT結果情報取得変数
    sqlite3_stmt* w_Stmt = NULL;

    // SELECT(ステージ情報)実行
    w_SqlStr = " select * From StageTable ";
    w_Result = sqlite3_prepare_v2(w_pDB, w_SqlStr.c_str(), w_SqlStr.length(), &w_Stmt, NULL);
    sqlite3_reset(w_Stmt);
    if (w_Result != SQLITE_OK)
        CCLOG("失敗　:%d ，原因:%s\n", w_Result, w_ErrMsg);

    // ステージ情報取得
    std::array<SelectLayer::StageStatus, 30> w_StageStatus;
    int w_SqlStatus = 0, i = 0;
    while (SQLITE_ROW == (w_SqlStatus = sqlite3_step(w_Stmt))) {
        w_StageStatus[i]._StageNumber = sqlite3_column_int(w_Stmt, 1);
        w_StageStatus[i]._AreaNumber = sqlite3_column_int(w_Stmt, 2);
        w_StageStatus[i]._ClearLevel = sqlite3_column_int(w_Stmt, 3);
        i++;
    }

    // DBクローズ
    sqlite3_close(w_pDB);

    return w_StageStatus;
}

// タッチイベント
bool SelectLayer::onTouchBegan(Touch* touch, Event* unused_event) {
    //タップアニメーション生成
    auto w_Tap = Tap::create();
    w_Tap->setPosition(Point(touch->getLocation().x, touch->getLocation().y));
    addChild(w_Tap, 22, T_Background);

    // タッチ位置を取得
    _onTouchPoint = touch->getLocation();
    _slideFlag = true;
    return true;
}

// タッチ移動イベント
void SelectLayer::onTouchMoved(Touch* touch, Event* unused_event) {
    // タッチした位置とスライドした位置の距離を計算
    float w_Distance = _onTouchPoint.getDistance(touch->getLocation());
    if (w_Distance > 0.0f)
        _slideFlag = false;
}

// タッチ終了イベント
void SelectLayer::onTouchEnded(Touch* touch, Event* unused_event) {
    //　ステージボタン当たり判定
    onTouchStageButton(touch);
}

// ステージボタンタッチ時処理
void SelectLayer::onTouchStageButton(Touch* touch) {
    // スライドもしくはボタンを押した場合は操作を無効
    if (_buttonAnim == false || _slideFlag == false) {
        return;
    }

    // スクロール取得
    auto w_Scroll = (ui::ScrollView*)getChildByTag(T_Scroll);
    Sprite* w_StageButton;

    for (int y = 1; y <= STAGE_Y; y++) {
        for (int x = 1; x <= STAGE_X; x++) {
            // ステージボタン取得
            w_StageButton = (Sprite*)w_Scroll->getChildByTag(T_StageButton + y * TAGY + x);

            auto w_ScrollInnerPos = -1 * w_Scroll->getInnerContainerPosition(); // インナースクロールの位置
            auto w_ScrollPos = w_Scroll->getPosition() - w_Scroll->getContentSize() / 2; // スクロールの左下の位置
            auto w_ScrollInTouch = (touch->getLocation() - w_ScrollPos) + w_ScrollInnerPos; // スクロールの中の位置を計算

            // 対象のステージボタンを選択時に処理
            if (w_StageButton->getBoundingBox().containsPoint(w_ScrollInTouch)) {

                // 効果音再生
                auto w_Audio = SimpleAudioEngine::getInstance();
                w_Audio->playEffect(cSound::getSEName(SE_Button));

                // メンバー変数にセット
                _y = y;
                _x = x;
                _buttonAnim = false;

                // ボタン押下時のアニメーションをセット
                auto w_ScaleUp = ScaleBy::create(0.1, 1.1);
                auto w_ScaleDown = ScaleBy::create(0.1, 1 / 1.1);
                auto w_Func = CallFunc::create([&]() {
                    _buttonAnim = true;

                    // ゲームレイヤーにステージ情報をセット
                    int w_StageNum = 10 * _y + _x;
                    GameLayer::StageNumberSet(w_StageNum);

                    // 選択画面シーンへ移動
                    auto w_Scene = GameLayer::createScene();
                    auto w_Tran = TransitionFade::create(1, w_Scene);
                    Director::getInstance()->replaceScene(w_Tran);
                });

                // ボタン処理実行
                auto w_Seq = Sequence::create(w_ScaleUp, w_ScaleDown, w_Func, nullptr);
                w_StageButton->runAction(w_Seq);
                CCLOG("y = %d x = %d", y, x);
            }
        }
    }
}