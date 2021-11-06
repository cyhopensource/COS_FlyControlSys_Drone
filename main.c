/**
 * main.c
 * my first attempt on the control of the plane.
 *
 * 2019.3.29 begin first plan of flight control
 * 2109.4.3 init hardware
 * 2019.4.20 setup more functions
 * 2019.4.29 up to a month.
 *
 */
#include "F28x_Project.h"
#include <stdbool.h>
#include "algorithm/PID_control.h"
#include "sys_dynamic/fly_sys.h"
unsigned char Plane_State = 0;
void main(void)
{
    InitSysCtrl();
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    Hardware_Init();
    EINT;
    while(1)
    {
        System_all();     // run the main system.
    }
}
