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
class brick            //磚塊類別
{
  public:             // 任何人(程式碼任何一處)都可用
    brick(int);
    brick();
    ~brick();
    void impact(int);     // 磚塊撞擊判斷
    bool brickworking;    // 磚塊的開關
    int BRheight(),BRwidth(),BRtop(),BRleft();  // 用於磚塊的撞擊判斷

  private:           // 只有本class可用
    int affordBR;    // 磚塊耐久度
    TTimer *Drop;
    TShape *Brick;
    void __fastcall DropTimer(TObject *Sender);
};
//******************************************************
class ballB            //球類別
{
  public:
    ballB();
    ~ballB();
    void STOP();
    void RUN();
    void impact(int);       // 球撞擊視窗邊角判斷
    void crashblock(int);   // 球撞到擋板
    bool ballBworking;      // 球的開關

  private:
    TTimer *engine;   //引擎
    TShape *B;        //球
    int x,y,boundx,boundy,fire;  //球的上下左右，球的限制範圍，球的火力
    void __fastcall engineTimer(TObject *Sender);
};
//*******************************************************
class block          // 擋板類別
{
  public:
    block(int);
    ~block();
    void impact(int);   // 撞擊
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
