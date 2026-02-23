# musicpp

A minimalist terminal music visualizer.

```
       ╭────────────────────────────────────────────╮
       │                                            │
       │  Radiohead                                 │
       │  Weird Fishes/ Arpeggi                     │
       │                                            │
       │   │    │         │      │    │      │      │
       │   │    │    │    │      │    │    │ │      │
       │   │    │    │    │   │  │    │    │ │  │   │
       │   │    │    │    │   │  │    │    │ │  │   │
       │                                            │
       │  ════════●──────────────────────────────   │
       │  1:42                                4:58  │
       │                                            │
       │                  ◁◁   ▶▶   ▷▷              │
       │                                            │
       ╰────────────────────────────────────────────╯
```

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
xmake
xmake run
```

---

## How audio works

Captures system audio via loopback — no microphone.

- **Windows** — WASAPI loopback
- **Linux** — PulseAudio/PipeWire monitor
- **macOS** — requires [BlackHole](https://github.com/ExistentialAudio/BlackHole)
