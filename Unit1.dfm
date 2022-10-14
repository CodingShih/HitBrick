object Form1: TForm1
  Left = 341
  Top = 75
  Width = 730
  Height = 732
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = CHINESEBIG5_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = #27161#26999#39636
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 21
  object GroupBox1: TGroupBox
    Left = 568
    Top = 0
    Width = 154
    Height = 701
    Align = alRight
    Caption = #25171#30938#22602':'
    Color = clGradientActiveCaption
    ParentColor = False
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 40
      Width = 11
      Height = 21
    end
    object START: TButton
      Left = 8
      Top = 256
      Width = 137
      Height = 81
      Caption = #36938#25138#38283#22987
      TabOrder = 0
      OnClick = STARTClick
    end
    object RESTART: TButton
      Left = 8
      Top = 480
      Width = 137
      Height = 81
      Caption = #37325#26032#38283#23616
      TabOrder = 1
      OnClick = RESTARTClick
    end
    object CLOSE: TButton
      Left = 8
      Top = 584
      Width = 137
      Height = 81
      Caption = #32080#26463#36938#25138
      TabOrder = 2
      OnClick = CLOSEClick
    end
    object NEWBALL: TButton
      Left = 8
      Top = 376
      Width = 137
      Height = 73
      Caption = #26032#22686#19968#38982#29699
      TabOrder = 3
      OnClick = NEWBALLClick
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 496
    Top = 672
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 536
    Top = 672
  end
end
