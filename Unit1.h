//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TButton *START;
        TButton *RESTART;
        TButton *CLOSE;
        TTimer *Timer1;
        TTimer *Timer2;
        TButton *NEWBALL;
        TLabel *Label1;
        void __fastcall CLOSEClick(TObject *Sender);
        void __fastcall STARTClick(TObject *Sender);
        void __fastcall RESTARTClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall NEWBALLClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//***************************************************** // friend class TForm1;
class brick            //�j�����O
{
  public:             // ����H(�{���X����@�B)���i��
    brick(int);
    brick();
    ~brick();
    void impact(int);     // �j�������P�_
    bool brickworking;    // �j�����}��
    int BRheight(),BRwidth(),BRtop(),BRleft();  // �Ω�j���������P�_

  private:           // �u����class�i��
    int affordBR;    // �j���@�[��
    TTimer *Drop;
    TShape *Brick;
    void __fastcall DropTimer(TObject *Sender);
};
//******************************************************
class ballB            //�y���O
{
  public:
    ballB();
    ~ballB();
    void STOP();
    void RUN();
    void impact(int);       // �y���������䨤�P�_
    void crashblock(int);   // �y����תO
    bool ballBworking;      // �y���}��

  private:
    TTimer *engine;   //����
    TShape *B;        //�y
    int x,y,boundx,boundy,fire;  //�y���W�U���k�A�y������d��A�y�����O
    void __fastcall engineTimer(TObject *Sender);
};
//*******************************************************
class block          // �תO���O
{
  public:
    block(int);
    ~block();
    void impact(int);   // ����
    int BLheight(),BLwidth(),BLtop(),BLleft();

  private:
    TTimer *blockmove;
    TShape *Block;

    void __fastcall blockmoveTimer(TObject *Sender);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
