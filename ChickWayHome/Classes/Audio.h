#ifndef __AUDIO__H__
#define __AUDIO__H__

#include "cocos2d.h"
#include "cocostudio/simpleAudioEngine.h"
#include "Common.h"

class Audio : public cocos2d::Sprite {
protected:
    int _AudioNumber;
    virtual bool init();    //初期化
public:
    static Audio* create();	//インスタンス生成
    void startAudio(int pm_AudioNumber,float pm_Delay); //音楽を再生
};

#endif // __AUDIO__H__
