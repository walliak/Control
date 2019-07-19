################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/bin/cl430" -vmsp --abi=coffabi --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/ccs_base/msp430/include" --include_path="E:/WindowsDesktop/MSP430G2/G2 pocket lab code for CCS5.5/21_1_DAC_AWG/src" --include_path="D:/CCS6.1.0.00104_win32/CCS/ccsv6/tools/compiler/ti-cgt-msp430_4.4.3/include" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


