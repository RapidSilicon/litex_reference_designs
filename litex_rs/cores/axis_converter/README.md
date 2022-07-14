## AXIS-CONVERTER CORE GENERATION

Run the following command to generate .tcl file and rtl:

```
python3 axis_converter.py --build-dir=./ --build-name=axis_converter --build
```

Run the following command to generate json template on terminal:
```
python3 axi_converter.py --json-template
```

Compilation with Raptor:
```
raptor --batch --script Path to TCL script
```
