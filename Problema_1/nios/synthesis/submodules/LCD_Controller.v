module LCD_Controller(
	dataa,
	result,
	lcd_out);
	
	input [31:0] dataa;
	
	output [31:0] result;
	output [8:0] lcd_out;
	
	assign result[0] = dataa[0];
	assign lcd_out = dataa[8:0];
endmodule