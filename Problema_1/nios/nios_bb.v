
module nios (
	buttons_connection_export,
	clk_clk,
	leds_connection_export,
	reset_reset_n,
	rs_lcd_rs,
	data_lcd_data,
	lcd_rw_export,
	lcd_en_export);	

	input	[3:0]	buttons_connection_export;
	input		clk_clk;
	output	[4:0]	leds_connection_export;
	input		reset_reset_n;
	output		rs_lcd_rs;
	output	[7:0]	data_lcd_data;
	output		lcd_rw_export;
	output		lcd_en_export;
endmodule
