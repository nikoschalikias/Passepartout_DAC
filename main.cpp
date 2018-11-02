#include "mbed.h"
#include "math.h"
/**********************
 *      MCP4922
 **********************/

///SPI Interface
SPI MCP4922_SPI(D11,D12,D13);//MOSI ,MISO ,SCK
DigitalOut MCP4922_CS(D10);//CS

AnalogIn knob(A1);

DigitalIn mode_s(D8);

//Digital Output
DigitalOut MCP4922_LDAC(D8);
DigitalOut MCP4922_SHDN(D9);
void volt_out(double volt)
{

    uint16_t temp=((uint16_t)(volt*4096/3.33))&0x0fff;
    uint16_t MCP4922_Sent_Data = 0;
    MCP4922_Sent_Data = 0xB000|temp;
    //MCP4922_Sent_Data = 0x3fff;
    MCP4922_CS = 0;


    //sent data buffer to mcp4922
    MCP4922_SPI.write(MCP4922_Sent_Data);

    //set CS to High to End MCP4922 SPI Interface
    MCP4922_CS = 1;

    //set LDAC to LOW to Load data to output
    MCP4922_LDAC = 0 ;

    //wait at least 100ns = 0.1 microsec ..... So set at 1 microsec
    wait_us(1);

    //set LDAC to High to prepare next output
    MCP4922_LDAC = 1 ;
}
int main()
{
    /******************************
     *****      setup       *******
     ******************************/
    uint16_t volt_temp=0;
    /////////setup SPI//////////
    //set CS High
    MCP4922_CS=1;

    //set SPI mode [1,1]=> mode 3 @16bit
    MCP4922_SPI.format(16,3);

    //set SPI Frequency @20MHz
    MCP4922_SPI.frequency(1000000);

    //set Load DAC High (inactive)
    MCP4922_LDAC = 1;

    //set shutdown DAC High (inactive)
    MCP4922_SHDN = 1;

    //loop
    while(1) {
             /* if(mode_s)volt_temp=uint16_t(3.33-knob.read()*3.33);
              else volt_temp=uint16_t(knob.read()*3.33);
              volt_out(volt_temp); */
              volt_out(2.5);
           }
}
