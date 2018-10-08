	component nios is
		port (
			buttons_connection_export       : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			clk_clk                         : in  std_logic                    := 'X';             -- clk
			lcd_custom_0_conduit_end_export : out std_logic;                                       -- export
			lcd_data_export                 : out std_logic_vector(7 downto 0);                    -- export
			lcd_en_export                   : out std_logic;                                       -- export
			lcd_rs_export                   : out std_logic;                                       -- export
			lcd_rw_export                   : out std_logic;                                       -- export
			leds_connection_export          : out std_logic_vector(4 downto 0);                    -- export
			reset_reset_n                   : in  std_logic                    := 'X'              -- reset_n
		);
	end component nios;

	u0 : component nios
		port map (
			buttons_connection_export       => CONNECTED_TO_buttons_connection_export,       --       buttons_connection.export
			clk_clk                         => CONNECTED_TO_clk_clk,                         --                      clk.clk
			lcd_custom_0_conduit_end_export => CONNECTED_TO_lcd_custom_0_conduit_end_export, -- lcd_custom_0_conduit_end.export
			lcd_data_export                 => CONNECTED_TO_lcd_data_export,                 --                 lcd_data.export
			lcd_en_export                   => CONNECTED_TO_lcd_en_export,                   --                   lcd_en.export
			lcd_rs_export                   => CONNECTED_TO_lcd_rs_export,                   --                   lcd_rs.export
			lcd_rw_export                   => CONNECTED_TO_lcd_rw_export,                   --                   lcd_rw.export
			leds_connection_export          => CONNECTED_TO_leds_connection_export,          --          leds_connection.export
			reset_reset_n                   => CONNECTED_TO_reset_reset_n                    --                    reset.reset_n
		);

