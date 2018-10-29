# signal-benchmark
Benchmark for various C++ signal libraries:
* [fgl::signal](https://github.com/fgoujeon/signal)
* [sigc++](https://github.com/libsigcplusplus/libsigcplusplus)

## Sample result
* Hardware: Intel(R) Core(TM) i5 CPU 750 @ 2.67GHz
* OS: Linux 4.18.16-arch1-1-ARCH 64-bits
* Compiler: g++ 8.2.1
* Compiler options: `g++ -O3 -std=c++17 -DNDEBUG`

```
10 receivers, 100000000 events:
C-style: 3259 ms
fgl::signal 0.1.0: 3252 ms
sigc++ 2.99.11: 8996 ms

10000000 receivers, 10 events:
C-style: 2856 ms
fgl::signal 0.1.0: 2435 ms
sigc++ 2.99.11: 8041 ms
```
