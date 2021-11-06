/*
 * mpu9250.c
 *
 *  Created on: 29/03/2019
 *      Author: cyh
 */

#include "communication/spi.h"
#include "mpu9250.h"
#include "F28x_project.h"
#include "math.h"
#define Buf_SIZE  10

int16_t MPU6500_FIFO[7][Buf_SIZE];
static int16_t Gx_offset=0,Gy_offset=0,Gz_offset=0;
//static int16_t Ax_offset=0,Ay_offset=0,Az_offset=0;
MPU6000_TYPE *MPU6000_Value3;

static unsigned char Wr_Index = 0;

void MPU6500_BrustRead(unsigned char address,unsigned char *p_buf,uint16_t length)
{
    uint16_t i;
    MPU6500_CSL();
    SPI_ReadWrite_Byte(0x80|address);
    for(i = 0;i<length;i++)
    {
      p_buf[i] = SPI_ReadWrite_Byte(0xff);
    }
    MPU6500_CSH();
}

static void MPU6500_writeReg(unsigned char reg, unsigned char data)
{
    MPU6500_CSL();
    SPI_ReadWrite_Byte(reg);
    SPI_ReadWrite_Byte(data);
    MPU6500_CSH();
}

void MPU6500_readRegs(unsigned char reg, unsigned char length, unsigned char *data)
{
    unsigned char count = 0;
    SPI_ReadWrite_Byte(reg |0x80);
    for(count=0;count<length;count++){
            data[count] = SPI_ReadWrite_Byte(0xff);
    }
}
/*
    Initialize the sensor.
*/
void MPU6500_initialize(void)  
{

    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x80);          
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_SIGNAL_PATH_RESET,0x07);
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x00);           // 20M clock
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_SMPLRT_DIV,0x00);           // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_ACCEL_CONFIG,0x01);         // +-2G accel
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_FF_THR,0x04);               
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_GYRO_CONFIG,0x18);          // +-2000 gyro
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_CONFIG, 0x02);            
    DELAY_US(500*100);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_2,0x00);
    DELAY_US(500*100);

/*
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x80); 
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_SIGNAL_PATH_RESET,0x07);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x00);     
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_GYRO_CONFIG,0x18);    
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_ACCEL_CONFIG,0x10);    
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_CONFIG,0x03);           
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_SMPLRT_DIV,0x01);      
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_2,0x00);
    DELAY_US(5000);
*/

        /*
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x80);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x03);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_USER_CTRL,0x01);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_SMPLRT_DIV,0x01);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_INT_PIN_CFG,0x02);  
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_INT_ENABLE,0x01);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_CONFIG,0x03);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_GYRO_CONFIG,0x18);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_ACCEL_CONFIG,0x08);
    DELAY_US(1000*110);
    */
/*
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x80);         
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_SIGNAL_PATH_RESET,0x07);
    DELAY_US(1000*110);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_1,0x00);           
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_ACCEL_CONFIG,0x00);         // +-2G accel
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_FF_THR,0x02);       
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_GYRO_CONFIG,0x18);          // +-2000 gyro
    DELAY_US(5000);
    MPU6500_writeReg(MPU6500_RA_PWR_MGMT_2,0x00);
    DELAY_US(5000);\
    */
    //MPU6500_Init_Offset();   
}

