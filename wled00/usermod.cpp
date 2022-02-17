#include "wled.h"
#include <SPI.h>
#include <U8x8lib.h>
/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 * 
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(15, 4, 16);

String IpAddress2String(const IPAddress &ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

//gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{
    u8x8.begin();
    u8x8.setFont(u8x8_font_chroma48medium8_r);
}

//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{
}

//loop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop()
{
    if (WLED_CONNECTED)
    {
        u8x8.drawString(0, 0, ("WiFi RSSI: " + String(WiFi.RSSI())).c_str());
        u8x8.drawString(0, 1, ("IP: " + IpAddress2String(WiFi.localIP())).c_str());
        u8x8.drawString(0, 2, ("Power: " + String(strip.currentMilliamps) + " mA").c_str());
        u8x8.drawString(0, 3, ("LED Pin: " + String(LEDPIN)).c_str());
        u8x8.drawString(0, 4, (String(WiFi.getHostname())).c_str());
    }
}