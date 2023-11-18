#ifndef __COMMON__H__
#define __COMMON__H__

#pragma execution_character_set("utf-8")

#include "cocos2d.h"

USING_NS_CC;

#define POSX Director::getInstance()->getWinSize().width / 2
#define POSY Director::getInstance()->getWinSize().height / 2

#define STAGENUMX 3
#define STAGENUMY 10

// 共通
namespace Common
{
    struct StageInfo {
        Vec2 position;
        int  blockType;
        Vec2 warpTo;
    };

    //タグ
    enum Tag {
        T_Background = 1,
        T_Title,
        T_Button,
        T_Scroll,
        T_Enemy,
        T_Ball,
        T_Arrow,
        T_Foot,
        T_Cross,
        T_Block,
        T_Clear,
        T_ShotCountLabel,
        T_GameClearLabel,
        T_GameClearButton,
        T_Tap,
        T_Bounce,
        T_Warp = 101,
        T_Key,
        T_Lock,
        T_MenuBack,
        T_MenuRestart,
        T_StageButton = 200, // ステージボタンのタグは200～310まで使用
    };

    //Zオーダー
    enum ZOrder {
        Z_Background = 1,
        Z_Title,
        Z_Scroll,
        Z_Text,
        Z_Ball,
        Z_Block,
        Z_Button,
        Z_Goal,
        Z_ShotCountLabel,
        Z_Tap,
        Z_Lock,
        Z_BackgroundBehind,
    };

    //種類
    enum BlockType {
        Block1 = 1,
        Block2,
        Block3,
        Block4,
        Block5,
        Block6,
        Warp,
        WarpTo,
        Key,
        Lock,
        Goal,
    };

    //レイヤー
    enum LayerType {
        L_Title = 1,
        L_Select,
        L_Bg1,
        L_Bg2,
        L_Bg3,
        L_Game,
    };

    //地面
    enum GroundType {
        G_Normal = 1,
        G_Ice,
        G_Bounce,
    };

    enum Sound {
        S_Title,
        S_Select,
        S_Game,
    };

    enum SoundEffect {
        SE_Button,
        SE_Chick,
        SE_Bound,
        SE_GetKey,
        SE_Cong,
    };

    enum Text {
        TXT_Title1,
    };

    enum Font {
        F_Google,
    };

    // サウンド
    class cSound {
    public:
        static char* getSoundName(int pm_BGM) {
            char* w_BGM[10] = { "audio/bgm.mp3" ,
                                "audio/selectbgm.mp3",
                                "audio/gamebgm.mp3" };

            return w_BGM[pm_BGM];
        }

        static char* getSEName(int pm_Sound) {
            char* w_Sound[10] = { "audio/button.mp3",
                                  "audio/chick.mp3",
                                  "audio/bound.mp3",
                                  "audio/getkey.mp3",
                                  "audio/congratulation.mp3" };

            return w_Sound[pm_Sound];
        }
    };

    // テキスト
    class cText {
    public:
        static char* getText(int pm_Text) {
            char* w_Text[10] = { "画面をタップ!" };

            return w_Text[pm_Text];
        }

        static char* getFont(int pm_Font) {
            char* w_Font[10] = { "fonts/GoogleMoji.ttf" };

            return w_Font[pm_Font];
        }
    };

    // ステージ番号変換
    class cStageNumConv {
    public:
        static std::map<int, int> getStageNumConv() {

            std::map<int, int> w_StageNumConvert;

            for (int y = 1; y <= STAGENUMY; y++)  {
                for (int x = 1; x <= STAGENUMX; x++) {
                    w_StageNumConvert[(y * 10) + x] = ((y - 1) * 3 + x ) - 1;
                }
            }

            return w_StageNumConvert;
        }
    };

