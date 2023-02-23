// Play sound using built in speaker
static void play_sound(int nFrequence)
{
    int Div;
    int tmp;

    // Set the PIT to the desired frequency
    Div = 1193180 / nFrequence;
    write_port(0x43, 0xb6);
    write_port(0x42, (int)(Div));
    write_port(0x42, (int)(Div >> 8));

    // And play the sound using the PC speaker
    tmp = read_port(0x61);
    if (tmp != (tmp | 3))
    {
        write_port(0x61, tmp | 3);
    }
}

// make it shutup
static void nosound()
{
    int tmp = read_port(0x61) & 0xFC;

    write_port(0x61, tmp);
}

// Make a beep
void beep()
{
    play_sound(1000);
    __std__sleep(0x09FFFFFF);
    nosound();
}
void tone(int hz, int time)
{
    play_sound(hz);
    __std__sleep(time);
    nosound();
}

// В лесу родилась Ёлочка
void music(){
    tone(247, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(370, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(329, 0x10FFFFFF);
    tone(247, 0x10FFFFFF);
    tone(247, 0x10FFFFFF);
    tone(247, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(370, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(497, 0x10FFFFFF);
    __std__sleep(0x15FFFFFF);
    tone(497, 0x10FFFFFF);
    tone(277, 0x10FFFFFF);
    tone(2770, 0x10FFFFFF);
    tone(440, 0x10FFFFFF);
    tone(440, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(370, 0x10FFFFFF);
    tone(329, 0x10FFFFFF);
    tone(247, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(370, 0x10FFFFFF);
    tone(417, 0x10FFFFFF);
    tone(329, 0x10FFFFFF); 
}