#pragma once

#include <iostream>
#include <memory>
#include <math.h>
#include <qcc/platform.h>
#include <corecrt.h>
#include <corecrt_memcpy_s.h>
#include <corecrt_wconio.h>
#include <corecrt_wctype.h>
#include <corecrt_wdirect.h>
#include <corecrt_wio.h>
#include <corecrt_wprocess.h>
#include <corecrt_wstdio.h>
#include <corecrt_wstdlib.h>
#include <corecrt_wstring.h>
#include <corecrt_wtime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vcruntime_string.h>

#define Analog_Pin_Port = 5;

class Analog_pin(int port);

Analog_pin_GetPortById(int port);
Analog_pin_GetObjectFrequncy(int frequncy, int objectAnalog);

Analog_Sys_Opk_date(const Analog_Pin_wire, int ReadSysHandle);

