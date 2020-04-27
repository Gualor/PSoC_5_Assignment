# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Lory\Desktop\psoc_assignment_git\PSoC_5_Assignment\AY1920_II_HW_05_GUALNIERA_LORENZO\AY1920_II_HW_05_PROJ_2.cydsn\AY1920_II_HW_05_PROJ_2.cyprj
# Date: Mon, 27 Apr 2020 16:25:23 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {UART_Debug_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {CLOCK_TIMER} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2401 4801} [list [get_pins {ClockBlock/dclk_glb_1}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\Lory\Desktop\psoc_assignment_git\PSoC_5_Assignment\AY1920_II_HW_05_GUALNIERA_LORENZO\AY1920_II_HW_05_PROJ_2.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Lory\Desktop\psoc_assignment_git\PSoC_5_Assignment\AY1920_II_HW_05_GUALNIERA_LORENZO\AY1920_II_HW_05_PROJ_2.cydsn\AY1920_II_HW_05_PROJ_2.cyprj
# Date: Mon, 27 Apr 2020 16:25:18 GMT
