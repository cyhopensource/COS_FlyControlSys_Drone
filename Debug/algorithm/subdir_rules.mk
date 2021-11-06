################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
algorithm/PID_control.obj: ../algorithm/PID_control.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="algorithm/PID_control.d_raw" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

algorithm/filter.obj: ../algorithm/filter.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="algorithm/filter.d_raw" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

algorithm/imu.obj: ../algorithm/imu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="algorithm/imu.d_raw" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

algorithm/math2.obj: ../algorithm/math2.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="C:/ti_workfiles/workspaces_28379d/flight_control_v1.0" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_common/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/F2837xD_headers/include" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d/project/cap_test" --include_path="C:/ti/workspaces_28379d/TMS320F28379_d" --include_path="C:/ti_new/ccsv8/tools/compiler/ti-cgt-c2000_18.1.2.LTS/include" --define=_LAUNCHXL_F28379D --define=_FLASH --define=CPU1 -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="algorithm/math2.d_raw" --obj_directory="algorithm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


