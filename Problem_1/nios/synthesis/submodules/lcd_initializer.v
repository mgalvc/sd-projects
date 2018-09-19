// we don't need data because there are no outputs coming from LCD to processor
// maybe we can use result to say that LCD was properly initialized

module lcd_initializer(
	clk,
	clk_en,
	reset,
	done,
	result
);
	
	input clk;
	input clk_en;
	input reset;
	output done;
	output [31:0] result;
	
	assign result = 10001;
endmodule