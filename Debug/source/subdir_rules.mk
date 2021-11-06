################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/F2837xD_Adc.obj: ../source/F2837xD_Adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Adc.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_CodeStartBranch.obj: ../source/F2837xD_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_CodeStartBranch.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_CpuTimers.obj: ../source/F2837xD_CpuTimers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_CpuTimers.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_DBGIER.obj: ../source/F2837xD_DBGIER.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_DBGIER.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_DefaultISR.obj: ../source/F2837xD_DefaultISR.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_DefaultISR.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Dma.obj: ../source/F2837xD_Dma.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Dma.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_ECap.obj: ../source/F2837xD_ECap.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_ECap.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_EPwm.obj: ../source/F2837xD_EPwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_EPwm.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_EQep.obj: ../source/F2837xD_EQep.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_EQep.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Emif.obj: ../source/F2837xD_Emif.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Emif.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_GlobalVariableDefs.obj: ../source/F2837xD_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_GlobalVariableDefs.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Gpio.obj: ../source/F2837xD_Gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Gpio.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_I2C.obj: ../source/F2837xD_I2C.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_I2C.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Ipc.obj: ../source/F2837xD_Ipc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Ipc.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Ipc_Driver.obj: ../source/F2837xD_Ipc_Driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Ipc_Driver.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Ipc_Driver_Lite.obj: ../source/F2837xD_Ipc_Driver_Lite.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Ipc_Driver_Lite.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Ipc_Driver_Util.obj: ../source/F2837xD_Ipc_Driver_Util.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Ipc_Driver_Util.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Mcbsp.obj: ../source/F2837xD_Mcbsp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Mcbsp.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_PieCtrl.obj: ../source/F2837xD_PieCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_PieCtrl.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_PieVect.obj: ../source/F2837xD_PieVect.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_PieVect.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Sci.obj: ../source/F2837xD_Sci.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Sci.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Spi.obj: ../source/F2837xD_Spi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Spi.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_SysCtrl.obj: ../source/F2837xD_SysCtrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_SysCtrl.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_TempSensorConv.obj: ../source/F2837xD_TempSensorConv.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_TempSensorConv.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_Upp.obj: ../source/F2837xD_Upp.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_Upp.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_can.obj: ../source/F2837xD_can.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_can.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_sci_io.obj: ../source/F2837xD_sci_io.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_sci_io.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_sdfm_drivers.obj: ../source/F2837xD_sdfm_drivers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_sdfm_drivers.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_struct.obj: ../source/F2837xD_struct.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_struct.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/F2837xD_usDelay.obj: ../source/F2837xD_usDelay.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="source/F2837xD_usDelay.d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


