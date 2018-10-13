
module nios (
	buttons_connection_export,
	clk_clk,
	leds_connection_export,
	reset_reset_n,
	data_export,
	rs_export,
	rw_export,
	en_export);	

	input	[3:0]	buttons_connection_export;
	input		clk_clk;
	output	[4:0]	leds_connection_export;
	input		reset_reset_n;
	output	[7:0]	data_export;
	output		rs_export;
	output		rw_export;
	output		en_export;
endmodule
