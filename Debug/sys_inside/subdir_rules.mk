################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
sys_inside/delay.obj: ../sys_inside/delay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="sys_inside/delay.d_raw" --obj_directory="sys_inside" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sys_inside/exit.obj: ../sys_inside/exit.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="sys_inside/exit.d_raw" --obj_directory="sys_inside" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sys_inside/timer.obj: ../sys_inside/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="sys_inside/timer.d_raw" --obj_directory="sys_inside" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


