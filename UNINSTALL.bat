@echo off

set "INSTALL_FOLDER=C:\Program Files\Cockoo"

set "RegKey=HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run"
set "RegName=Cockoo"

if not "%1"=="am_admin" (
    powershell -Command "Start-Process -Verb RunAs -FilePath '%0' -ArgumentList 'am_admin'"
    exit /b
)



if exist "%INSTALL_FOLDER%" (
	del "%INSTALL_FOLDER%\Cockoo.exe" > nul
	del "%INSTALL_FOLDER%\openal32.dll" > nul
	del "%INSTALL_FOLDER%\UNINSTALL.bat" > nul

	rd /q "%INSTALL_FOLDER%"

	echo ----------------------------------------------
	echo.
	echo ^> Uninstalled from "%INSTALL_FOLDER%"

	reg delete "%RegKey%" /v "%RegName%" /f

	
	echo ^> Registry records were deleted
	echo.
) else (
	echo.
	echo ----------------------------------------------
	echo.
	echo Program is not installed!
)

pause