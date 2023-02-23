static void __driver_audio_play_sound(int nFrequence)
{
    int __driver_audio_Div;
    int __driver_audio_tmp;

    __driver_audio_Div = 1193180 / nFrequence;
    write_port(0x43, 0xb6);
    write_port(0x42, (int)(__driver_audio_Div));
    write_port(0x42, (int)(__driver_audio_Div >> 8));

    __driver_audio_tmp = read_port(0x61);
    if (__driver_audio_tmp != (__driver_audio_tmp | 3)) {
        write_port(0x61, __driver_audio_tmp | 3);
    }
}

static void __driver_audio_nosound()
{
    int __driver_audio_tmp2 = read_port(0x61) & 0xFC;
    write_port(0x61, __driver_audio_tmp2);
}

void __driver_audio_beeps()
{
    __driver_audio_play_sound(1000);
    __std__sleep(0x09FFFFFF);
    __driver_audio_nosound();
}

void __driver_audio_tone(int __driver_audio_hz, int __driver_audio_time)
{
    __driver_audio_play_sound(__driver_audio_hz);
    __std__sleep(__driver_audio_time);
    __driver_audio_nosound();
}