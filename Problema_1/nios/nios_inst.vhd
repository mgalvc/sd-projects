	component nios is
		port (
			buttons_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			clk_clk                   : in  std_logic                    := 'X';             -- clk
			leds_connection_export    : out std_logic_vector(4 downto 0);                    -- export
			reset_reset_n             : in  std_logic                    := 'X';             -- reset_n
			rs_lcd_rs                 : out std_logic;                                       -- lcd_rs
			data_lcd_data             : out std_logic_vector(7 downto 0);                    -- lcd_data
			lcd_rw_export             : out std_logic;                                       -- export
			lcd_en_export             : out std_logic                                        -- export
		);
	end component nios;

	u0 : component nios
		port map (
			buttons_connection_export => CONNECTED_TO_buttons_connection_export, -- buttons_connection.export
			clk_clk                   => CONNECTED_TO_clk_clk,                   --                clk.clk
			leds_connection_export    => CONNECTED_TO_leds_connection_export,    --    leds_connection.export
			reset_reset_n             => CONNECTED_TO_reset_reset_n,             --              reset.reset_n
			rs_lcd_rs                 => CONNECTED_TO_rs_lcd_rs,                 --                 rs.lcd_rs
			data_lcd_data             => CONNECTED_TO_data_lcd_data,             --               data.lcd_data
			lcd_rw_export             => CONNECTED_TO_lcd_rw_export,             --             lcd_rw.export
			lcd_en_export             => CONNECTED_TO_lcd_en_export              --             lcd_en.export
		);

