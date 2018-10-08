set_global_assignment -entity "nios" -library "lib_nios" -name IP_TOOL_NAME "Qsys"
set_global_assignment -entity "nios" -library "lib_nios" -name IP_TOOL_VERSION "18.1"
set_global_assignment -entity "nios" -library "lib_nios" -name IP_TOOL_ENV "Qsys"
set_global_assignment -library "lib_nios" -name SPD_FILE [file join $::quartus(sip_path) "../nios.spd"]
set_global_assignment -library "lib_nios" -name MISC_FILE [file join $::quartus(sip_path) "../../nios.qsys"]

set_global_assignment -library "lib_nios" -name MISC_FILE [file join $::quartus(sip_path) "nios.v"]
