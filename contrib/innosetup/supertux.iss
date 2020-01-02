; Supertux setup script. Process this scrip with InnoSetup
;
; This script assumes that you have prepared a directory that contains all
; files that "jam install" installs in the data\ subdir. You should also place
; files like README and COPYING
; into the doc\ dir.
; The main directory should contain this file the supertux.ico, all .dll
; files and the supertux.exe file.
[Setup]
AppName=Super Turr
AppVerName=Super Turr ALPHA
AppPublisher=Super Turr Development Team
AppPublisherURL=
AppSupportURL=
AppUpdatesURL=
DefaultDirName={pf}\SuperTurr
DefaultGroupName=SuperTurr

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "superturr.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "superturr.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "*.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "doc\*.*"; DestDir: "{app}\doc\"; Flags: ignoreversion
Source: "data\*.*"; DestDir: "{app}\data\"; Flags: ignoreversion recursesubdirs

[Icons]
Name: "{group}\SuperTurr"; Filename: "{app}\superturr.exe"; WorkingDir: "{app}"; IconFilename: "{app}\superturr.ico"
Name: "{group}\{cm:UninstallProgram,SuperTurr}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\SuperTurr"; Filename: "{app}\superturr.exe"; WorkingDir: "{app}"; IconFilename: "{app}\superturr.ico"; Tasks: desktopicon

[Run]
Filename: "{app}\superturr.exe"; Description: "{cm:LaunchProgram,SuperTurr}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{app}\.superturr"
Type: filesandordirs; Name: "{app}\stdout.txt"
Type: filesandordirs; Name: "{app}\stderr.txt"
