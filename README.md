# floatrandom

48ビット精度の0〜1の範囲のfloat型実数の真性乱数を返すPython モジュール

    frandommodule.c   モジュールソース
    frandom.so        動的ライブラリ（モジュール本体）
    floatrandom.py    テストプログラム
    makefile          makefile
    
メソッド説明

    Open()            乱数デバイスを開く
    frandom()         0〜1の真性乱数を返す
    Close()           乱数デバイスを閉じる
    
make
    make              モジュール作成
    make install      ライブラリを当該ディレクトリにインストール
    make clean        カレントにある動的ライブラリファイルを削除
    make all          全部やる
    
