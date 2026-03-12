// entry point — temporary smoke test for loopback capture
#include "loopback/Loopback.h"
#include <cstdio>
#include <thread>
#include <chrono>
#include <cmath>

int main() {
    Loopback loopback;

    if (!loopback.start()) {
        std::printf("failed to start loopback capture\n");
        return 1;
    }

    std::printf("capturing system audio at %u Hz (%u ch) — play something!\n",
                loopback.sample_rate(), loopback.channels());

    for (int i = 0; i < 30; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        auto samples = loopback.grab(1024);

        // compute RMS level
        float sum = 0.0f;
        for (float s : samples) sum += s * s;
        float rms = std::sqrt(sum / static_cast<float>(samples.size()));

        // simple bar
        int bar_len = static_cast<int>(rms * 200.0f);
        if (bar_len > 50) bar_len = 50;

        std::printf("[");
        for (int j = 0; j < 50; ++j)
            std::printf(j < bar_len ? "#" : " ");
        std::printf("] rms=%.4f\n", rms);
    }

    loopback.stop();
    return 0;
}
