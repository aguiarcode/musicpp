# musicpp

A minimalist terminal music visualizer. One line. Reacts to whatever is playing on your device.

```

        Radiohead — Weird Fishes/ Arpeggi


             ╭─╮                 ╭──╮
─────────────╯  ╰────────────────╯   ╰──────────────────╮
                                                         │
─────────────────────────────────────────────────────────╯
         ╭──╮                              ╭─╮
─────────╯   ╰──────────────────────────╮  ╰────────────
                                        │
────────────────────────────────────────╯
```

Play anything. The line moves with it.

---

## Design principles

- One element on screen — the line
- Single color, brightness varies with amplitude
- Motion feels like water, not a graph
- Braille unicode characters for smooth curves
- Track name: centered, dim, above the line

---

## How audio works

Captures system audio via loopback — whatever is playing through your speakers or headphones. No microphone involved.

- **Windows** — WASAPI loopback, works out of the box
- **Linux** — PulseAudio/PipeWire monitor source
- **macOS** — requires [BlackHole](https://github.com/ExistentialAudio/BlackHole)

---

## Dependencies

| Library | Purpose |
|---|---|
| [miniaudio](https://miniaud.io/) | system audio loopback — header only |
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
├── app.h / app.cpp        # main loop
├── app_state.h            # shared state
├── loopback/              # system audio capture via miniaudio
│   ├── Loopback.h
│   └── Loopback.cpp
├── metadata/              # track name via Windows Media Session / MPRIS
│   ├── Metadata.h
│   └── Metadata.cpp
├── dsp/                   # FFT, signal processing
│   ├── FFT.h
│   └── FFT.cpp
├── renderer/              # terminal output, braille encoding
│   ├── Terminal.h
│   └── Terminal.cpp
└── visualizers/           # the line — geometry, interpolation, decay
    ├── LineVisualizer.h
    └── LineVisualizer.cpp
```
