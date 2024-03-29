// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.2 (64-bit)
// Version: 2021.2
// Copyright (C) Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module filter3x3_orig_convolution_int_3_s (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        image_r_TDATA,
        image_r_TVALID,
        image_r_TREADY,
        output_r_TDATA,
        output_r_TVALID,
        output_r_TREADY
);

parameter    ap_ST_fsm_state1 = 11'd1;
parameter    ap_ST_fsm_state2 = 11'd2;
parameter    ap_ST_fsm_state3 = 11'd4;
parameter    ap_ST_fsm_state4 = 11'd8;
parameter    ap_ST_fsm_state5 = 11'd16;
parameter    ap_ST_fsm_state6 = 11'd32;
parameter    ap_ST_fsm_state7 = 11'd64;
parameter    ap_ST_fsm_state8 = 11'd128;
parameter    ap_ST_fsm_state9 = 11'd256;
parameter    ap_ST_fsm_state10 = 11'd512;
parameter    ap_ST_fsm_state11 = 11'd1024;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] image_r_TDATA;
input   image_r_TVALID;
output   image_r_TREADY;
output  [31:0] output_r_TDATA;
output   output_r_TVALID;
input   output_r_TREADY;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg image_r_TREADY;
reg[31:0] output_r_TDATA;
reg output_r_TVALID;

