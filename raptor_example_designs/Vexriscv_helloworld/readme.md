# Vexriscv SoC with UART & Hello World:
Hello World application code for Vexriscv based SoC.

### Instructions:
Copy the demo folder from litex installation directory ``litex/litex/soc/software/demo`` and paste it inside your project directory. Use the main.c file provided in test folder of this example and replace it with the main.c file located inside your newly copied demo folder in project directory.

## 1. Simulation:
We can simulate the hello world example using litex_sim tool in litex.

Run the following command to generate your SoC:
```
litex_sim --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --no-compile-gateware --sim-debug
```
Before running the simulation, you have to create the binary of your application code residing in demo. The python script below generates the binary from application code as demo.bin, which is later loaded on to the system.

Run the following command to generate .bin file from .py file:
```
python3 ./demo/demo.py --build-path=build/sim
```
Run the following command to execute your applicationcode onto the processor:
```
litex_sim --integrated-main-ram-size=0x10000 --cpu-type vexriscv --ram-init=demo.bin --sim-debug
```


## Output:
![hello_sim.png](./../Pictures/hello_sim.png "Optional title")

## Application
This application code prints a Hello World onto the terminal via Uart.