## AXI-RAM CORE GENERATION

Run the following command to generate .tcl file and rtl:

```
python3 axi_ram.py --build-name=axi_ram --build
```

Run the following command to generate json template on terminal:
```
python3 axi_ram.py --json-template
```

Compilation with Raptor:
```
raptor --batch --script path to Tcl script
```