(* fsm_encoding = "none" *) reg   [10:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_1;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_1;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_2;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_2;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_3;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_3;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_4;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_4;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_5;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_5;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_6;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_6;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_7;
reg   [31:0] void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_7;
reg    image_r_TDATA_blk_n;
wire    ap_CS_fsm_state2;
wire   [0:0] icmp_ln18_fu_357_p2;
wire    ap_CS_fsm_state3;
wire    ap_CS_fsm_state4;
wire    ap_CS_fsm_state5;
wire    ap_CS_fsm_state6;
wire    ap_CS_fsm_state7;
wire    ap_CS_fsm_state8;
wire    ap_CS_fsm_state9;
reg    output_r_TDATA_blk_n;
reg   [0:0] icmp_ln28_reg_899;
reg   [31:0] window_buffer_10_reg_825;
reg   [31:0] window_buffer_12_reg_832;
reg   [31:0] window_buffer_14_reg_839;
reg   [31:0] window_buffer_16_reg_847;
reg   [31:0] window_buffer_18_reg_855;
reg   [31:0] window_buffer_20_reg_863;
reg   [31:0] window_buffer_22_reg_871;
reg   [31:0] window_buffer_24_reg_878;
wire   [3:0] i_2_fu_363_p2;
reg   [3:0] i_2_reg_888;
reg   [31:0] tmp_reg_893;
wire   [0:0] icmp_ln28_fu_379_p2;
reg   [31:0] tmp_9_reg_903;
reg   [31:0] tmp_10_reg_909;
reg   [31:0] sum_4_load_1_reg_915;
reg   [31:0] tmp_11_reg_920;
reg   [31:0] sum_6_load_1_reg_926;
reg   [31:0] tmp_12_reg_931;
reg   [31:0] sum_8_load_1_reg_937;
reg   [31:0] tmp_13_reg_942;
reg   [31:0] sum_10_load_1_reg_948;
reg   [31:0] tmp_14_reg_953;
wire    ap_CS_fsm_state11;
wire    ap_CS_fsm_state10;
reg   [3:0] i_fu_76;
reg    ap_block_state9;
reg    ap_block_state9_io;
reg   [31:0] sum_1_fu_80;
reg   [31:0] sum_2_fu_84;
reg   [31:0] sum_4_fu_88;
reg   [31:0] sum_6_fu_92;
reg   [31:0] sum_8_fu_96;
reg   [31:0] sum_10_fu_100;
reg   [31:0] window_buffer_fu_104;
reg   [31:0] window_buffer_2_fu_108;
reg   [31:0] window_buffer_1_fu_112;
reg   [31:0] window_buffer_3_fu_116;
reg   [31:0] window_buffer_4_fu_120;
reg   [31:0] window_buffer_5_fu_124;
reg   [31:0] window_buffer_6_fu_128;
reg   [31:0] window_buffer_7_fu_132;
reg   [31:0] window_buffer_8_fu_136;
reg   [31:0] window_buffer_9_fu_140;
reg    ap_block_state2;
reg    ap_block_state4;
reg    ap_block_state4_io;
reg    ap_block_state5;
reg    ap_block_state5_io;
reg    ap_block_state6;
reg    ap_block_state6_io;
reg    ap_block_state7;
reg    ap_block_state7_io;
reg    ap_block_state8;
reg    ap_block_state8_io;
wire   [31:0] sum_fu_406_p2;
wire   [31:0] sum_12_fu_434_p2;
wire   [31:0] sum_13_fu_461_p2;
wire   [31:0] sum_14_fu_488_p2;
wire   [31:0] sum_15_fu_515_p2;
wire   [31:0] sum_16_fu_542_p2;
wire   [2:0] tmp_8_fu_369_p4;
wire   [31:0] add_ln65_fu_385_p2;
wire   [31:0] add_ln65_2_fu_396_p2;
wire   [31:0] add_ln65_3_fu_401_p2;
wire   [31:0] add_ln65_1_fu_391_p2;
wire   [31:0] add_ln65_5_fu_413_p2;
wire   [31:0] add_ln65_7_fu_424_p2;
wire   [31:0] add_ln65_8_fu_429_p2;
wire   [31:0] add_ln65_6_fu_419_p2;
wire   [31:0] add_ln65_10_fu_441_p2;
wire   [31:0] add_ln65_12_fu_452_p2;
wire   [31:0] add_ln65_13_fu_456_p2;
wire   [31:0] add_ln65_11_fu_447_p2;
wire   [31:0] add_ln65_15_fu_468_p2;
wire   [31:0] add_ln65_17_fu_479_p2;
wire   [31:0] add_ln65_18_fu_483_p2;
wire   [31:0] add_ln65_16_fu_474_p2;
wire   [31:0] add_ln65_20_fu_495_p2;
wire   [31:0] add_ln65_22_fu_506_p2;
wire   [31:0] add_ln65_23_fu_510_p2;
wire   [31:0] add_ln65_21_fu_501_p2;
wire   [31:0] add_ln65_25_fu_522_p2;
wire   [31:0] add_ln65_27_fu_533_p2;
wire   [31:0] add_ln65_28_fu_537_p2;
wire   [31:0] add_ln65_26_fu_528_p2;
reg   [10:0] ap_NS_fsm;
reg    ap_ST_fsm_state1_blk;
reg    ap_ST_fsm_state2_blk;
reg    ap_ST_fsm_state3_blk;
reg    ap_ST_fsm_state4_blk;
reg    ap_ST_fsm_state5_blk;
reg    ap_ST_fsm_state6_blk;
reg    ap_ST_fsm_state7_blk;
reg    ap_ST_fsm_state8_blk;
reg    ap_ST_fsm_state9_blk;
wire    ap_ST_fsm_state10_blk;
wire    ap_ST_fsm_state11_blk;
reg    ap_condition_515;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 11'd1;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_1 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_1 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_2 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_2 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_3 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_3 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_4 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_4 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_5 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_5 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_6 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_6 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_7 = 32'd0;
#0 void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_7 = 32'd0;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        i_fu_76 <= 4'd0;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        i_fu_76 <= i_2_reg_888;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_10_fu_100 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_5;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_10_fu_100 <= window_buffer_20_reg_863;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_1_fu_80 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_1_fu_80 <= window_buffer_10_reg_825;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_2_fu_84 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_1;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_2_fu_84 <= window_buffer_12_reg_832;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_4_fu_88 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_2;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_4_fu_88 <= window_buffer_14_reg_839;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_6_fu_92 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_3;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_6_fu_92 <= window_buffer_16_reg_847;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        sum_8_fu_96 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_4;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        sum_8_fu_96 <= window_buffer_18_reg_855;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_1_fu_112 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_1_fu_112 <= tmp_reg_893;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_2_fu_108 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_7;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_2_fu_108 <= window_buffer_24_reg_878;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_3_fu_116 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_1;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_3_fu_116 <= tmp_9_reg_903;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_4_fu_120 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_2;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_4_fu_120 <= tmp_10_reg_909;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_5_fu_124 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_3;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_5_fu_124 <= tmp_11_reg_920;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_6_fu_128 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_4;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_6_fu_128 <= tmp_12_reg_931;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_7_fu_132 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_5;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_7_fu_132 <= tmp_13_reg_942;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_8_fu_136 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_6;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_8_fu_136 <= tmp_14_reg_953;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_9_fu_140 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_7;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_9_fu_140 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        window_buffer_fu_104 <= void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_6;
    end else if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
        window_buffer_fu_104 <= window_buffer_22_reg_871;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        i_2_reg_888 <= i_2_fu_363_p2;
        window_buffer_10_reg_825 <= window_buffer_1_fu_112;
        window_buffer_12_reg_832 <= window_buffer_3_fu_116;
        window_buffer_14_reg_839 <= window_buffer_4_fu_120;
        window_buffer_16_reg_847 <= window_buffer_5_fu_124;
        window_buffer_18_reg_855 <= window_buffer_6_fu_128;
        window_buffer_20_reg_863 <= window_buffer_7_fu_132;
        window_buffer_22_reg_871 <= window_buffer_8_fu_136;
        window_buffer_24_reg_878 <= window_buffer_9_fu_140;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln18_fu_357_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        icmp_ln28_reg_899 <= icmp_ln28_fu_379_p2;
        tmp_reg_893 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state7) & (icmp_ln28_reg_899 == 1'd0))) begin
        sum_10_load_1_reg_948 <= sum_10_fu_100;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state4) & (icmp_ln28_reg_899 == 1'd0))) begin
        sum_4_load_1_reg_915 <= sum_4_fu_88;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state5) & (icmp_ln28_reg_899 == 1'd0))) begin
        sum_6_load_1_reg_926 <= sum_6_fu_92;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state6) & (icmp_ln28_reg_899 == 1'd0))) begin
        sum_8_load_1_reg_937 <= sum_8_fu_96;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        tmp_10_reg_909 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        tmp_11_reg_920 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        tmp_12_reg_931 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        tmp_13_reg_942 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        tmp_14_reg_953 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        tmp_9_reg_903 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1 <= sum_1_fu_80;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_1 <= sum_2_fu_84;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_2 <= sum_4_fu_88;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_3 <= sum_6_fu_92;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_4 <= sum_8_fu_96;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_5 <= sum_10_fu_100;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_6 <= window_buffer_fu_104;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_1_7 <= window_buffer_2_fu_108;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state10)) begin
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2 <= window_buffer_10_reg_825;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_1 <= window_buffer_12_reg_832;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_2 <= window_buffer_14_reg_839;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_3 <= window_buffer_16_reg_847;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_4 <= window_buffer_18_reg_855;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_5 <= window_buffer_20_reg_863;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_6 <= window_buffer_22_reg_871;
        void_convolution_int_3_stream_int_0_int_const_stream_int_0_line_buffer_2_7 <= window_buffer_24_reg_878;
    end
