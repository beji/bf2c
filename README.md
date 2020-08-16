# bf2c

A very basic "compiler" that transforms brainfuck into C code.

## Usage

### All in one command

``` sh
make IN=examples/hello.bf MODE=Release
```

Pass the program you want to run with the IN paramter

### build the "compiler"

``` sh
make compiler MODE=Release
```

this will emit the program under `_build/bf2c`. You can then pass a program to it through stdin, .e.g `_build/bf2c < examples/hello.bf` and it will print the output to stdout for further use (mostly passing it to a file and then compiling that)

