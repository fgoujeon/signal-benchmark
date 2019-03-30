# signal-benchmark
Benchmark for various C++ signal libraries:
* [fgsig](https://github.com/fgoujeon/signal)
* [sigc++](https://github.com/libsigcplusplus/libsigcplusplus)

## Sample result
* Hardware: Intel(R) Core(TM) i5 CPU 750 @ 2.67GHz
* OS: Linux 5.0.3-arch1-1-ARCH 64-bits
* Compiler: g++ 8.2.1
* Compiler options: `g++ -O3 -std=c++17 -DNDEBUG`

```
10 receivers, 100000000 events:
C-style: 3310 ms
fgsig 0.2.0: 3382 ms
sigc++ 2.99.11: 9141 ms

10000000 receivers, 10 events:
C-style: 2949 ms
fgsig 0.2.0: 4378 ms
sigc++ 2.99.11: 7992 ms
```
