process __desktop_process;

void __desktop_offset()
{
    __graphics_init();
    __plasmaUI_Button(20,20,80,20,GREEN1,"Button");
}

void __desktop_init()
{
    __desktop_process.offset = *__desktop_offset;
}