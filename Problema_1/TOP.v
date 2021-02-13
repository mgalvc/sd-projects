module TOP(
	input wire [3:0] buttons,
	input wire clock,
	output wire [7:0] lcd_data,
	output wire lcd_en,
	output wire lcd_rs,
	output wire lcd_rw,
	output wire [4:0] leds,
	input wire [7:0] datain_h,
	input wire [7:0] datain_l
);

	wire [3:0] pll_clk;
	wire [7:0] ddio_out;
	wire locked;

	nios nios2(
		.buttons_connection_export(buttons[3:0]),
		.clk_clk(clock),
		.data_export(lcd_data[7:0]),
		.en_export(lcd_en),
		.leds_connection_export(leds[4:0]),
		.rs_export(lcd_rs),
		.rw_export(lcd_rw)
	);
	
	my_pll pll(
		.areset(reset),
		.inclk0(clock),
		.c0(pll_clk[0]),
		.c1(pll_clk[1]),
		.c2(pll_clk[2]),
		.c3(pll_clk[3]),
		.locked(locked)
	);
	
	my_ddio_out ddio(
		.datain_h(datain_h[7:0]),
		.datain_l(datain_l[7:0]),
		.outclock(clock),					// is that right?
		.dataout(ddio_out[7:0])
	);

endmodule