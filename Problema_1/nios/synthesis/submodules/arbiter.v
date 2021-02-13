module arbiter(
	input [7:0] datain,
	input wire rx,
	input clk,
	input reset,
	output wire tx,
	output wire [7:0] rxdata,
	output reg [7:0] sensor_result,
	input clk_en
);

	reg enable = 0;
	reg [2:0] state, next_state = 0;
	reg [7:0] data_rcv;

	wire tx_busy;//output
	wire rdy;
	wire rdy_clr; // ?
	
	
	parameter IDLE = 3'b000;
	parameter RECV = 3'b001;
	parameter CHECK = 3'b010;
	parameter WAIT_ALARM = 3'b011;
	parameter RESULT = 3'b100;	
	
	
	parameter KEY = 8'b00110111;
	parameter ZERO = 8'b00000000;
	
	

	uart U(.din(datain),
	       .wr_en(enable),
	       .clk_50m(clk),
	       .tx(tx),
	       .tx_busy(tx_busy),
	       .rx(rx),
	       .rdy(rdy),
	       .rdy_clr(rdy_clr),
	       .dout(rxdata));
			 
	
	always @(clk, state, rdy) begin
		if(reset)
			next_state = IDLE;
		else begin
			state = next_state;
		
			case (state) 
				IDLE: begin
					sensor_result = ZERO;
					if (rdy && rxdata) begin
						next_state <= RECV;
						data_rcv <= rxdata;
					end
					else
						next_state = IDLE;
				end
				
				RECV: begin
				
					if (rdy && rxdata) begin
						if ((data_rcv ^ KEY) == rxdata) begin
							next_state <= RESULT;
							sensor_result <= data_rcv;
						end
						else
							next_state = WAIT_ALARM;
						
					end
				
				end
				
				WAIT_ALARM: begin
					if (rdy && rxdata) begin
						if (rxdata == (ZERO ^ KEY)) begin
							data_rcv <= ZERO ^ KEY;
							next_state <= RESULT;
						end
						else
							next_state = IDLE;
					end
				
				end
				
				RESULT: begin
					if (clk_en) begin
						sensor_result = data_rcv;
						next_state = IDLE;
					end
				end
				
			endcase  // case
		end
	end // end always state,
	
	
	always @(posedge clk) begin
		if (~tx_busy && datain)
			enable = 1'b1;
		else
			enable = 0;
		
	end

endmodule