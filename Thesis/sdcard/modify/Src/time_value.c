#include "time_value.h"

ip4_addr_t server_addr;

uint8_t Get_Time(uint8_t time[6])
{
	RTC_TimeTypeDef sTime = { 0 };
	RTC_DateTypeDef sDate = { 0 };
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	time[0] = sTime.Hours;
	time[1] = sTime.Minutes;
	time[2] = sTime.Seconds;
	time[3] = sDate.Month;
	time[4] = sDate.Date;
	time[5] = sDate.Year;
	}
