
module nios (
	buttons_connection_export,
	clk_clk,
	lcd_custom_0_conduit_end_export,
	lcd_data_export,
	lcd_en_export,
	lcd_rs_export,
	lcd_rw_export,
	leds_connection_export,
	reset_reset_n);	

	input	[3:0]	buttons_connection_export;
	input		clk_clk;
	output		lcd_custom_0_conduit_end_export;
	output	[7:0]	lcd_data_export;
	output		lcd_en_export;
	output		lcd_rs_export;
	output		lcd_rw_export;
	output	[4:0]	leds_connection_export;
	input		reset_reset_n;
endmodule
