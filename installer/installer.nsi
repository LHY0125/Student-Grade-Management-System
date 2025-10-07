; NSIS Install Script - Student Grade Management System
; Version: v4.1.0
; Author: LHY

!define PRODUCT_NAME "Student Grade Management System"
!define PRODUCT_VERSION "4.1.0"
!define PRODUCT_PUBLISHER "LHY"
!define PRODUCT_WEB_SITE "https://github.com/LHY0125/Student-Grade-Management-System.git"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\student_system.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; Include Modern UI
!include "MUI2.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "..\LICENSE"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Install page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\student_system.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstall page
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "SimpChinese"

; Installer attributes
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "dist\StudentGradeSystem_NSIS_Setup.exe"
InstallDir "$PROGRAMFILES\StudentGradeSystem"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

; Version information
VIProductVersion "4.1.0.0"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "Comments" "Student Grade Management System - Professional student information management tool"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "LegalTrademarks" "MIT License"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "LegalCopyright" "© 2025 ${PRODUCT_PUBLISHER}"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "FileDescription" "${PRODUCT_NAME} Setup"
VIAddVersionKey /LANG=${LANG_SIMPCHINESE} "FileVersion" "${PRODUCT_VERSION}"

Section "Main Program" SEC01
  SectionIn RO
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  File "..\student_system.exe"
  CreateDirectory "$SMPROGRAMS\${PRODUCT_NAME}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\student_system.exe"
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\student_system.exe"
SectionEnd

Section "Data Files" SEC02
  SetOutPath "$INSTDIR\data"
  File /r "..\data\*.*"
SectionEnd

Section "Documentation" SEC03
  SetOutPath "$INSTDIR\MD"
  File /r "..\MD\*.*"
  SetOutPath "$INSTDIR\TXT"
  File /r "..\TXT\*.*"
  SetOutPath "$INSTDIR"
  File "..\README.md"
  File "..\LICENSE"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\student_system.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\student_system.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

; Component descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "Install main program files. This is a required component."
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "Install sample data files, including student information and user data."
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC03} "Install project documentation, including user manual and technical documents."
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) has been successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\student_system.exe"
  Delete "$INSTDIR\README.md"
  Delete "$INSTDIR\LICENSE"
  
  RMDir /r "$INSTDIR\data"
  RMDir /r "$INSTDIR\MD"
  RMDir /r "$INSTDIR\TXT"
  
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\Website.lnk"
  Delete "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  
  RMDir "$SMPROGRAMS\${PRODUCT_NAME}"
  RMDir "$INSTDIR"
  
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd