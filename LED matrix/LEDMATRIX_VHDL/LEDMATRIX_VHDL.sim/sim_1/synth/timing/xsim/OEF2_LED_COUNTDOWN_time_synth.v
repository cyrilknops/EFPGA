// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Fri Apr 24 16:56:23 2020
// Host        : LAPTOP-1RN17QUT running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               C:/OEF2_LEDMATRIX_COUNTDOWN/OEF2_LED_COUNTDOWN/OEF2_LED_COUNTDOWN.sim/sim_1/synth/timing/xsim/OEF2_LED_COUNTDOWN_time_synth.v
// Design      : OEF2_LED_COUNTDOWN
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7z007sclg225-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* NotValidForBitStream *)
module OEF2_LED_COUNTDOWN
   (LatchPin,
    ClockPin,
    DataPin);
  output LatchPin;
  output ClockPin;
  output [0:0]DataPin;

  wire ClockPin;
  wire [0:0]DataPin;
  wire LatchPin;
  wire buf_i_clk;
  wire i_clk;
  wire NLW_STARTUPE2_inst_CFGCLK_UNCONNECTED;
  wire NLW_STARTUPE2_inst_EOS_UNCONNECTED;
  wire NLW_STARTUPE2_inst_PREQ_UNCONNECTED;

initial begin
 $sdf_annotate("OEF2_LED_COUNTDOWN_time_synth.sdf",,,,"tool_control");
end
  (* box_type = "PRIMITIVE" *) 
  BUFG BUFG_i
       (.I(i_clk),
        .O(buf_i_clk));
  OBUF ClockPin_OBUF_inst
       (.I(1'b0),
        .O(ClockPin));
  OBUF \DataPin_OBUF[0]_inst 
       (.I(1'b0),
        .O(DataPin));
  OBUF LatchPin_OBUF_inst
       (.I(1'b0),
        .O(LatchPin));
  (* box_type = "PRIMITIVE" *) 
  STARTUPE2 #(
    .PROG_USR("FALSE"),
    .SIM_CCLK_FREQ(0.000000)) 
    STARTUPE2_inst
       (.CFGCLK(NLW_STARTUPE2_inst_CFGCLK_UNCONNECTED),
        .CFGMCLK(i_clk),
        .CLK(1'b0),
        .EOS(NLW_STARTUPE2_inst_EOS_UNCONNECTED),
        .GSR(1'b0),
        .GTS(1'b0),
        .KEYCLEARB(1'b0),
        .PACK(1'b0),
        .PREQ(NLW_STARTUPE2_inst_PREQ_UNCONNECTED),
        .USRCCLKO(1'b0),
        .USRCCLKTS(1'b0),
        .USRDONEO(1'b1),
        .USRDONETS(1'b0));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
