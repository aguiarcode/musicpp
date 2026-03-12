#pragma once

#include <vector>
#include <mutex>
#include <cstdint>

struct ma_device;

class Loopback {
public:
    Loopback();
    ~Loopback();

    bool start();
    void stop();

    // copies current buffer out (thread-safe)
    std::vector<float> grab(std::size_t num_samples) const;

    uint32_t sample_rate() const;
    uint32_t channels() const;

private:
    static void data_callback(ma_device* device, void* output, const void* input, uint32_t frame_count);
    void push(const float* frames, uint32_t frame_count);

    ma_device* m_device = nullptr;

    mutable std::mutex m_mutex;
    std::vector<float> m_buffer;        // ring of mono samples
    std::size_t        m_write_pos = 0;
    static constexpr std::size_t kBufferSize = 8192;

    uint32_t m_sample_rate = 0;
    uint32_t m_channels    = 0;
    bool     m_running     = false;
};
