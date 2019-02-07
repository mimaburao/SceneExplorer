@echo off

if not exist %~dp0prepare.bat (
  echo prepare.bat not exist. Copy prepare.bat.sample and edit it.
  goto :err
)
call %~dp0prepare.bat

set TEST=%QTROOT%\%QTVERSION%\%QTVERSIONTOOLS%\bin
if not exist %TEST%\ (
  echo %TEST% not found
  goto err
)
set PATH=%TEST%;%PATH%

::set TEST=%QTROOT%\Tools\%QTTOOLS%\bin
::if not exist %TEST%\ (
::  echo %TEST% not found
::  goto err
::)
::set PATH=%TEST%;%PATH%

echo Qt is inserted in path.
@echo on
cmd /k


:err
pause