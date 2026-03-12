#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "Loopback.h"
#include <algorithm>
#include <cstring>

Loopback::Loopback()
    : m_buffer(kBufferSize, 0.0f) {}

Loopback::~Loopback() {
    stop();
}

bool Loopback::start() {
    if (m_running) return true;

    m_device = new ma_device;

    ma_device_config config = ma_device_config_init(ma_device_type_loopback);
    config.capture.format   = ma_format_f32;
    config.capture.channels = 2;
    config.sampleRate       = 44100;
    config.dataCallback     = &Loopback::data_callback;
    config.pUserData        = this;

    if (ma_device_init(nullptr, &config, m_device) != MA_SUCCESS) {
        delete m_device;
        m_device = nullptr;
        return false;
    }

    m_sample_rate = m_device->sampleRate;
    m_channels    = m_device->capture.channels;

    if (ma_device_start(m_device) != MA_SUCCESS) {
        ma_device_uninit(m_device);
        delete m_device;
        m_device = nullptr;
        return false;
    }

    m_running = true;
    return true;
}

void Loopback::stop() {
    if (!m_running) return;
    ma_device_uninit(m_device);
    delete m_device;
    m_device  = nullptr;
    m_running = false;
}

void Loopback::data_callback(ma_device* device, void* /*output*/, const void* input, uint32_t frame_count) {
    auto* self = static_cast<Loopback*>(device->pUserData);
    self->push(static_cast<const float*>(input), frame_count);
}

void Loopback::push(const float* frames, uint32_t frame_count) {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (uint32_t i = 0; i < frame_count; ++i) {
        // downmix to mono by averaging channels
        float mono = 0.0f;
        for (uint32_t ch = 0; ch < m_channels; ++ch) {
            mono += frames[i * m_channels + ch];
        }
        mono /= static_cast<float>(m_channels);

        m_buffer[m_write_pos] = mono;
        m_write_pos = (m_write_pos + 1) % kBufferSize;
    }
}

std::vector<float> Loopback::grab(std::size_t num_samples) const {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (num_samples > kBufferSize) num_samples = kBufferSize;

    std::vector<float> out(num_samples);

    // read the most recent num_samples from the ring buffer
    std::size_t start = (m_write_pos + kBufferSize - num_samples) % kBufferSize;
    for (std::size_t i = 0; i < num_samples; ++i) {
        out[i] = m_buffer[(start + i) % kBufferSize];
    }
    return out;
}

uint32_t Loopback::sample_rate() const { return m_sample_rate; }
uint32_t Loopback::channels() const    { return m_channels; }
