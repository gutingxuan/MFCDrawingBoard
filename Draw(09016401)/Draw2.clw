; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDraw2View
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "draw2.h"
LastPage=0

ClassCount=9
Class1=CDraw2App
Class2=CAboutDlg
Class3=CDraw2Doc
Class4=CDraw2View
Class5=HColorBar
Class6=CMainFrame
Class7=CNewPaperDlg
Class8=CSettingDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_PENTYPE
Resource3=IDR_COLORBAR
Resource4=IDR_MAINFRAME
Resource5=IDD_DLG_SETTING
Resource6=IDR_GRAPHIC
Class9=CTextEdit
Resource7=IDD_NEWPAPER

[CLS:CDraw2App]
Type=0
BaseClass=CWinApp
HeaderFile=Draw2.h
ImplementationFile=Draw2.cpp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Draw2.cpp
ImplementationFile=Draw2.cpp
Filter=D
VirtualFilter=dWC
LastObject=CAboutDlg

[CLS:CDraw2Doc]
Type=0
BaseClass=CDocument
HeaderFile=Draw2Doc.h
ImplementationFile=Draw2Doc.cpp

[CLS:CDraw2View]
Type=0
BaseClass=CScrollView
HeaderFile=Draw2View.h
ImplementationFile=Draw2View.cpp
LastObject=IDM_FLIP_VER
Filter=C
VirtualFilter=VWC

[CLS:HColorBar]
Type=0
BaseClass=CToolBar
HeaderFile=HColorBar.h
ImplementationFile=HColorBar.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CNewPaperDlg]
Type=0
BaseClass=CDialog
HeaderFile=NewPaperDlg.h
ImplementationFile=NewPaperDlg.cpp

[CLS:CSettingDlg]
Type=0
BaseClass=CDialog
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
LastObject=IDM_LINESETTING

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NEWPAPER]
Type=1
Class=CNewPaperDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_SETTING]
Type=1
Class=CSettingDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LINE_WIDTH,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342308361
Control7=IDC_RADIO2,button,1342177289
Control8=IDC_RADIO3,button,1342177289
Control9=IDC_SAMPLE,button,1342177287

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=7

[TB:IDR_GRAPHIC]
Type=1
Class=?
Command1=IDM_DOT
Command2=IDM_LINE
Command3=IDM_ELLIPSE
Command4=IDM_SOLIDELLIPSE
Command5=IDM_RECTANGLE
Command6=IDM_SOLIDRECTANGLE
Command7=IDM_CIRCLE
Command8=IDM_SOLIDCIRCLE
Command9=IDM_LINESETTING
CommandCount=9

[TB:IDR_PENTYPE]
Type=1
Class=?
Command1=IDM_OPEN
Command2=IDM_NEW
Command3=IDM_SAVE
Command4=ID_SAVEIMAGE
Command5=IDM_BRUSH
Command6=IDM_PEN
Command7=IDM_SPRAYER
Command8=IDM_PAINT
Command9=IDM_ERASER
Command10=IDM_NEWSCREEN
CommandCount=10

[TB:IDR_COLORBAR]
Type=1
Class=?
CommandCount=0

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=IDM_GAUSS
Command18=IDM_COLORGREY
Command19=IDM_ROT_LEFT
Command20=IDM_ROT_RIGHT
Command21=IDM_FLIP_HOR
Command22=IDM_FLIP_VER
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CTextEdit]
Type=0
HeaderFile=TextEdit.h
ImplementationFile=TextEdit.cpp
BaseClass=CView
Filter=C

