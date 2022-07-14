#!/usr/bin/env python3

# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

import os
import json
import argparse
import shutil


from migen import *

from litex.build.generic_platform import *
from litex.build.osfpga import OSFPGAPlatform

from litex.soc.interconnect import stream
from litex.soc.interconnect.axi import *


# Build --------------------------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="AXI Ram core.")
    parser.formatter_class = lambda prog: argparse.ArgumentDefaultsHelpFormatter(prog,
        max_help_position = 10,
        width             = 120
    )

    

    # Build Parameters.
    build_group = parser.add_argument_group(title="Build parameters")
    build_group.add_argument("--build",         action="store_true", help="Build core.")
    build_group.add_argument("--build-dir",     default="build",     help="Build directory.")
    build_group.add_argument("--build-name",    default=None,        help="Build name.")

    # JSON Import/Template
    json_group = parser.add_argument_group(title="JSON parameters")
    json_group.add_argument("--json",          help="Generate core from JSON file.")
    json_group.add_argument("--json-template", action="store_true", help="Generate JSON template.")

    args = parser.parse_args()

    # Import JSON (Optional) -----------------------------------------------------------------------
    if args.json:
        with open(args.json, 'rt') as f:
            t_args = argparse.Namespace()
            t_args.__dict__.update(json.load(f))
            args = parser.parse_args(namespace=t_args)

    # Create LiteX Core ----------------------------------------------------------------------------
    platform   = OSFPGAPlatform("", io=[], toolchain="raptor")


    rtl_path = os.path.join(os.path.abspath(os.path.dirname(__file__)), "rtl")

    # Enforce build name when not specified.
    if args.build_name is None:
        args.build_name = "AXI_RAM"
    # Remove build extension when specified.
    args.build_name = os.path.splitext(args.build_name)[0]

    # Build
    if args.build:

        build_path = os.path.join(os.path.abspath(os.getcwd()), "build")

        src_files = os.listdir(rtl_path)
        for file_name in src_files:
            full_file_name = os.path.join(rtl_path, file_name)
            if os.path.isfile(full_file_name):
                shutil.copy(full_file_name, args.build_dir)
                
        tcl = []
        # Create Design.
        tcl.append(f"create_design {args.build_name}")
        # Set Device.
        tcl.append(f"target_device {'GEMINI'}")
        # Add Include Path.
        tcl.append(f"add_library_path {rtl_path}")
        # Add Sources.
#        for f, typ, lib in file_name:
#            tcl.append(f"add_design_file {axi_ram.v}")
        # Set Top Module.
        tcl.append(f"set_top_module {args.build_name}")
        # Add Timings Constraints.
#        tcl.append(f"add_constraint_file {args.build_name}.sdc")
        # Run.
         tcl.append("synthesize")
#        tcl.append("packing")
#        tcl.append("place")
#        tcl.append("route")
#        tcl.append("sta")
#        tcl.append("power")
#        tcl.append("bitstream")
        # Generate .tcl.
        with open("build.tcl", "w") as f:
            f.write("\n".join(tcl))




    # Export JSON Template (Optional) --------------------------------------------------------------
    if args.json_template:
        print(json.dumps(vars(args), indent=4))

if __name__ == "__main__":
    main()
