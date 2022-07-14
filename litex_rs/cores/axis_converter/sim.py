#!/usr/bin/env python3

# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

import argparse

from migen import *

from litex.build.sim import SimPlatform
from litex.build.sim.config import SimConfig

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *

from litex.soc.interconnect import stream
from litex.soc.interconnect import axi

# Platform -----------------------------------------------------------------------------------------

_io = [("clk_sys",  0, Pins(1))]

class Platform(SimPlatform):
    default_clk_name = "clk_sys"
    def __init__(self):
        SimPlatform.__init__(self, "SIM", _io)

# Sim ----------------------------------------------------------------------------------------------

class SimSoC(SoCCore):
    def __init__(self, sys_clk_freq=int(1e6)):
        # Platform ---------------------------------------------------------------------------------
        platform  = Platform()
        self.comb += platform.trace.eq(1) # Always enable tracing.

        # SoC --------------------------------------------------------------------------------------
        SoCMini.__init__(self, platform, clk_freq=sys_clk_freq)


        # AXI Stream Converter Test ----------------------------------------------------------------

        # The AXI Stream Converter generator is tested by connecting a 64-32-bit converter to a 32-64-bit
        # converter and verifying that the output data matches input data.

        # Generate 2 AXI Stream Converter: 64-bit to 32-bit and 32-bit to 64-bit.
        os.system("./axis_converter.py --core-in-width=64 --core-out-width=32 --build-dir=./ --build")
        os.system("./axis_converter.py --core-in-width=32 --core-out-width=64 --build-dir=./ --build")

        # AXI Interfaces.
        axis_in  = axi.AXIStreamInterface(data_width=64)
        axis_out = axi.AXIStreamInterface(data_width=64)
        axis_32b = axi.AXIStreamInterface(data_width=32)

        # Pattern Generator.
        self.sync += [
            axis_in.valid.eq(1),
            If(axis_in.ready,
                axis_in.data.eq(axis_in.data + 1)
            )
        ]

        # 64-bit to 32-bit Converter.
        self.specials += Instance("axis_converter_64b_to_32b",
            i_axis_clk        = ClockSignal("sys"),
            i_axis_rst        = ResetSignal("sys"),
            i_axis_in_tvalid  = axis_in.valid,
            i_axis_in_tlast   = axis_in.last,
            o_axis_in_tready  = axis_in.ready,
            i_axis_in_tdata   = axis_in.data,
            o_axis_out_tvalid = axis_32b.valid,
            o_axis_out_tlast  = axis_32b.last,
            i_axis_out_tready = axis_32b.ready,
            o_axis_out_tdata  = axis_32b.data,
        )
        platform.add_source("axis_converter_64b_to_32b.v")

        # 32-bit to 64-bit Converter.
        self.specials += Instance("axis_converter_32b_to_64b",
            i_axis_clk        = ClockSignal("sys"),
            i_axis_rst        = ResetSignal("sys"),
            i_axis_in_tvalid  = axis_32b.valid,
            i_axis_in_tlast   = axis_32b.last,
            o_axis_in_tready  = axis_32b.ready,
            i_axis_in_tdata   = axis_32b.data,
            o_axis_out_tvalid = axis_out.valid,
            o_axis_out_tlast  = axis_out.last,
            i_axis_out_tready = axis_out.ready,
            o_axis_out_tdata  = axis_out.data,
        )
        platform.add_source("axis_converter_32b_to_64b.v")


        # Pattern Checker.
        data   = Signal(64)
        cycles = Signal(32)
        errors = Signal(32)
        self.sync += [
            axis_out.ready.eq(1),
            If(axis_out.valid,
                cycles.eq(cycles + 1),
                If(axis_out.data != data,
                    Display("%x %x", axis_out.data, data),
                    errors.eq(errors + 1)
                ),
                data.eq(data + 1),
            ),
            If(cycles == 1000,
                Display("Errors: %d", errors),
                Finish()
            )
        ]

# Build --------------------------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="AXI Stream Converter core simulation.")
    parser.add_argument("--trace", action="store_true", help="Enable VCD tracing.")
    args = parser.parse_args()
    sim_config = SimConfig()
    sim_config.add_clocker(clk="clk_sys", freq_hz=int(1e6))

    soc = SimSoC()
    builder = Builder(soc, output_dir="build")
    builder.build(sim_config=sim_config, trace=args.trace)


if __name__ == "__main__":
    main()
