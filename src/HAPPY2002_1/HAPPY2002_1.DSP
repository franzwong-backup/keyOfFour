# Microsoft Developer Studio Project File - Name="Happy2002_1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Happy2002_1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Happy2002_1.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Happy2002_1.mak" CFG="Happy2002_1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Happy2002_1 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Happy2002_1 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Happy2002_1 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "NDEBUG"
# ADD RSC /l 0x404 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 gdiplus.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib ddraw.lib dinput8.lib winmm.lib Quartz.lib /nologo /subsystem:windows /machine:I386 /out:"Release/TheKeyOfFour.exe"

!ELSEIF  "$(CFG)" == "Happy2002_1 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x404 /d "_DEBUG"
# ADD RSC /l 0x404 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Strmiids.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dxguid.lib ddraw.lib dinput8.lib winmm.lib Quartz.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/TheKeyOfFour.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Happy2002_1 - Win32 Release"
# Name "Happy2002_1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\AlphaBlend.cpp
# End Source File
# Begin Source File

SOURCE=.\src\BattleScene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DD.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DI.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DS.cpp
# End Source File
# Begin Source File

SOURCE=.\Happy2002_1.rc
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MainChar.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Map.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MapScene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\MenuScene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Monster.cpp
# End Source File
# Begin Source File

SOURCE=.\src\OpeningScene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Pic.cpp
# End Source File
# Begin Source File

SOURCE=.\src\PicInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\TileOp.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlphaBlend.h
# End Source File
# Begin Source File

SOURCE=.\include\AlphaBlend.h
# End Source File
# Begin Source File

SOURCE=.\include\BattleScene.h
# End Source File
# Begin Source File

SOURCE=.\include\DD.h
# End Source File
# Begin Source File

SOURCE=.\include\DI.h
# End Source File
# Begin Source File

SOURCE=.\include\DS.h
# End Source File
# Begin Source File

SOURCE=.\include\MainChar.h
# End Source File
# Begin Source File

SOURCE=.\include\Map.h
# End Source File
# Begin Source File

SOURCE=.\include\MapScene.h
# End Source File
# Begin Source File

SOURCE=.\include\MenuScene.h
# End Source File
# Begin Source File

SOURCE=.\include\Monster.h
# End Source File
# Begin Source File

SOURCE=.\include\OpeningScene.h
# End Source File
# Begin Source File

SOURCE=.\include\Pic.h
# End Source File
# Begin Source File

SOURCE=.\include\PicInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\Scene.h
# End Source File
# Begin Source File

SOURCE=.\include\TileOp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\TheKeyOfFour.ico
# End Source File
# End Group
# End Target
# End Project
