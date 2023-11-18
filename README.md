# ChickWayHome(ひよこの帰り道)

## URL

http://

## ゲーム概要

ひよこを弾いて家までゴールさせるゲームです。

途中には様々なアイテムやギミック、そして障害物が待ち構えています。

## 開発環境

★言語

　C、C++

★ゲームエンジン

　Cocos2dx

★外部ライブラリ

　SQLite3
 
　https://www.sqlite.org/index.html

## 設計書

[クラス図.xlsx](./クラス図.xlsx)

## 操作機能

タップ

## ゲーム詳細

★メイン画面

　ゲームが起動すると、メイン画面が表示します。
 
　メイン画面をタップすると、ステージ選択画面へ遷移します。

★ステージ選択画面

　ステージボタンをタップすると、ゲーム画面へ遷移します。

　合計30のステージが用意されており、最初のステージから順に難易度がじわじわと高まっていきます。

　ステージをクリアすると、ひよこを弾いた回数に応じて、ステージボタンに星の得点が設定されます。

 ★ゲーム画面

　ひよこをゴールまで弾きます。
 
　たくさん弾いた数ほど、ステージ選択画面のボタンには星の得点が削られます。

　<img src="https://github.com/KASHIHARA-GITHUB/ChickWayHome_Cocos2dx/assets/69448136/706c4ea4-6285-4728-b2d7-473f8929eb51" alt="代替テキスト" width="40%" />
　<img src="https://github.com/KASHIHARA-GITHUB/ChickWayHome_Cocos2dx/assets/69448136/b50f08b4-5489-4357-9458-539ac09dc414" alt="代替テキスト" width="40%" />