    // ボール位置
    class cBallPos {
    private:
        static Vec2 getBallPos(float pm_PosIndexX, float pm_PosIndexY) {
            int w_BSize = 50;

            float pm_PosX = POSX + w_BSize * pm_PosIndexX;
            float pm_PosY = POSY + w_BSize * pm_PosIndexY;

            return Vec2(pm_PosX, pm_PosY);
        }
    public:
        static Vec2 getBallPos(int pm_StageNum) {

            std::map<int, int> StageNumConvert;
            StageNumConvert = cStageNumConv::getStageNumConv();
            int w_BallPosNum = StageNumConvert[pm_StageNum];
            CCLOG("StagenumConv %d ", StageNumConvert[pm_StageNum]);

            Vec2 BallPos[30] = {
                Vec2(getBallPos(-8, -4)),   // 1-1
                Vec2(getBallPos(-8, -4)),   // 1-2
                Vec2(getBallPos(-8, -4)),   // 1-3
                Vec2(getBallPos(-8, -4)),   // 2-1
                Vec2(getBallPos(-8, -4)),   // 2-2
                Vec2(getBallPos(-8, -4)),   // 2-3
                Vec2(getBallPos(-8, -4)),   // 3-1
                Vec2(getBallPos(-8, -4)),   // 3-2
                Vec2(getBallPos(-8, -4)),   // 3-3
                Vec2(getBallPos(-10, -4)),  // 4-1
                Vec2(getBallPos(-10, -4)),  // 4-2
                Vec2(getBallPos(-10, -4)),  // 4-3
                Vec2(getBallPos(-10, -4)),  // 5-1
                Vec2(getBallPos(-10, -4)),  // 5-2
                Vec2(getBallPos(-10, -4)),  // 5-3
                Vec2(getBallPos(-10, -4)),  // 6-1
                Vec2(getBallPos(-10, -4)),  // 6-2
                Vec2(getBallPos(-10, -4)),  // 6-3
                Vec2(getBallPos(-10, -4)),  // 7-1
                Vec2(getBallPos(-10, -4)),  // 7-2
                Vec2(getBallPos(-10, -4)),  // 7-3
                Vec2(getBallPos(-10, -4)),  // 8-1
                Vec2(getBallPos(-10, -4)),  // 8-2
                Vec2(getBallPos(-10, -4)),  // 8-3
                Vec2(getBallPos(-10, -4)),  // 9-1
                Vec2(getBallPos(-10, -4)),  // 9-2
                Vec2(getBallPos(-10, -4)),  // 9-3
                Vec2(getBallPos(-10, -4)),  // 10-1
                Vec2(getBallPos(-10, -4)),  // 10-2
                Vec2(getBallPos(-10, -4)),  // 10-3
            };

            return BallPos[w_BallPosNum];
        }
    };

