	component nios is
		port (
			buttons_connection_export : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
			clk_clk                   : in  std_logic                    := 'X';             -- clk
			data_export               : out std_logic_vector(7 downto 0);                    -- export
			en_export                 : out std_logic;                                       -- export
			leds_connection_export    : out std_logic_vector(4 downto 0);                    -- export
			rs_export                 : out std_logic;                                       -- export
			rw_export                 : out std_logic;                                       -- export
			uart_rxd                  : in  std_logic                    := 'X';             -- rxd
			uart_txd                  : out std_logic                                        -- txd
		);
	end component nios;

	u0 : component nios
		port map (
			buttons_connection_export => CONNECTED_TO_buttons_connection_export, -- buttons_connection.export
			clk_clk                   => CONNECTED_TO_clk_clk,                   --                clk.clk
			data_export               => CONNECTED_TO_data_export,               --               data.export
			en_export                 => CONNECTED_TO_en_export,                 --                 en.export
			leds_connection_export    => CONNECTED_TO_leds_connection_export,    --    leds_connection.export
			rs_export                 => CONNECTED_TO_rs_export,                 --                 rs.export
			rw_export                 => CONNECTED_TO_rw_export,                 --                 rw.export
			uart_rxd                  => CONNECTED_TO_uart_rxd,                  --               uart.rxd
			uart_txd                  => CONNECTED_TO_uart_txd                   --                   .txd
		);

