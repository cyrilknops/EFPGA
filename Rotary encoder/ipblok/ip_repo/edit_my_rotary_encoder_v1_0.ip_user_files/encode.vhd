library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity encode is
    Port ( AB : in  STD_LOGIC_VECTOR (1 downto 0);
           Clk : in  STD_LOGIC;
           UD : out  STD_LOGIC_VECTOR (1 downto 0));
end encode;

architecture Behavioral of encode is
signal State: STD_LOGIC_VECTOR (1 downto 0) := "00";
	-- State 0 = "00", State 1 = "01", State 2 = "10", State 3 = "11"
begin
process (CLk)
begin
	if (Clk'event and Clk='1') then
		case State is
			when "00" => -- State 0
				case AB is
					when "00" => UD <= "00"; -- stays at State 0
					when "01" => UD <= "00"; State <= "11"; -- to State 3
					when "10" => UD <= "00"; State <= "01"; -- to State 1
					when others => UD <= "00";
				end case;
			when "01" =>  -- State 1
				case AB is
					when "00" => UD <= "00"; State <= "00"; -- to State 0  -- this pulse might be safer, better against bouncing
					when "10" => UD <= "00"; -- stays at State 1
					when "11" => UD <= "10"; State <= "10"; -- to State 2 --if so then this off
					when others => UD <= "00";
				end case;
			when "10" => -- State 2
					case AB is
					when "01" => UD <= "00"; State <= "11"; -- to State 3
					when "10" => UD <= "00"; State <= "01"; -- to State 1
					when "11" => UD <= "00";  -- stays at State 2
					when others => UD <= "00";
				end case;
			when "11" => -- State 3
				case AB is
					when "00" => UD <= "00"; State <= "00"; -- to State 0
					when "01" => UD <= "00"; -- stays at State 3
					when "11" => UD <= "01"; State <= "10"; -- to State 2 --if so then this off
					when others => UD <= "00";
				end case;
			when others => null;	
		end case;
	end if;
end process;

end Behavioral;
