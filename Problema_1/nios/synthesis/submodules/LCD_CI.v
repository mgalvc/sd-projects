module LCD_CI(data, lcd_out);
	input [31:0] data;
	output [31:0] lcd_out;
	
	wire [31:0] data;
	wire [31:0] lcd_out;
	
	LCD CI(data, lcd_out);
	
endmodule