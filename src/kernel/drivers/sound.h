static void __driver_audio_play_sound(int nFrequence)
{
    int Div;
    int tmp;

    Div = 1193180 / nFrequence;
    write_port(0x43, 0xb6);
    write_port(0x42, (int)(Div));
    write_port(0x42, (int)(Div >> 8));

    tmp = read_port(0x61);
    if (tmp != (tmp | 3))
    {
        write_port(0x61, tmp | 3);
    }
}

static void __driver_audio_nosound()
{
    int tmp = read_port(0x61) & 0xFC;

    write_port(0x61, tmp);
}

void __driver_audio_beeps()
{
    __driver_audio_play_sound(1000);
    __std__sleep(0x09FFFFFF);
    __driver_audio_nosound();
}

void __driver_audio_tone(int hz, int time)
{
    __driver_audio_play_sound(hz);
    __std__sleep(time);
    __driver_audio_nosound();
}

// В лесу родилась Ёлочка
void __driver_audio_music(){
    __driver_audio_tone(247, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(370, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(329, 0x10FFFFFF);
    __driver_audio_tone(247, 0x10FFFFFF);
    __driver_audio_tone(247, 0x10FFFFFF);
    __driver_audio_tone(247, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(370, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(497, 0x10FFFFFF);
    __std__sleep(0x15FFFFFF);
    __driver_audio_tone(497, 0x10FFFFFF);
    __driver_audio_tone(277, 0x10FFFFFF);
    __driver_audio_tone(2770, 0x10FFFFFF);
    __driver_audio_tone(440, 0x10FFFFFF);
    __driver_audio_tone(440, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(370, 0x10FFFFFF);
    __driver_audio_tone(329, 0x10FFFFFF);
    __driver_audio_tone(247, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(370, 0x10FFFFFF);
    __driver_audio_tone(417, 0x10FFFFFF);
    __driver_audio_tone(329, 0x10FFFFFF); 
}