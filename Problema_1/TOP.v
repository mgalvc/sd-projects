module TOP(
	input wire [3:0] buttons,
	input wire clock,
	output wire [7:0] lcd_data,
	output wire lcd_en,
	output wire lcd_rs,
	output wire lcd_rw,
	output wire [4:0] leds
);

	nios nios2(
		.buttons_connection_export(buttons[3:0]),
		.clk_clk(clock),
		.data_export(lcd_data[7:0]),
		.en_export(lcd_en),
		.leds_connection_export(leds[4:0]),
		.rs_export(lcd_rs),
		.rw_export(lcd_rw)
	);

endmodule