# musicpp

A minimalist terminal music visualizer.

```
          Radiohead — Everything In Its Right Place


  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
     |  |  |  |  |  |  |  |  |  |  |  |  |
        |  |  |  |  |  |  |  |  |  |  |
           |  |  |  |  |  |  |  |  |
              |  |  |  |  |  |  |
```

## Dependencies

- [miniaudio](https://miniaud.io/) — audio capture
- [kissfft](https://github.com/mborgerding/kissfft) — FFT
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI) — terminal rendering

## Build

```bash
cmake -B build
cmake --build build
./build/musicpp
```

## Structure

```
src/
├── main.cpp
├── audio/        # audio capture
├── dsp/          # FFT and signal processing
├── renderer/     # terminal output
└── visualizer/   # bar geometry and animation
```
