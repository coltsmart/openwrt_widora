/*!
 * File:
 *  radio_comm.h
 *
 * Description:
 *  This file contains the RADIO communication layer.
 *
 * Silicon Laboratories Confidential
 * Copyright 2012 Silicon Laboratories, Inc.
 */

                /* ======================================= *
                 *              I N C L U D E              *
                 * ======================================= */

#include "typedef.h"
#include "radio_comm.h"
#include "radio_hal.h"
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */
#define SILABS_RADIO_SI446X
                /* ======================================= *
                 *     G L O B A L   V A R I A B L E S     *
                 * ======================================= */

#if (defined SILABS_RADIO_SI446X) || (defined SILABS_RADIO_SI4455)
bool ctsWentHigh = 0;
#endif


                /* ======================================= *
                 *      L O C A L   F U N C T I O N S      *
                 * ======================================= */

                /* ======================================= *
                 *     P U B L I C   F U N C T I O N S     *
                 * ======================================= */

#if (defined SILABS_RADIO_SI446X) || (defined SILABS_RADIO_SI4455)

/*!
 * Gets a command response from the radio chip
 *
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 *
 * @return CTS value
 */
extern struct spi_device *slave;
U8 radio_comm_GetResp(U8 byteCount, U8* pData)
{
  SEGMENT_VARIABLE(ctsVal = 0u, U8, SEG_DATA);
  SEGMENT_VARIABLE(errCnt = RADIO_CTS_TIMEOUT, U16, SEG_DATA);
  U8 *p;
  ctsVal = 0x44;
  p = kmalloc(byteCount + 1,GFP_KERNEL);
  spi_write_then_read(slave,&ctsVal,1,p,byteCount + 1);
  if(p[0] != 0xff)
  {
    printk("%s : CTS error\r\n",__func__);
  }
  memcpy(pData,p + 1,byteCount);
  kfree(p);
  #if 0
  while (errCnt != 0)      //wait until radio IC is ready with the data
  {
    radio_hal_ClearNsel();
    //radio_hal_SpiWriteByte(0x44);    //read CMD buffer
    //ctsVal = radio_hal_SpiReadByte();
    ctsVal = spi_w8r8(slave,0x44);
    if (ctsVal == 0xFF)
    {
      if (byteCount)
      {
        radio_hal_SpiReadData(byteCount, pData);
      }
      radio_hal_SetNsel();
      break;
    }
    radio_hal_SetNsel();
    errCnt--;
    udelay(1);
  }

  if (errCnt == 0)
  {
    while(1)
    {
      printk("%s,%d,0x%02x\r\n",__func__,__LINE__,ctsVal);
      /* ERROR!!!!  CTS should never take this long. */
      #ifdef RADIO_COMM_ERROR_CALLBACK
        RADIO_COMM_ERROR_CALLBACK();
      #endif
    }
  }
#endif
  ctsVal = 0xff;
  //if (ctsVal == 0xFF)
  {
    ctsWentHigh = 1;
  }

  return ctsVal;
}

/*!
 * Sends a command to the radio chip
 *
 * @param byteCount     Number of bytes in the command to send to the radio device
 * @param pData         Pointer to the command to send.
 */
void radio_comm_SendCmd(U8 byteCount, U8* pData)
{
    /* There was a bug in A1 hardware that will not handle 1 byte commands. 
       It was supposedly fixed in B0 but the fix didn't make it at the last minute, so here we go again */
    if (byteCount == 1)
        byteCount++;

    while (!ctsWentHigh)
    {
        radio_comm_PollCTS();
    }
    //radio_hal_ClearNsel();
    //radio_hal_SpiWriteData(byteCount, pData);
    //radio_hal_SetNsel();
    spi_write(slave,pData,byteCount);
    ctsWentHigh = 0;
}

/*!
 * Gets a command response from the radio chip
 *
 * @param cmd           Command ID
 * @param pollCts       Set to poll CTS
 * @param byteCount     Number of bytes to get from the radio chip.
 * @param pData         Pointer to where to put the data.
 */
void radio_comm_ReadData(U8 cmd, bool pollCts, U8 byteCount, U8* pData)
{
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
    msleep(3);
    /*radio_hal_ClearNsel();
    radio_hal_SpiWriteByte(cmd);
    radio_hal_SpiReadData(byteCount, pData);
    radio_hal_SetNsel();*/
    spi_write_then_read(slave,&cmd,1,pData,byteCount);
    ctsWentHigh = 0;
}


/*!
 * Gets a command response from the radio chip
 *
 * @param cmd           Command ID
 * @param pollCts       Set to poll CTS
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 */
void radio_comm_WriteData(U8 cmd, bool pollCts, U8 byteCount, U8* pData)
{
    U8 *p;
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
    p = kmalloc(byteCount + 1,GFP_KERNEL);
    p[0] = cmd;
    memcpy(p + 1,pData,byteCount);
    /*radio_hal_ClearNsel();
    radio_hal_SpiWriteByte(cmd);
    radio_hal_SpiWriteData(byteCount, pData);
    radio_hal_SetNsel();*/
    spi_write(slave,p,1 + byteCount);
    kfree(p);
    ctsWentHigh = 0;
}

/*!
 * Waits for CTS to be high
 *
 * @return CTS value
 */
U8 radio_comm_PollCTS(void)
{
#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS
    while(!radio_hal_Gpio1Level())
    {
        /* Wait...*/
    }
    ctsWentHigh = 1;
    return 0xFF;
#else
    return radio_comm_GetResp(0, 0);
#endif
}

/**
 * Clears the CTS state variable.
 */
void radio_comm_ClearCTS()
{
  ctsWentHigh = 0;
}

#elif (defined SILABS_RADIO_SI4012)

/*!
 * Gets a command response from the radio chip
 *
 * @param byteCount     Number of bytes to get from the radio chip
 * @param pData         Pointer to where to put the data
 *
 * @return CTS value
 */
U8 radio_comm_GetResp(U8 byteCount, U8* pData)
{
  SEGMENT_VARIABLE(ctsVal = 0u, U8, SEG_DATA);

  if (qSmbus_SMBusRead(SI4012_SMBUS_ADDRESS, byteCount, pData) != \
                                                          SMBUS_RX_FINISHED) {
    return FALSE;
  }

  if (pData[0] == 0x80) {
    return TRUE;
  }

  return FALSE;
}

/*!
 * Sends a command to the radio chip
 *
 * @param byteCount     Number of bytes in the command to send to the radio device
 * @param pData         Pointer to the command to send.
 */
U8 radio_comm_SendCmd(U8 byteCount, U8* pData)
{
  if (qSmbus_SMBusWrite(SI4012_SMBUS_ADDRESS, byteCount, pData) != \
                                                      SMBUS_TRANSMISSION_OK) {
    return FALSE;
  }

  return TRUE;
}

#endif

/*!
 * Sends a command to the radio chip and gets a response
 *
 * @param cmdByteCount  Number of bytes in the command to send to the radio device
 * @param pCmdData      Pointer to the command data
 * @param respByteCount Number of bytes in the response to fetch
 * @param pRespData     Pointer to where to put the response data
 *
 * @return CTS value
 */
U8 radio_comm_SendCmdGetResp(U8 cmdByteCount, U8* pCmdData, U8 respByteCount, U8* pRespData)
{
    radio_comm_SendCmd(cmdByteCount, pCmdData);
    msleep(3);
    return radio_comm_GetResp(respByteCount, pRespData);
}