    class cStageInfo {
    private:
        static Vec2 getBlockPos(float pm_PosIndexX, float pm_PosIndexY) {
            int w_BSize = 50;

            float pm_PosX = POSX + w_BSize * pm_PosIndexX;
            float pm_PosY = POSY + w_BSize * pm_PosIndexY;

            return Vec2(pm_PosX, pm_PosY);
        }
        static std::vector<StageInfo> getStageGround(int pm_StageType, std::vector<StageInfo> pm_StageInfo) {
            //地面
            for (int i = 0; i < 23; i++) {
                if (pm_StageType == G_Normal) {
                    pm_StageInfo.push_back({ Vec2(getBlockPos(i - 11, -6)) , Block1 });
                } else if (pm_StageType == G_Ice) {
                    pm_StageInfo.push_back({ Vec2(getBlockPos(i - 11, -6)) , Block2 });
                } else {
                    pm_StageInfo.push_back({ Vec2(getBlockPos(i - 11, -6)) , Block3 });
                }
            }

            return pm_StageInfo;
        }
    public:
        static std::vector<StageInfo> getStagePos(int pm_StageNumber) {

            std::vector<StageInfo> w_StageInfo;
            w_StageInfo.clear();

            switch(pm_StageNumber) {
                case 11:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 12:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 3; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i, j - 5)) , Block1 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 13:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 3, j - 5)) , Block1 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 21:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < i * 2; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i, j - 5)) , Block1 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 22:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i, j - 5)) , Block1 });
                        }
                    }
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4 - i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 5, j)) , Block1 });
                        }
                    }
                    for (int i = 0; i < 1; i++) {
                        for (int j = 0; j < 10; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i + 5, j - 5)) , Block1 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 23:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int i = 0; i < 1; i++) {
                        for (int j = 0; j < 10; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 3, j - 3)) , Block1 });
                        }
                    }
                    for (int i = 0; i < 1; i++) {
                        for (int j = 0; j < 10; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i, j - 5)) , Block1 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 31:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 32:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 7, j - 5)) , Block2 });
                        }
                    }
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3 - i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i + 3, j - 5)) , Block2 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 33:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i * 2 - 5, j * 2 - 5)) , Block2 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 41:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 9, j - 5)) , Block2 });
                        }
                    }
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3 - i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i + 4, j - 5)) , Block2 });
                        }
                    }
                    for (int i = 0; i < 5; i++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(i * 2 - 5, -3)) , Block2 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 42:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    for (int i = 0; i < 7; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i * 2 - 9, j - 4)) , Block2 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 43:
                    w_StageInfo = cStageInfo::getStageGround(G_Ice, w_StageInfo);
                    for (int i = 0; i < 6; i++) {
                        for (int j = 0; j < i; j++) {
                            w_StageInfo.push_back({ Vec2(getBlockPos(i * 3 - 9, j * 2 - 4)) , Block2 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 51:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 52:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-10, -5)) , Block1 });
                    for (int i = 0; i < 17; i++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(i - 5, -2)) , Block3 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -4)) , Goal });
                    break;
                case 53:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-10, -5)) , Block1 });
                    for (int i = 0; i < 17; i++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(i - 11, -2)) , Block3 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(-8, 2)) , Goal });
                    break;
                case 61:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-10, -5)) , Block3});
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 62:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    for (int j = 0; j < 15; j++) {
                        if (!(j == 5 || j == 6 || j == 7))
                            w_StageInfo.push_back({ Vec2(getBlockPos(-4, j - 5)) , Block3 });
                        if (!(j == 2 || j == 3 || j == 4))
                            w_StageInfo.push_back({ Vec2(getBlockPos(0, j - 5)) , Block3 });
                        if (!(j == 7 || j == 8 || j == 9))
                            w_StageInfo.push_back({ Vec2(getBlockPos(4, j - 5)) , Block3 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 63:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 15; j++) {
                            if (!(j == i || j == i + 1 || j == i + 2))
                                w_StageInfo.push_back({ Vec2(getBlockPos(i - 4, j - 5)) , Block3 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Goal });
                    break;
                case 71:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int j = 0; j < 15; j++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(0, j - 5)) , Block1 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(-4, -4)) , Warp, Vec2(getBlockPos(4, -4)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(7, -3)) , Goal });
                    break;
                case 72:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-4, -4)) , Warp, Vec2(getBlockPos(-2, -2)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 0)) , Warp, Vec2(getBlockPos(-7, 0)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-5, 2)) , Warp, Vec2(getBlockPos(0, 2)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, 2)) , Warp, Vec2(getBlockPos(5, 4)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 1)) , Goal });
                    break;
                case 73:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-6, -5)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-3, -5)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, -5)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, -5)) , Warp, Vec2(getBlockPos(6, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(4, -5)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    for (int j = 0; j < 15; j++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(5, j - 5)) , Block1 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, -3)) , Goal });
                    break;
                case 81:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-3, - 3)) , Block4 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 0)) , Block4 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, 3)) , Block4 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 3)) , Goal });
                    break;
                case 82:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-4, -3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-3, -3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-2, -3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-1, 0)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 0)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(1, 0)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(2, 3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, 3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(4, 3)) , Block5 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 3)) , Goal });
                    break;
                case 83:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(-3, -3)) , Block6 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 0)) , Block6 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, 3)) , Block6 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 3)) , Goal });
                    break;
                case 91:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 0)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(6, -3)) , Goal });
                    break;
                case 92:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int j = 0; j < 5; j++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(0, j - 2)) , Block2 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, 4)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(5, -3)) , Goal });
                    break;
                case 93:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int j = 0; j < 5; j++) {
                        w_StageInfo.push_back({ Vec2(getBlockPos(-2, j - 5)) , Block2 });
                        w_StageInfo.push_back({ Vec2(getBlockPos(2, j - 5)) , Block2 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(-1, -1)) , Block6 });
                    w_StageInfo.push_back({ Vec2(getBlockPos(0, -3)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(5, -3)) , Goal });
                    break;
                case 101:
                    w_StageInfo = cStageInfo::getStageGround(G_Bounce, w_StageInfo);
                    for (int i = 0; i < 10; i++) {
                        for (int j = 0; j < 15; j++) {
                            if (!(j == i || j == i + 1 || j == i + 2))
                                w_StageInfo.push_back({ Vec2(getBlockPos(i - 4, j - 5)) , Block3 });
                        }
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-7, 0)) , Goal });
                    break;
                case 102:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int j = 0; j < 15; j++) {
                        if (!(j == 0 || j == 1 || j == 2))
                            w_StageInfo.push_back({ Vec2(getBlockPos(-4, j - 5)) , Block2 });
                        if (!(j == 9 || j == 10 || j == 11))
                            w_StageInfo.push_back({ Vec2(getBlockPos(0, j - 5)) , Block2 });
                        if (!(j == 0 || j == 1 || j == 2))
                            w_StageInfo.push_back({ Vec2(getBlockPos(4, j - 5)) , Block2 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(-3, 0)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-1, 3)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, -1)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(3, 4)) , Warp, Vec2(getBlockPos(-8, -5)) });
                    w_StageInfo.push_back({ Vec2(getBlockPos(8, 4)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-8, 0)) , Goal });
                    break;
                case 103:
                    w_StageInfo = cStageInfo::getStageGround(G_Normal, w_StageInfo);
                    for (int j = 0; j < 15; j++) {
                        if (!(j == 0 || j == 1 || j == 2))
                            w_StageInfo.push_back({ Vec2(getBlockPos(-6, j - 5)) , Block1 });
                    }
                    for (int i = 0; i < 18; i++) {
                        if (!(i == 14 || i == 15 || i == 16))
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 6, -3)) , Block1 });
                        if (!(i == 0 || i == 1 || i == 2 || i == 3))
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 6, 0)) , Block1 });
                        if (!(i == 0 || i == 14 || i == 15 || i == 16))
                            w_StageInfo.push_back({ Vec2(getBlockPos(i - 6, 3)) , Block1 });
                    }
                    w_StageInfo.push_back({ Vec2(getBlockPos(-4, 5)) , Key });
                    w_StageInfo.push_back({ Vec2(getBlockPos(-10, 0)) , Goal });
                    break;
            }

            return w_StageInfo;
        }

        static int getClearLevel(int pm_StageNum, int pm_ShotCount) {
            int w_ClearLevel;
            int w_StageLevel[30][3] = { {2,3,4},{2,3,4},{3,4,5},
                                        {3,4,5},{4,5,6},{6,7,8},
                                        {1,2,3},{2,3,4},{1,2,3},
                                        {2,3,4},{5,6,7},{4,5,6},
                                        {2,3,4},{2,3,4},{4,5,6},
                                        {2,3,4},{3,4,5},{5,6,7},
                                        {2,3,4},{2,3,4},{3,4,5},
                                        {3,4,5},{3,4,5},{3,4,5},
                                        {3,4,5},{5,6,7},{5,6,7},
                                        {6,7,8},{8,9,10},{22,23,24},
            };

            // ステージ番号変換
            std::map<int, int> w_StageNumConvert;
            w_StageNumConvert = cStageNumConv::getStageNumConv();
            int w_BallPosNum = w_StageNumConvert[pm_StageNum];

            // クリア評価をセット
            if (pm_ShotCount <= w_StageLevel[w_BallPosNum][0]) { w_ClearLevel = 3; }
            else if (pm_ShotCount <= w_StageLevel[w_BallPosNum][1]) { w_ClearLevel = 2; }
            else { w_ClearLevel = 1; }

            return w_ClearLevel;
        }
    };
};

#endif // __COMMON__H__
