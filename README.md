# musicpp

A minimalist terminal music visualizer. One line. Reacts to music. Nothing else.

```

          ╭──╮                        ╭─╮
──────────╯    ╰──────────────────────╯   ╰───────
                         ╭──╮
─────────────────────────╯   ╰────────────────────
```

The line is calm when music is quiet. It surges at the drop. Silence is flat — not absent.

---

## Design principles

- One element on screen — the line
- Single color, brightness varies with amplitude
- Motion feels like water, not a graph
- Braille unicode characters for smooth curves
- Track name: centered, dim, above the line

---

## Dependencies

| Library | Purpose |
|---|---|
| [miniaudio](https://miniaud.io/) | cross-platform audio capture — header only |
| [kissfft](https://github.com/mborgerding/kissfft) | FFT — header only |
| [FTXUI](https://github.com/ArthurSonzogni/FTXUI) | terminal rendering |

---

## Build

```bash
cmake -B build
cmake --build build
./build/musicpp
```

---

## Structure

```
src/
├── main.cpp
├── audio/          # capture audio from system or microphone
│   ├── AudioCapture.h
│   └── AudioCapture.cpp
├── dsp/            # FFT and signal processing
│   ├── FFT.h
│   └── FFT.cpp
├── renderer/       # terminal output, braille encoding
│   ├── Terminal.h
│   └── Terminal.cpp
└── visualizer/     # line geometry, wave interpolation, decay
    ├── LineVisualizer.h
    └── LineVisualizer.cpp
```
