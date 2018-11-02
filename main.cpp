#include "mbed.h"
#include "math.h"
/**********************
 *      MCP4922
 **********************/

///SPI Interface
SPI MCP4922_SPI(D11,D12,D13);//MOSI ,MISO ,SCK
DigitalOut MCP4922_CS(D7);//CS



//Digital Output
DigitalOut MCP4922_LDAC(D4);
DigitalOut MCP4922_SHDN(D6);
void volt_out(double volt)
{

    uint16_t temp=((uint16_t)(volt*4096/3.33))&0x0fff;
    uint16_t MCP4922_Sent_Data = 0;
    MCP4922_Sent_Data = 0x3000|temp;
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

    /////////setup SPI//////////
    //set CS High
    MCP4922_CS=1;

    //set SPI mode [1,1]=> mode 3 @16bit
    MCP4922_SPI.format(16,3);

    //set SPI Frequency @20MHz
    MCP4922_SPI.frequency(20000000);

    //set Load DAC High (inactive)
    MCP4922_LDAC = 1;

    //set shutdown DAC High (inactive)
    MCP4922_SHDN = 1;

    //loop
    while(1) {
        for(double x=0; x<2*3.141592; x+=0.00001) {
            volt_out((sin(x)+1.00)*3.33/2.00);
        }

    }
}
