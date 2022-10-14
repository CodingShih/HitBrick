//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
brick *BRICK[70];    // 磚塊宣告
ballB *BALL[10];     //  球宣告
block *BLOCK[2];     // 擋板宣告
int n=0;             //紀錄球的顆數
TColor C[5]={TColor(0x000078F0),clGray,TColor(0x000054A8),
TColor(0x00414141),TColor(0x00DBDDDC)};     //土黏木石鐵
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
brick::brick(int i)       //   磚塊建構子
{
  Brick=new TShape(Form1);
  Brick->Parent=Form1;
  Brick->Height=32;
  Brick->Width=80;
  Brick->Top=i%10*33;
  Brick->Left=i/10*81;
  affordBR=random(5)+1;
  Brick->Brush->Color=C[affordBR-1];
  brickworking=true;

  Drop=new TTimer(Form1);
  Drop->Enabled=false;
  Drop->Interval=20;
  Drop->OnTimer=brick::DropTimer;
}

brick::~brick()          //   磚塊解構子
{
  delete Drop;
  delete Brick;
}

void brick::impact(int a)           //當磚塊被撞擊
{
  affordBR -= a;       //耐久度減損
  if (affordBR==0 || affordBR<0)       // 耐久度小於等於0時
  {
    brickworking=false;
    Brick->Shape=stCircle;            //變成圓形寶物掉到下方
    Drop->Enabled=true;
  }
  else
  {
    Brick->Brush->Color=C[affordBR-1];  //依照耐久度扣損來變色
  }
}

void __fastcall brick::DropTimer(TObject *Sender)
{
  Brick->Top+=10;    //磚塊變成寶物掉落
  if (Brick->Top+20 >Form1->Height-40)
  {
    Brick->Visible=false;
    Drop->Enabled=false;
  }
}

int brick::BRleft()
{
  return Brick->Left;
}
int brick::BRwidth()
{
  return Brick->Width;
}
int brick::BRtop()
{
  return Brick->Top;
}
int brick::BRheight()
{
  return Brick->Height;
}
//***************************************************************************
ballB::ballB()              // 球 建構子
{
  x=5;                      //球的移動距離
  y=5;
  fire=random(5)+1;             //球的火力

  B=new TShape(Form1);         // 球 是Shape物件
  B->Parent=Form1;             // 球 屬性設定
  B->Width=20;
  B->Height=B->Width;
  B->Left=245;
  B->Top=420;
  B->Brush->Color=C[fire-1];
  B->Shape=stCircle;
  ballBworking=true;

  engine=new TTimer(Form1);       // engine 引擎 TTimer
  engine->Enabled=true;
  engine->Interval=90;   // 球的跑速
  engine->OnTimer=engineTimer;
}

ballB::~ballB()            // 球球解構子
{
  engine->Enabled=false;
  delete engine;         // 先讓球停下來
  delete B;             // 再刪除球
}

void ballB::STOP()         // 停下 函式
{
  engine->Enabled=false;
}

void ballB::RUN()        // 球的跑動 函式
{
  engine->Enabled=true;
}

void __fastcall ballB::engineTimer(TObject *Sender)  // 球的跑動範圍
{
  if (ballBworking)
  {
    B->Top -=y;
    B->Left +=x;

    if (B->Left-10 <0 || B->Left+20>568)
      x=-x;
    if (B->Top-10 <0)
      y=-y;
    if (B->Top+20>672)   //球 沒被接到，掉到底部
      ballBworking=false;
  }
}