void MPU6000_Read(int16_t *gyro,int16_t *acc)   
{
    unsigned char tmp[14];

    //LOGIC_DBG_PIN1_H;
    MPU6500_BrustRead(ACCEL_XOUT_H,&tmp[0],14);
    //LOGIC_DBG_PIN1_L;
    /* acc data */
    acc[0]   = (((int16_t)tmp[0])<<8 | tmp[1]); 

    acc[1]   = (((int16_t)tmp[2])<<8 | tmp[3]);

    acc[2]   = (((int16_t)tmp[4])<<8 | tmp[5]);
    /* gyro data */
    gyro[0]  =  (((int16_t)tmp[8])<<8 | tmp[9]) - Gx_offset;    

    gyro[1]  =  (((int16_t)tmp[10])<<8 | tmp[11]) - Gy_offset;

    gyro[2]  =  (((int16_t)tmp[12])<<8 | tmp[13]) - Gz_offset;

    //MPU6000_Value->temperature = (tmp[6]<<8)+tmp[7];

}
/*
unsigned char MPU6500_Read(MPU6500_TYPE* MPU6500Value)
{
    unsigned char temp[14];
    static int16_t gx,gy,gz;
    static int16_t ax,ay,az;

    MPU6500_BrustRead(MPU6500_RA_ACCEL_XOUT_H,&temp[0],14);

    ax = ((temp[0]<<8)+temp[1]);
    ay = ((temp[2]<<8)+temp[3]);
    az = ((temp[4]<<8)+temp[5]);

    gx = ((temp[8]<<8)+temp[9]);
    gy = ((temp[10]<<8)+temp[11]);
    gz = ((temp[12]<<8)+temp[13]);

    MPU6500Value->acc_x  =  ax;
    MPU6500Value->acc_y  =  ay;
    MPU6500Value->acc_z  =  az;

    MPU6500Value->gyro_x  =  gx - Gx_Offset;
    MPU6500Value->gyro_y  =  gy - Gy_Offset;
    MPU6500Value->gyro_z  =  gz - Gz_Offset;

    return DEF_OK;

}

*/
unsigned char MPU6000_ReadAcc(MPU6000_TYPE* MPU6000_Value) 
{
    unsigned char tmp[6];
    /* acc data */
    MPU6500_readRegs(ACCEL_XOUT_H,6,&tmp[0]);

    MPU6000_Value->acc_y   = ((tmp[0]<<8)+tmp[1]);

    MPU6000_Value->acc_x   = -((tmp[2]<<8)+tmp[3]);

    MPU6000_Value->acc_z   = -((tmp[4]<<8)+tmp[5]);

    return 1;
}
/*
unsigned char MPU6000_ReadGyro(MPU6000_TYPE* MPU6000_Value) 
{
    unsigned char tmp[6];

    MPU6000_BrustRead(GYRO_XOUT_H,&tmp[0],6);

    MPU6000_Value->gyro_y   = -((tmp[0]<<8)+tmp[1]);

    MPU6000_Value->gyro_x   = ((tmp[2]<<8)+tmp[3]);

    MPU6000_Value->gyro_z   = ((tmp[4]<<8)+tmp[5]);
    return 1;
}
*/
/*
void Mpu_GyroOffest(void)    
{
    const int32_t cnt_g=500;
    int16_t i;
    float offset_temp1,offset_temp2,offset_temp3;
    MPU6000_TYPE Mpu6000Data;

    do
    {
        offset_temp1 = offset_temp2 = offset_temp3 =0;
        for(i=0;i<cnt_g;i++)
        {
            MPU6000_Read(&Mpu6000Data);
            offset_temp1=(float)Mpu6000Data.gyro_x * GYRO_SCALE_X;
            offset_temp2=(float)Mpu6000Data.gyro_y * GYRO_SCALE_Y;;
            offset_temp3=(float)Mpu6000Data.gyro_z * GYRO_SCALE_Z;;   // *

            GyroOffsetX+=offset_temp1;
            GyroOffsetY+=offset_temp2;
            GyroOffsetZ+=offset_temp3;
            Delay_ms(5);
        }
        GyroOffsetX/=(float)cnt_g;
        GyroOffsetY/=(float)cnt_g;
        GyroOffsetZ/=(float)cnt_g;

        offset_temp1 = offset_temp2 = offset_temp3 =0;

        for(i=0;i<cnt_g;i++)
        {
            MPU6000_Read(&Mpu6000Data);
            offset_temp1 +=(float)Mpu6000Data.gyro_x * GYRO_SCALE_X - GyroOffsetX;
            offset_temp2 +=(float)Mpu6000Data.gyro_y * GYRO_SCALE_Y - GyroOffsetY;
            offset_temp3 +=(float)Mpu6000Data.gyro_z * GYRO_SCALE_Z - GyroOffsetZ;
            Delay_ms(5);
        }
    }while((fabs(offset_temp1) > 0.15f) || (fabs(offset_temp2) > 0.15f) || (fabs(offset_temp3) > 0.15f));

}
*/
static void MPU6500_NewVal(int16_t* buf,int16_t val) {
    buf[Wr_Index] = val;
}

