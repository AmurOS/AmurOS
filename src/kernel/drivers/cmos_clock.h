#define CURRENT_YEAR        2023                            // Change this each year!
 
int __cmos_century_register = 0x00;                                // Set by ACPI table parsing code if possible
 
unsigned char __cmos_second;
unsigned char __cmos_minute;
unsigned char __cmos_hour;
unsigned char __cmos_day;
unsigned char __cmos_month;
unsigned int __cmos_year;
 
enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};
 
int __cmos_get_update_in_progress_flag() {
      write_port(cmos_address, 0x0A);
      return (read_port(cmos_data) & 0x80);
}
 
unsigned char __cmos_get_RTC_register(int reg) {
      write_port(cmos_address, reg);
      return read_port(cmos_data);
}
 
void __cmos_read_rtc() {
      unsigned char century;
      unsigned char last___cmos_second;
      unsigned char last_minute;
      unsigned char last___cmos_hour;
      unsigned char last___cmos_day;
      unsigned char last___cmos_month;
      unsigned char last___cmos_year;
      unsigned char last_century;
      unsigned char registerB;
 
      // Note: This uses the "read registers until you get the same values twice in a row" technique
      //       to avoid getting dodgy/inconsistent values due to RTC updates
 
      while (__cmos_get_update_in_progress_flag());                // Make sure an update isn't in progress
      __cmos_second = __cmos_get_RTC_register(0x00);
      __cmos_minute = __cmos_get_RTC_register(0x02);
      __cmos_hour = __cmos_get_RTC_register(0x04);
      __cmos_day = __cmos_get_RTC_register(0x07);
      __cmos_month = __cmos_get_RTC_register(0x08);
      __cmos_year = __cmos_get_RTC_register(0x09);
      if(__cmos_century_register != 0) {
            century = __cmos_get_RTC_register(__cmos_century_register);
      }
 
      do {
            last___cmos_second = __cmos_second;
            last_minute = __cmos_minute;
            last___cmos_hour = __cmos_hour;
            last___cmos_day = __cmos_day;
            last___cmos_month = __cmos_month;
            last___cmos_year = __cmos_year;
            last_century = century;
 
            while (__cmos_get_update_in_progress_flag());           // Make sure an update isn't in progress
            __cmos_second = __cmos_get_RTC_register(0x00);
            __cmos_minute = __cmos_get_RTC_register(0x02);
            __cmos_hour = __cmos_get_RTC_register(0x04);
            __cmos_day = __cmos_get_RTC_register(0x07);
            __cmos_month = __cmos_get_RTC_register(0x08);
            __cmos_year = __cmos_get_RTC_register(0x09);
            if(__cmos_century_register != 0) {
                  century = __cmos_get_RTC_register(__cmos_century_register);
            }
      } while( (last___cmos_second != __cmos_second) || (last_minute != __cmos_minute) || (last___cmos_hour != __cmos_hour) ||
               (last___cmos_day != __cmos_day) || (last___cmos_month != __cmos_month) || (last___cmos_year != __cmos_year) ||
               (last_century != century) );
 
      registerB = __cmos_get_RTC_register(0x0B);
 
      // Convert BCD to binary values if necessary
 
      if (!(registerB & 0x04)) {
            __cmos_second = (__cmos_second & 0x0F) + ((__cmos_second / 16) * 10);
            __cmos_minute = (__cmos_minute & 0x0F) + ((__cmos_minute / 16) * 10);
            __cmos_hour = ( (__cmos_hour & 0x0F) + (((__cmos_hour & 0x70) / 16) * 10) ) | (__cmos_hour & 0x80);
            __cmos_day = (__cmos_day & 0x0F) + ((__cmos_day / 16) * 10);
            __cmos_month = (__cmos_month & 0x0F) + ((__cmos_month / 16) * 10);
            __cmos_year = (__cmos_year & 0x0F) + ((__cmos_year / 16) * 10);
            if(__cmos_century_register != 0) {
                  century = (century & 0x0F) + ((century / 16) * 10);
            }
      }
 
      // Convert 12 __cmos_hour clock to 24 __cmos_hour clock if necessary
 
      if (!(registerB & 0x02) && (__cmos_hour & 0x80)) {
            __cmos_hour = ((__cmos_hour & 0x7F) + 12) % 24;
      }
 
      // Calculate the full (4-digit) __cmos_year
 
      if(__cmos_century_register != 0) {
            __cmos_year += century * 100;
      } else {
            __cmos_year += (CURRENT_YEAR / 100) * 100;
            if(__cmos_year < CURRENT_YEAR) __cmos_year += 100;
      }
}