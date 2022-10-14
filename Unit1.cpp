//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
brick *BRICK[70];    // �j���ŧi
ballB *BALL[10];     //  �y�ŧi
block *BLOCK[2];     // �תO�ŧi
int n=0;             //�����y������
TColor C[5]={TColor(0x000078F0),clGray,TColor(0x000054A8),
TColor(0x00414141),TColor(0x00DBDDDC)};     //�g�H����K
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
brick::brick(int i)       //   �j���غc�l
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

brick::~brick()          //   �j���Ѻc�l
{
  delete Drop;
  delete Brick;
}

void brick::impact(int a)           //��j���Q����
{
  affordBR -= a;       //�@�[�״�l
  if (affordBR==0 || affordBR<0)       // �@�[�פp�󵥩�0��
  {
    brickworking=false;
    Brick->Shape=stCircle;            //�ܦ�����_������U��
    Drop->Enabled=true;
  }
  else
  {
    Brick->Brush->Color=C[affordBR-1];  //�̷ӭ@�[�צ��l���ܦ�
  }
}

void __fastcall brick::DropTimer(TObject *Sender)
{
  Brick->Top+=10;    //�j���ܦ��_������
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
ballB::ballB()              // �y �غc�l
{
  x=5;                      //�y�����ʶZ��
  y=5;
  fire=random(5)+1;             //�y�����O

  B=new TShape(Form1);         // �y �OShape����
  B->Parent=Form1;             // �y �ݩʳ]�w
  B->Width=20;
  B->Height=B->Width;
  B->Left=245;
  B->Top=420;
  B->Brush->Color=C[fire-1];
  B->Shape=stCircle;
  ballBworking=true;

  engine=new TTimer(Form1);       // engine ���� TTimer
  engine->Enabled=true;
  engine->Interval=90;   // �y���]�t
  engine->OnTimer=engineTimer;
}

ballB::~ballB()            // �y�y�Ѻc�l
{
  engine->Enabled=false;
  delete engine;         // �����y���U��
  delete B;             // �A�R���y
}

void ballB::STOP()         // ���U �禡
{
  engine->Enabled=false;
}

void ballB::RUN()        // �y���]�� �禡
{
  engine->Enabled=true;
}

void __fastcall ballB::engineTimer(TObject *Sender)  // �y���]�ʽd��
{
  if (ballBworking)
  {
    B->Top -=y;
    B->Left +=x;

    if (B->Left-10 <0 || B->Left+20>568)
      x=-x;
    if (B->Top-10 <0)
      y=-y;
    if (B->Top+20>672)   //�y �S�Q����A���쩳��
      ballBworking=false;
  }
}

void ballB::impact(int I)    // �P�_�y�����j�����禡
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
    BRICK[I]->impact(fire);       // �������O �|���j������
    if (brick_B1<ball_C1 && ball_C1<brick_B2
       || brick_B1<ball_D2 && ball_D2<brick_B2)
    {
       x=-x;
    }
    else if (brick_A1<ball_C1 && ball_C1<brick_B2
            || brick_A1<ball_C2 && ball_C2<brick_A2)
    {
      y=-y;
    }                                    // �o��PART���� !
  }

}
    // �y����תO                             //        (x1,y1) *********** (x2,y1)
void ballB::crashblock(int I)                 //                *  block  *
{                                             //        (x1,y2) *********** (x2,y2)
  int block_E1=BLOCK[I]->BLleft();               // x1 ->  ���W
  int block_E2= block_E1 +BLOCK[I]->BLwidth();   // x2 ->  �k�W
  int block_F1=BLOCK[I]->BLtop();                // x3 ->  ���U
  int block_F2= block_F1 +BLOCK[I]->BLheight();  // x4 ->  �k�U

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
block::block(int i)           // �תO�غc�l
{
  Block=new TShape(Form1);       //�Ĥ@���ݩʳ]�w
  Block->Parent=Form1;
  Block->Left=i%2 *300;
  Block->Top=520;
  Block->Width=82;
  Block->Height=26;               //�תO���C�� �� �@�[�� �L��
  Block->Brush->Color=(TColor)random(0xffffff);
  Block->Shape=stRoundRect;


  blockmove=new TTimer(Form1);         // ���ʾתO��Timer�ݩʳ]�w
  blockmove->Interval=50;
  blockmove->Enabled=true;
  blockmove->OnTimer=blockmoveTimer;

}

block::~block()         // �תO�Ѻc�l
{
  blockmove->Enabled=false;
  delete blockmove;
  delete Block;
}

void __fastcall block::blockmoveTimer(TObject *Sender)
{                    // �תO ����(��L�����k��)

  blockmove->Interval=50;       //�ɪO���ʳt��

  if (GetAsyncKeyState(37))      //&0x8000
    BLOCK[0]->Block->Left-=10;   //�� �Ĥ@���תO ����
  if (GetAsyncKeyState(39))
    BLOCK[0]->Block->Left+=10;   //�k �Ĥ@���תO �k��

  if (GetAsyncKeyState(65))
    BLOCK[1]->Block->Left-=10;   // A �ĤG���תO ����
  if (GetAsyncKeyState(68))
    BLOCK[1]->Block->Left+=10;   // D �ĤG���תO �k��

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
{                          //�C������
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
{                        //�}�l�C��
  n=0;
    for (int i=0;i<70;i++)        // �s�W�j��
    {
      if (BRICK[i]==NULL)
      {
        BRICK[i]=new brick(i);
      }
    }
    for (int i=0;i<2;i++)       // �s�W�תO
    {
      if (BLOCK[i]==NULL)
      {
        BLOCK[i]=new block(i);
      }
    }
  
  if (Label1->Caption=="")
    Label1->Caption="�j���@�[��:\n\n�d�g: 1(���) \n�H�g: 2(�`��) \n���: 3(��)\n���Y: 4 (��)\n�K��: 5 (��)";

  //Timer1->Enabled=true;
  //Timer2->Enabled=true;
  START->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RESTARTClick(TObject *Sender)
{                       // ���s�}��
  Timer1->Enabled=false;
  Timer2->Enabled=false;
  START->Enabled=true;
  for (int i=0;i<70;i++)
  {
    if (BRICK[i]!=NULL)      //�M�� �j���B�y�B�תO
      delete BRICK[i];         //�MClose���s�ۮt�@�������ɮת��\��
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

  for (int i=0;i<70;i++)        // �s�W�j��
  {
    BRICK[i]=new brick(i);
  }
  for (int i=0;i<2;i++)       // �s�W�תO
  {
    BLOCK[i]=new block(i);
  }
  Form1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  for (int i=0;i<n;i++)      //�y�I��j��
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
  for (int i=0;i<n;i++)      //�y�I��תO
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

    BALL[n]=new ballB();      // �s�W�y
    n++;
  Timer1->Enabled=true;
  Timer2->Enabled=true;
}
//---------------------------------------------------------------------------



