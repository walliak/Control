################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/430_key.obj: ../src/430_key.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -O2 --use_hw_mpy=F5 --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/ccs_base/msp430/include" --include_path="D:/CCS6.1.0.00104_win32/workspace/F5529_example/src" --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --include_path="E:/WindowsDesktop/Control/EX/F5529_example/driverlib/MSP430F5xx_6xx" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="src/430_key.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ad.obj: ../src/ad.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -O2 --use_hw_mpy=F5 --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/ccs_base/msp430/include" --include_path="D:/CCS6.1.0.00104_win32/workspace/F5529_example/src" --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --include_path="E:/WindowsDesktop/Control/EX/F5529_example/driverlib/MSP430F5xx_6xx" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="src/ad.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/lcd.obj: ../src/lcd.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -O2 --use_hw_mpy=F5 --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/ccs_base/msp430/include" --include_path="D:/CCS6.1.0.00104_win32/workspace/F5529_example/src" --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --include_path="E:/WindowsDesktop/Control/EX/F5529_example/driverlib/MSP430F5xx_6xx" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="src/lcd.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/led.obj: ../src/led.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted -O2 --use_hw_mpy=F5 --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/ccs_base/msp430/include" --include_path="D:/CCS6.1.0.00104_win32/workspace/F5529_example/src" --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" --include_path="E:/WindowsDesktop/Control/EX/F5529_example/driverlib/MSP430F5xx_6xx" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="src/led.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


