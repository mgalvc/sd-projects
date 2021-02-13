
module nios (
	buttons_connection_export,
	clk_clk,
	data_export,
	en_export,
	leds_connection_export,
	rs_export,
	rw_export,
	uart_rxd,
	uart_txd,
	arbiter_conduit_writeresponsevalid_n,
	arbiter_conduit_beginbursttransfer);	

	input	[3:0]	buttons_connection_export;
	input		clk_clk;
	output	[7:0]	data_export;
	output		en_export;
	output	[4:0]	leds_connection_export;
	output		rs_export;
	output		rw_export;
	input		uart_rxd;
	output		uart_txd;
	output		arbiter_conduit_writeresponsevalid_n;
	input		arbiter_conduit_beginbursttransfer;
endmodule