static int16_t MPU6500_GetAvg(int16_t* buf)
{
    int i;
    int32_t sum = 0;
    for(i=0;i<Buf_SIZE;i++){
        sum += buf[i];
    }
    sum = sum / Buf_SIZE;
    return (int16_t)sum;
}


void MPU6500_readGyro_Acc(int16_t *gyro,int16_t *acc)
{
    static unsigned char buf[14];
    static int16_t gx,gy,gz;
    static int16_t ax,ay,az;
    MPU6500_CSL();
    MPU6500_readRegs(MPU6500_RA_ACCEL_XOUT_H,14,buf);
    MPU6500_CSH();
    //acc
//    MPU6500_NewVal(&MPU6500_FIFO[0][0],(int16_t)(((int16_t)buf[0]) << 8 | buf[1]));
//    MPU6500_NewVal(&MPU6500_FIFO[1][0],(int16_t)(((int16_t)buf[2]) << 8 | buf[3]));
//    MPU6500_NewVal(&MPU6500_FIFO[2][0],(int16_t)(((int16_t)buf[4]) << 8 | buf[5]));
    ax =    (int16_t)(((int16_t)buf[0]) << 8 | buf[1]);
    ay =    (int16_t)(((int16_t)buf[2]) << 8 | buf[3]);
    az =    (int16_t)(((int16_t)buf[4]) << 8 | buf[5]);
    //temp
  //  MPU6500_NewVal(&MPU6500_FIFO[3][0],(int16_t)(((int16_t)buf[6]) << 8 | buf[7]));
    //gyro
    MPU6500_NewVal(&MPU6500_FIFO[4][0],(int16_t)(((int16_t)buf[8]) << 8 | buf[9]));
    MPU6500_NewVal(&MPU6500_FIFO[5][0],(int16_t)(((int16_t)buf[10]) << 8 | buf[11]));
    MPU6500_NewVal(&MPU6500_FIFO[6][0],(int16_t)(((int16_t)buf[12]) << 8 | buf[13]));

    Wr_Index = (Wr_Index + 1) % Buf_SIZE;

    gx =  MPU6500_GetAvg(&MPU6500_FIFO[4][0]);
    gy =  MPU6500_GetAvg(&MPU6500_FIFO[5][0]);
    gz =  MPU6500_GetAvg(&MPU6500_FIFO[6][0]);

    gyro[0] = gx - Gx_offset;   //gyro
    gyro[1] = gy - Gy_offset;
    gyro[2] = gz - Gz_offset;

//    ax = MPU6500_GetAvg(&MPU6500_FIFO[0][0]);
//    ay = MPU6500_GetAvg(&MPU6500_FIFO[1][0]);
//    az = MPU6500_GetAvg(&MPU6500_FIFO[2][0]);

    acc[0] = ax;     //acc
    acc[1] = ay;
    acc[2] = az;
}

void MPU6500_Init_Offset(void)   
{

    int16_t accgyroval_2[9];
    unsigned int i;
    int32_t tempgx=0,tempgy=0,tempgz=0;
    Gx_offset=0;
    Gy_offset=0;
    Gz_offset=0;

    for(i=0;i<10000;i++)
    {
        DELAY_US(300);
        MPU6000_Read(&accgyroval_2[3],&accgyroval_2[0]);
        tempgx += accgyroval_2[3];
        tempgy += accgyroval_2[4];
        tempgz += accgyroval_2[5];

    }
    Gx_offset=tempgx/10000;
    Gy_offset=tempgy/10000;
    Gz_offset=tempgz/10000;

}



