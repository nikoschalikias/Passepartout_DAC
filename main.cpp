// imported from: https://os.mbed.com/teams/fra221-pb11/code/Lab4MCP492_SPI//file/b81dc534e7d7/main.cpp/

#include "mbed.h"
#include "math.h"

SPI MCP4922_SPI(PA_12,PA_6,PA_5);//MOSI ,MISO ,SCK  // nikos:  D12 MISO PA_6 NOT USED IN DAC, BUT IS USED AS VALVE2 in Passepartout motherboard
DigitalOut MCP4922_CS(PA_11);//CS
DigitalIn mode_s(PB_2); // nikos: #TEC-DAC-LDAC, WAS D8
DigitalOut MCP4922_LDAC(PB_2);  // nikos: #TEC-DAC-LDAC, WAS D8
DigitalOut MCP4922_SHDN(PD_15);    // nikos: SHDN is connected to +3.3V in Passepartout motherboard, D9 is PD_15, is not connected

void volt_out(double volt) {
    uint16_t temp=((uint16_t)(volt*4096/3.33))&0x0fff;
    uint16_t MCP4922_Sent_Data = 0;
    MCP4922_Sent_Data = 0xB000|temp;
    MCP4922_CS = 0;  //MCP4922_Sent_Data = 0x3fff;
    MCP4922_SPI.write(MCP4922_Sent_Data); //sent data buffer to mcp4922
    MCP4922_CS = 1;  //set CS to High to End MCP4922 SPI Interface
    MCP4922_LDAC = 0 ;  //set LDAC to LOW to Load data to output
    wait_us(1);  //wait at least 100ns = 0.1 microsec ..... So set at 1 microsec
    MCP4922_LDAC = 1 ; //set LDAC to High to prepare next output
}

int main() {  
    MCP4922_CS=1;
    MCP4922_SPI.format(16,3);
    MCP4922_SPI.frequency(1000000);
    MCP4922_LDAC = 1;
    MCP4922_SHDN = 1;

    while(1) {
        volt_out(1);
    }
}

