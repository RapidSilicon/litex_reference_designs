## AXI-GPIO CORE GENERATION

Run the following command to generate .tcl file and rtl:

```
python3 axi_gpio.py --build-dir=./ --build-name=axi_gpio --build
```

Run the following command to generate json template on terminal:
```
python3 axi_gpio.py --json-template
```

Compilation with Raptor:
```
raptor --batch --script path to Tcl script
```
