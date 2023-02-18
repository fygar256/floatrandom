# Makefileのコマンド行の先頭キャラクタをスペースに
.RECIPEPREFIX :=$(RECIPEPREFIX) <space>

# ユーザーネーム
USER        = gar

CC          = gcc
RM          = rm
CP          = cp
CSUFFIX     = .c
LSUFFIX     = .so

# 動的ライブラリの名前
TARGET      = frandom$(LSUFFIX)

SRCS        = frandommodule.c          # ソースファイルの列挙
# ライブラリディレクトリ
LIBDIRNAME  = /home/$(USER)/lib/
# コンパイラに渡すオプション
CFLAGS      = -Wall -O2

# makeとすると動的ライブラリを作成する
$(TARGET): $(SRCS)
    gcc -I/usr/include/python3.10 -fPIC -Wall -shared -o $@ $^

# make installとすると、ライブラリを当該ディレクトリにインストール
install: $(TARGET)
    $(CP) $(TARGET) $(LIBDIRNAME)

# make clean とすると .o ファイル削除
clean:
    $(RM) -rf $(TARGET)

# make all とすると最初からやる
all: clean install
