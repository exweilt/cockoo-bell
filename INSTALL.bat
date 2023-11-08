@echo off
set "INSTALL_FOLDER=C:\Program Files\Cockoo"

set "RegKey=HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run"
set "RegName=Cockoo"
set "RegValue=%INSTALL_FOLDER%\Cockoo.exe"

:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
    IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"
:--------------------------------------   


if not exist "%INSTALL_FOLDER%" (
    mkdir "%INSTALL_FOLDER%"
)

copy /Y "Cockoo.exe" "%INSTALL_FOLDER%" > nul
copy /Y "openal32.dll" "%INSTALL_FOLDER%" > nul
copy /Y "UNINSTALL.bat" "%INSTALL_FOLDER%" > nul

reg add "%RegKey%" /v "%RegName%" /t REG_SZ /d "%RegValue%" /f

echo.
echo Program installed to "%INSTALL_FOLDER%"
echo Program added to autorun

pause