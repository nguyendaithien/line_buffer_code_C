############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project line_buffer_code_C
set_top filter3x3_orig
add_files conv.cpp
add_files -tb test.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xcvu9p-flga2104-2-i}
create_clock -period 6.66 -name default
source "./line_buffer_code_C/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
