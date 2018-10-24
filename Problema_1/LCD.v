module LCD (
	clk,
	dataa,
	datab,
	reset,
	lcd_rs,
	lcd_rw,
	lcd_en,
	lcd_data
);

	input wire [7:0] dataa;
	input wire datab;
	input clk, reset;
	
	output lcd_rw;
	output reg lcd_rs, lcd_en;
	output reg[7:0] lcd_data;	
	
	wire rData = dataa != 0;
	assign lcd_rw = 0;
	
	reg [2:0] count;
	always @(posedge clk) if(rData | (count!=0)) count <= count + 1;

	always @(posedge clk) begin
		if(lcd_en == 0)
		  lcd_en <= rData;
		else
		  lcd_en <= (count!=6);
	end
	
	always @(posedge clk) begin
		lcd_data <= dataa;
		lcd_rs <= datab;
	end
  
endmodule

