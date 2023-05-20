#define CURRENT_YEAR        2023                            // Change this each year!
 
extern int __cmos_century_register;                               // Set by ACPI table parsing code if possible
 
extern unsigned char __cmos_second;
extern unsigned char __cmos_minute;
extern unsigned char __cmos_hour;
extern unsigned char __cmos_day;
extern unsigned char __cmos_month;
extern unsigned int __cmos_year;
 
//enum {
//      cmos_address = 0x70,
//      cmos_data    = 0x71
//};
 
extern int __cmos_get_update_in_progress_flag();
extern unsigned char __cmos_get_RTC_register(int reg);
extern void __cmos_read_rtc();