void ballB::impact(int I)    // 判斷球撞擊磚塊的函式
{                                               //        A1               A2
  int brick_A1=BRICK[I]->BRleft();                 // (x1,y1) ........ (x2,y1)
  int brick_A2= brick_A1 +BRICK[I]->BRwidth();     // brick   ........
  int brick_B1=BRICK[I]->BRtop();                  // (x1,y2) ........ (x2,y2)
  int brick_B2= brick_B1 +BRICK[I]->BRheight();  //       B1               B2
                                                   //    C1            C2
  int ball_C1=B->Left;                             // (x1,y1) * * * (x2,y1)
  int ball_C2= ball_C1 +B->Width;                  //  ball   * * *
  int ball_D1=B->Top;                              // (x1,y2) * * * (x2,y2)
  int ball_D2= ball_D1 +B->Height;                  //    D1            D2

  if ((brick_A1 < ball_C1 && ball_C1 < brick_A2
     && brick_B1 < ball_D1 && ball_D1 < brick_B2) ||

      (brick_A1 < ball_C2 && ball_C2 < brick_A2
     && brick_B1 < ball_D1 && ball_D1 < brick_B2) ||

      (brick_A1 < ball_C1 && ball_C1 < brick_A2
     && brick_B1 < ball_D2 && ball_D2 < brick_B2) ||

      (brick_A1 < ball_C2 && ball_C2 < brick_A2
     && brick_B1 < ball_D2 && ball_D2 < brick_B2))
  {
    BRICK[I]->impact(fire);       // 撞擊火力 會讓磚塊掉色
    if (brick_B1<ball_C1 && ball_C1<brick_B2
       || brick_B1<ball_D2 && ball_D2<brick_B2)
    {
       x=-x;
    }
    else if (brick_A1<ball_C1 && ball_C1<brick_B2
            || brick_A1<ball_C2 && ball_C2<brick_A2)
    {
      y=-y;
    }                                    // 這個PART完成 !
  }

}
    // 球打到擋板                             //        (x1,y1) *********** (x2,y1)
void ballB::crashblock(int I)                 //                *  block  *
{                                             //        (x1,y2) *********** (x2,y2)
  int block_E1=BLOCK[I]->BLleft();               // x1 ->  左上
  int block_E2= block_E1 +BLOCK[I]->BLwidth();   // x2 ->  右上
  int block_F1=BLOCK[I]->BLtop();                // x3 ->  左下
  int block_F2= block_F1 +BLOCK[I]->BLheight();  // x4 ->  右下

  int ball_C1=B->Left;                              //   (x2,y2) * * * (x2,y1)
  int ball_C2= ball_C1 +B->Width;                   //    ball   * * *
  int ball_D1=B->Top;                               //   (x1,y2) * * * (x2,y2)
  int ball_D2= ball_D1 +B->Height;

  if ((block_E1 < ball_C1 && ball_C1 < block_E2
      && block_F1 < ball_D1 && ball_D1 < block_F2) ||

      (block_E1 < ball_C2 && ball_C2 < block_E2
      && block_F1 < ball_D1 && ball_D1 < block_F2) ||

      (block_E1 < ball_C1 && ball_C1 < block_E2
      && block_F1 < ball_D2 && ball_D2 < block_F2) ||

      (block_E1 < ball_C2 && ball_C2 < block_E2
      && block_F1 < ball_D2 && ball_D2 < block_F2))
  {
      if( block_F1<ball_D2 && ball_D2>block_F2 ||
          block_F1<ball_D1 && ball_D1>block_F2 )
      {
        x=-x;
      }
      else if( block_E1-1<ball_C1 && ball_C1<block_E2+2 ||
               block_E1-1<ball_C2 && ball_C2<block_E2+2 )
      {
        y=-y;
      }
  }  

}
//***************************************************************************
block::block(int i)           // 擋板建構子
{
  Block=new TShape(Form1);       //第一塊屬性設定
  Block->Parent=Form1;
  Block->Left=i%2 *300;
  Block->Top=520;
  Block->Width=82;
  Block->Height=26;               //擋板的顏色 跟 耐久度 無關
  Block->Brush->Color=(TColor)random(0xffffff);
  Block->Shape=stRoundRect;


  blockmove=new TTimer(Form1);         // 移動擋板的Timer屬性設定
  blockmove->Interval=50;
  blockmove->Enabled=true;
  blockmove->OnTimer=blockmoveTimer;

}

block::~block()         // 擋板解構子
{
  blockmove->Enabled=false;
  delete blockmove;
  delete Block;
}

