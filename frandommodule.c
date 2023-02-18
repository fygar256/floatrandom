#include  <Python.h>
#include  <stdlib.h>
#include  <stdio.h>

static  FILE *fp=NULL;
static  int  count=0;
#define RANDOMMAX (0x0000ffffffffffff)

// サブ関数
// 48bit符号なし整数の乱数を乱数デバイスから得る
//
static int64_t get_48bit_random() {
    int c;
    char buff[sizeof (int64_t)]={0,0,0,0,0,0,0,0};
    for (int idx=0;idx<(int)sizeof (double)-2;idx++) {
        c=fgetc(fp);
        if (c==EOF)
            return -1;
        buff[idx]=c;
        }
    return (*((int64_t *)buff) );
}

//
// Open()        乱数デバイスを開く
// 戻り値：成功したらTrueを、失敗したらFalseを返す。
//
static PyObject* Open(PyObject *self,PyObject *args) {
  if (count==0) {
      if ((fp=fopen("/dev/random","rb"))!=NULL) {
          count++;
          Py_RETURN_TRUE;
          }
      else
          Py_RETURN_FALSE;
      }
  else {
      count++;
      Py_RETURN_TRUE;
      }
}

//
// Close() 乱数デバイスを閉じる
// 戻り値：成功したらTrueを、失敗したらFalseを返す。
//
static PyObject* Close(PyObject *self,PyObject *args) {
  if (count==0)
      Py_RETURN_TRUE;
  else {
      count--;
      if (count==0)
          if (fclose(fp)!=EOF)
              Py_RETURN_TRUE;
          else
              Py_RETURN_FALSE;
      else
          Py_RETURN_TRUE;
      }
}

//
// frandom(): ０〜１までの乱数を返す エラーのときは−１を返す。
//

static PyObject* frandom(PyObject *self,PyObject *args) {
    int64_t l;
    double f;
    if (fp==NULL)
        return Py_BuildValue("d", -1);
    if ((l=get_48bit_random())==-1) 
        return Py_BuildValue("d", -1);
    f=(double)l/RANDOMMAX;
    return Py_BuildValue("d", f);
}

///*****************************************************************
///
/// モジュール定義
///
///*****************************************************************


//
// モジュール内のメソッドの定義する
//
// {
// "Open" メソッド名
//  Open メソッドの本体
//  METH_VARARGS は引数の定義, METH_NOARGS は引数なしのときの定義
//  "open random"         // メソッドの説明
// }

static PyMethodDef methods[] = {
    { 
     "Open",                // メソッド名
      Open,                 // メソッド本体
      METH_NOARGS,          // 引数なしのときの定義
      "open random"         // メソッドの説明
    },
    {"Close", Close, METH_NOARGS, "close random"},
    {"frandom", frandom, METH_NOARGS, "get float random number"},
    //{"frandom", frandom, METH_VARARGS, "get float random number"}, 引数を取る場合
    {NULL,NULL,0,NULL},  // 番兵
};

// モジュールの定義
static struct PyModuleDef module =
{
    PyModuleDef_HEAD_INIT,
    "frandom",  // モジュール名。
    "get random number",  // モジュールの説明
    -1,  // モジュールのインタプリタのステートのサイズ
    methods  // メソッド群定義
};

// モジュールの初期化
PyMODINIT_FUNC PyInit_frandom(void)
{
    return PyModule_Create(&module);
}