end

assign ap_ST_fsm_state10_blk = 1'b0;

assign ap_ST_fsm_state11_blk = 1'b0;

always @ (*) begin
    if ((ap_start == 1'b0)) begin
        ap_ST_fsm_state1_blk = 1'b1;
    end else begin
        ap_ST_fsm_state1_blk = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln18_fu_357_p2 == 1'd0) & (image_r_TVALID == 1'b0))) begin
        ap_ST_fsm_state2_blk = 1'b1;
    end else begin
        ap_ST_fsm_state2_blk = 1'b0;
    end
end

always @ (*) begin
    if ((image_r_TVALID == 1'b0)) begin
        ap_ST_fsm_state3_blk = 1'b1;
    end else begin
        ap_ST_fsm_state3_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state4_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state4_blk = 1'b1;
    end else begin
        ap_ST_fsm_state4_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state5_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state5_blk = 1'b1;
    end else begin
        ap_ST_fsm_state5_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state6_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state6_blk = 1'b1;
    end else begin
        ap_ST_fsm_state6_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state7_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state7_blk = 1'b1;
    end else begin
        ap_ST_fsm_state7_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state8_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state8_blk = 1'b1;
    end else begin
        ap_ST_fsm_state8_blk = 1'b0;
    end
end

always @ (*) begin
    if (((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)))) begin
        ap_ST_fsm_state9_blk = 1'b1;
    end else begin
        ap_ST_fsm_state9_blk = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state11) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0)))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_state8) | (1'b1 == ap_CS_fsm_state7) | (1'b1 == ap_CS_fsm_state6) | (1'b1 == ap_CS_fsm_state5) | (1'b1 == ap_CS_fsm_state4) | (1'b1 == ap_CS_fsm_state3) | (1'b1 == ap_CS_fsm_state9) | ((icmp_ln18_fu_357_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
        image_r_TDATA_blk_n = image_r_TVALID;
    end else begin
        image_r_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state8_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state8)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state7_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state7)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state6_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state6)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state5_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state5)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state4_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state4)) | ((image_r_TVALID == 1'b1) & (1'b1 == ap_CS_fsm_state3)) | (~((icmp_ln18_fu_357_p2 == 1'd0) & (image_r_TVALID == 1'b0)) & (icmp_ln18_fu_357_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9)))) begin
        image_r_TREADY = 1'b1;
    end else begin
        image_r_TREADY = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_condition_515)) begin
        if ((1'b1 == ap_CS_fsm_state9)) begin
            output_r_TDATA = sum_16_fu_542_p2;
        end else if ((1'b1 == ap_CS_fsm_state8)) begin
            output_r_TDATA = sum_15_fu_515_p2;
        end else if ((1'b1 == ap_CS_fsm_state7)) begin
            output_r_TDATA = sum_14_fu_488_p2;
        end else if ((1'b1 == ap_CS_fsm_state6)) begin
            output_r_TDATA = sum_13_fu_461_p2;
        end else if ((1'b1 == ap_CS_fsm_state5)) begin
            output_r_TDATA = sum_12_fu_434_p2;
        end else if ((1'b1 == ap_CS_fsm_state4)) begin
            output_r_TDATA = sum_fu_406_p2;
        end else begin
            output_r_TDATA = 'bx;
        end
    end else begin
        output_r_TDATA = 'bx;
    end
end

always @ (*) begin
    if ((((1'b1 == ap_CS_fsm_state8) & (icmp_ln28_reg_899 == 1'd0)) | ((1'b1 == ap_CS_fsm_state7) & (icmp_ln28_reg_899 == 1'd0)) | ((1'b1 == ap_CS_fsm_state6) & (icmp_ln28_reg_899 == 1'd0)) | ((1'b1 == ap_CS_fsm_state5) & (icmp_ln28_reg_899 == 1'd0)) | ((1'b1 == ap_CS_fsm_state4) & (icmp_ln28_reg_899 == 1'd0)) | ((1'b1 == ap_CS_fsm_state9) & (icmp_ln28_reg_899 == 1'd0)))) begin
        output_r_TDATA_blk_n = output_r_TREADY;
    end else begin
        output_r_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state8_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state8) & (icmp_ln28_reg_899 == 1'd0)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state7_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state7) & (icmp_ln28_reg_899 == 1'd0)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state6_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state6) & (icmp_ln28_reg_899 == 1'd0)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state5_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state5) & (icmp_ln28_reg_899 == 1'd0)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state4_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state4) & (icmp_ln28_reg_899 == 1'd0)) | (~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9) & (icmp_ln28_reg_899 == 1'd0)))) begin
        output_r_TVALID = 1'b1;
    end else begin
        output_r_TVALID = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if ((~((icmp_ln18_fu_357_p2 == 1'd0) & (image_r_TVALID == 1'b0)) & (icmp_ln18_fu_357_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else if ((~((icmp_ln18_fu_357_p2 == 1'd0) & (image_r_TVALID == 1'b0)) & (icmp_ln18_fu_357_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((image_r_TVALID == 1'b1) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state4_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end
        end
        ap_ST_fsm_state5 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state5_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state6 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state6_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state6))) begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state7 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state7_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state7))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state7;
            end
        end
        ap_ST_fsm_state8 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state8_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state8))) begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end
        end
        ap_ST_fsm_state9 : begin
            if ((~((image_r_TVALID == 1'b0) | (1'b1 == ap_block_state9_io) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (1'b1 == ap_CS_fsm_state9))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            ap_NS_fsm = ap_ST_fsm_state1;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln65_10_fu_441_p2 = (image_r_TDATA + sum_8_fu_96);

assign add_ln65_11_fu_447_p2 = (add_ln65_10_fu_441_p2 + tmp_10_reg_909);

assign add_ln65_12_fu_452_p2 = (window_buffer_14_reg_839 + sum_4_load_1_reg_915);

assign add_ln65_13_fu_456_p2 = (add_ln65_12_fu_452_p2 + window_buffer_18_reg_855);

assign add_ln65_15_fu_468_p2 = (image_r_TDATA + sum_10_fu_100);

assign add_ln65_16_fu_474_p2 = (add_ln65_15_fu_468_p2 + tmp_11_reg_920);

assign add_ln65_17_fu_479_p2 = (window_buffer_16_reg_847 + sum_6_load_1_reg_926);

assign add_ln65_18_fu_483_p2 = (add_ln65_17_fu_479_p2 + window_buffer_20_reg_863);

assign add_ln65_1_fu_391_p2 = (add_ln65_fu_385_p2 + tmp_reg_893);

assign add_ln65_20_fu_495_p2 = (image_r_TDATA + window_buffer_fu_104);

assign add_ln65_21_fu_501_p2 = (add_ln65_20_fu_495_p2 + tmp_12_reg_931);

assign add_ln65_22_fu_506_p2 = (window_buffer_18_reg_855 + sum_8_load_1_reg_937);

assign add_ln65_23_fu_510_p2 = (add_ln65_22_fu_506_p2 + window_buffer_22_reg_871);

assign add_ln65_25_fu_522_p2 = (image_r_TDATA + window_buffer_2_fu_108);

assign add_ln65_26_fu_528_p2 = (add_ln65_25_fu_522_p2 + tmp_13_reg_942);

assign add_ln65_27_fu_533_p2 = (window_buffer_20_reg_863 + sum_10_load_1_reg_948);

assign add_ln65_28_fu_537_p2 = (add_ln65_27_fu_533_p2 + window_buffer_24_reg_878);

assign add_ln65_2_fu_396_p2 = (window_buffer_10_reg_825 + sum_1_fu_80);

assign add_ln65_3_fu_401_p2 = (add_ln65_2_fu_396_p2 + window_buffer_14_reg_839);

assign add_ln65_5_fu_413_p2 = (image_r_TDATA + sum_6_fu_92);

assign add_ln65_6_fu_419_p2 = (add_ln65_5_fu_413_p2 + tmp_9_reg_903);

assign add_ln65_7_fu_424_p2 = (window_buffer_12_reg_832 + sum_2_fu_84);

assign add_ln65_8_fu_429_p2 = (add_ln65_7_fu_424_p2 + window_buffer_16_reg_847);

assign add_ln65_fu_385_p2 = (image_r_TDATA + sum_4_fu_88);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

always @ (*) begin
    ap_block_state2 = ((icmp_ln18_fu_357_p2 == 1'd0) & (image_r_TVALID == 1'b0));
end

always @ (*) begin
    ap_block_state4 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state4_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_block_state5 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state5_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_block_state6 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state6_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_block_state7 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state7_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_block_state8 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state8_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_block_state9 = ((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0)));
end

always @ (*) begin
    ap_block_state9_io = ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0));
end

always @ (*) begin
    ap_condition_515 = (~((image_r_TVALID == 1'b0) | ((output_r_TREADY == 1'b0) & (icmp_ln28_reg_899 == 1'd0))) & (icmp_ln28_reg_899 == 1'd0));
end

assign i_2_fu_363_p2 = (i_fu_76 + 4'd1);

assign icmp_ln18_fu_357_p2 = ((i_fu_76 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln28_fu_379_p2 = ((tmp_8_fu_369_p4 == 3'd0) ? 1'b1 : 1'b0);

assign sum_12_fu_434_p2 = (add_ln65_8_fu_429_p2 + add_ln65_6_fu_419_p2);

assign sum_13_fu_461_p2 = (add_ln65_13_fu_456_p2 + add_ln65_11_fu_447_p2);

assign sum_14_fu_488_p2 = (add_ln65_18_fu_483_p2 + add_ln65_16_fu_474_p2);

assign sum_15_fu_515_p2 = (add_ln65_23_fu_510_p2 + add_ln65_21_fu_501_p2);

assign sum_16_fu_542_p2 = (add_ln65_28_fu_537_p2 + add_ln65_26_fu_528_p2);

assign sum_fu_406_p2 = (add_ln65_3_fu_401_p2 + add_ln65_1_fu_391_p2);

assign tmp_8_fu_369_p4 = {{i_fu_76[3:1]}};

endmodule //filter3x3_orig_convolution_int_3_s
