[Setup]
AppName=学生成绩管理系统
AppVersion=1.0
AppPublisher=LHY
AppPublisherURL=https://github.com/LHY0125Student-Grade-Management-System.git
AppSupportURL=https://github.com/LHY0125Student-Grade-Management-System.git
AppUpdatesURL=https://github.com/LHY0125Student-Grade-Management-System.git
DefaultDirName={autopf}\StudentGradeSystem
DefaultGroupName=学生成绩管理系统
AllowNoIcons=yes
LicenseFile=..\LICENSE
OutputDir=dist
OutputBaseFilename=StudentGradeSystem_Inno_Setup
SetupIconFile=
Compression=lzma
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=lowest

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\student_system.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\MD\*"; DestDir: "{app}\MD"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\TXT\*"; DestDir: "{app}\TXT"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\README.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\LICENSE"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\学生成绩管理系统"; Filename: "{app}\student_system.exe"
Name: "{group}\{cm:UninstallProgram,学生成绩管理系统}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\学生成绩管理系统"; Filename: "{app}\student_system.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\student_system.exe"; Description: "{cm:LaunchProgram,学生成绩管理系统}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{app}\data"