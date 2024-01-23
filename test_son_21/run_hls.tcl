# Create a projec
open_project -reset CNN

# Add design files
add_files full.cpp 
# Add test bench & files
add_files -tb full_test.cpp

# Set the top-level function
set_top full

# ########################################################
# Create a solution
open_solution -reset solution1
# Define technology and clock rate
set_part {xcvu9p-flga2104-2-i}
create_clock -period 6.66

# Source x_hls.tcl to determine which steps to execute
source x_hls.tcl
csim_design
# Set any optimization directives
# End of directives

if {$hls_exec == 1} {
	# Run Synthesis and Exit
	csynth_design
	
} elseif {$hls_exec == 2} {
	# Run Synthesis, RTL Simulation and Exit
	csynth_design
	
	cosim_design
} elseif {$hls_exec == 3} { 
	# Run Synthesis, RTL Simulation, RTL implementation and Exit
	csynth_design
	
	cosim_design
	export_design
} else {
	# Default is to exit after setup
	csynth_design
}

exit

open_project loop_opts_prj

set_top full

add_files full.cpp
add_files -tb full_test.cpp

open_solution "solution1"
set_part {xcvu9p-flga2104-2-i}
create_clock -period 6.66 -name default

csim_design -clean
csynth_design
#cosim_design -trace_level none -rtl systemc
#export_design -format ip_catalog
exit
