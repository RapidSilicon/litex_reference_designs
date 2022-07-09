hello_world:
			mkdir litex_example_hello_world
			~/litex_instll/litex_rs/example_designs/vexriscv_helloworld/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --no-compile-gateware --sim-debug
			python3 ~/litex_instll/litex_rs/example_designs/vexriscv_helloworld/test/demo/demo.py --build-path=build/sim
			~/litex_instll/litex_rs/example_designs/vexriscv_helloworld/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --ram-init=demo.bin --sim-debug

axi_ram:
			mkdir litex_example_axiram
			~/litex_instll/litex_rs/example_designs/vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --axiram --no-compile-gateware --sim-debug
			python3 ~/litex_instll/litex_rs/example_designs/vexriscv_axi_ram/test/demo/demo.py --build-path=build/sim
			~/litex_instll/litex_rs/example_designs/vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --axiram --ram-init=demo.bin --sim-debug

axi_gpio:
			mkdir litex_example_axigpio
			~/litex_instll/litex_rs/example_designs/vexriscv_axi_gpio_led/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --axigpio --no-compile-gateware --sim-debug
			python3 ~/litex_instll/litex_rs/example_designs/vexriscv_axi_gpio_led/test/demo/demo.py --build-path=build/sim
			~/litex_instll/litex_rs/example_designs/vexriscv_axi_gpio_led/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --axigpio --ram-init=demo.bin --sim-debug --trace

clean:
		rm -rf litex_example*
