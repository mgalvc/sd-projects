
module nios (
	buttons_connection_export,
	clk_clk,
	data_export,
	en_export,
	leds_connection_export,
	reset_reset_n,
	rs_export,
	rw_export);	

	input	[3:0]	buttons_connection_export;
	input		clk_clk;
	output	[7:0]	data_export;
	output		en_export;
	output	[4:0]	leds_connection_export;
	input		reset_reset_n;
	output		rs_export;
	output		rw_export;
endmodule
