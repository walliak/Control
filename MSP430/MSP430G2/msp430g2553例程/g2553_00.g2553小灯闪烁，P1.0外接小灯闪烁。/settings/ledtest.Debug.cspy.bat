@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM
@REM Read about available command line parameters in the C-SPY Debugging
@REM Guide. Hints about additional command line parameters that may be
@REM useful in specific cases:
@REM   --download_only   Downloads a code image without starting a debug
@REM                     session afterwards.
@REM   --silent          Omits the sign-on message.
@REM   --timeout         Limits the maximum allowed execution time.
@REM 


@echo off 

if not "%~1" == "" goto debugFile 

@echo on 

"D:\IAR\common\bin\cspybat" -f "E:\WindowsDesktop\Control\MSP430资料\MSP430例程\msp430g2553例程\g2553_00.g2553小灯闪烁，P1.0外接小灯闪烁。\settings\ledtest.Debug.general.xcl" --backend -f "E:\WindowsDesktop\Control\MSP430资料\MSP430例程\msp430g2553例程\g2553_00.g2553小灯闪烁，P1.0外接小灯闪烁。\settings\ledtest.Debug.driver.xcl" 

@echo off 
goto end 

:debugFile 

@echo on 

"D:\IAR\common\bin\cspybat" -f "E:\WindowsDesktop\Control\MSP430资料\MSP430例程\msp430g2553例程\g2553_00.g2553小灯闪烁，P1.0外接小灯闪烁。\settings\ledtest.Debug.general.xcl" "--debug_file=%~1" --backend -f "E:\WindowsDesktop\Control\MSP430资料\MSP430例程\msp430g2553例程\g2553_00.g2553小灯闪烁，P1.0外接小灯闪烁。\settings\ledtest.Debug.driver.xcl" 

@echo off 
:end