void __fastcall block::blockmoveTimer(TObject *Sender)
{                    // 擋板 移動(鍵盤的左右鍵)

  blockmove->Interval=50;       //檔板移動速度

  if (GetAsyncKeyState(37))      //&0x8000
    BLOCK[0]->Block->Left-=10;   //左 第一塊擋板 左移
  if (GetAsyncKeyState(39))
    BLOCK[0]->Block->Left+=10;   //右 第一塊擋板 右移

  if (GetAsyncKeyState(65))
    BLOCK[1]->Block->Left-=10;   // A 第二塊擋板 左移
  if (GetAsyncKeyState(68))
    BLOCK[1]->Block->Left+=10;   // D 第二塊擋板 右移

  int block_0=BLOCK[0]->BLleft();
  int block_1=BLOCK[1]->BLleft();

  if ((BLOCK[0]->Block->Left < 0) && (block_0 != 0))  //
    BLOCK[0]->Block->Left+=10;
  if ((BLOCK[0]->Block->Left >480) && (block_0+82 != block_1))
    BLOCK[0]->Block->Left-=10;
  if ((BLOCK[1]->Block->Left < 0) && (block_1 != block_0+82))
    BLOCK[1]->Block->Left+=10;
  if ((BLOCK[1]->Block->Left >480) && (block_1+82<480))
    BLOCK[1]->Block->Left-=10;
}

int block::BLleft()
{
  return Block->Left;
}
int block::BLwidth()
{
  return Block->Width;
}
int block::BLtop()
{
  return Block->Top;
}
int block::BLheight()
{
  return Block->Height;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CLOSEClick(TObject *Sender)
{                          //遊戲結束
  for (int i=0;i<70;i++)
  {
    if (BRICK[i]!=NULL)
      delete BRICK[i];
  }
  for (int i=0;i<10;i++)
  {
    if (BALL[i]!=NULL)
      delete BALL[i];
  }
  for (int i=0;i<2;i++)
  {
    if (BLOCK[i]!=NULL)
      delete BLOCK[i];
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::STARTClick(TObject *Sender)
{                        //開始遊戲
  n=0;
    for (int i=0;i<70;i++)        // 新增磚塊
    {
      if (BRICK[i]==NULL)
      {
        BRICK[i]=new brick(i);
      }
    }
    for (int i=0;i<2;i++)       // 新增擋板
    {
      if (BLOCK[i]==NULL)
      {
        BLOCK[i]=new block(i);
      }
    }
  
  if (Label1->Caption=="")
    Label1->Caption="磚塊耐久度:\n\n泥土: 1(橘黃) \n黏土: 2(深灰) \n木材: 3(棕)\n石頭: 4 (黑)\n鐵塊: 5 (白)";

  //Timer1->Enabled=true;
  //Timer2->Enabled=true;
  START->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RESTARTClick(TObject *Sender)
{                       // 重新開局
  Timer1->Enabled=false;
  Timer2->Enabled=false;
  START->Enabled=true;
  for (int i=0;i<70;i++)
  {
    if (BRICK[i]!=NULL)      //清除 磚塊、球、擋板
      delete BRICK[i];         //和Close按鈕相差一個關閉檔案的功能
  }
  for (int i=0;i<10;i++)
  {
    if (BALL[i]!=NULL)
      delete BALL[i];
  }
  for (int i=0;i<2;i++)
  {
    if (BLOCK[i]!=NULL)
      delete BLOCK[i];
  }

  for (int i=0;i<70;i++)        // 新增磚塊
  {
    BRICK[i]=new brick(i);
  }
  for (int i=0;i<2;i++)       // 新增擋板
  {
    BLOCK[i]=new block(i);
  }
  Form1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  for (int i=0;i<n;i++)      //球碰到磚塊
  {
    for (int j=0;j<70;j++)
    {
      if (BRICK[j]->brickworking)
        BALL[i]->impact(j);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
  for (int i=0;i<n;i++)      //球碰到擋板
  {
    for (int j=0;j<2;j++)
    {
      if (BALL[i]->ballBworking)
        BALL[i]->crashblock(j);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NEWBALLClick(TObject *Sender)
{
  //if (BALL[n]==NULL)

    BALL[n]=new ballB();      // 新增球
    n++;
  Timer1->Enabled=true;
  Timer2->Enabled=true;
}
//---------------------------------------------------------------------------



