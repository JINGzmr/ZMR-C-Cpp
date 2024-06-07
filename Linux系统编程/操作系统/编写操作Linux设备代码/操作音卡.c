#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#define PCM_DEVICE "default"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <wav-file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Cannot open file");
        return 1;
    }

    // 读取WAV文件头部
    char buffer[44];
    fread(buffer, 1, 44, file);

    // 初始化ALSA PCM设备
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    unsigned int rate = 44100;
    int channels = 2;
    int pcm;

    if ((pcm = snd_pcm_open(&pcm_handle, PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        fprintf(stderr, "ERROR: Can't open \"%s\" PCM device. %s\n", PCM_DEVICE, snd_strerror(pcm));
        return 1;
    }

    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, channels);
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, NULL);
    snd_pcm_hw_params(pcm_handle, params);

    snd_pcm_uframes_t frames;
    snd_pcm_hw_params_get_period_size(params, &frames, 0);

    int size = frames * channels * 2; // 2 bytes/sample, 2 channels
    char *data = (char *)malloc(size);

    while (1) {
        int ret = fread(data, 1, size, file);
        if (ret == 0) {
            break;
        } else if (ret != size) {
            fprintf(stderr, "Short read: read %d bytes\n", ret);
        }

        if (snd_pcm_writei(pcm_handle, data, frames) == -EPIPE) {
            snd_pcm_prepare(pcm_handle);
        }
    }

    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    free(data);
    fclose(file);

    return 0;
}
