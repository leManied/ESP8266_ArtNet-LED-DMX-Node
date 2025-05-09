/*
ESP8266_ArtNet-LED-DMX-Node
https://github.com/bombcheck/ESP8266_LED-DMX-ArtNetNode

Forked from: https://github.com/mtongnz/ESP8266_ArtNetNode_v2

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program.
If not, see http://www.gnu.org/licenses/
*/


// Change this if the settings structure changes
#define CONFIG_VERSION "la1"

// Dont change this
#define CONFIG_START 0

enum fx_mode {
  FX_MODE_PIXEL_MAP = 0,
  FX_MODE_12 = 1
};

enum p_type {
  TYPE_DMX_OUT = 0,
  TYPE_RDM_OUT = 1,
  TYPE_DMX_IN = 2,
  TYPE_WS2812 = 3
};

enum p_protocol {
  PROT_ARTNET = 0,
  PROT_ARTNET_SACN = 1
};

enum p_merge {
  MERGE_LTP = 0,
  MERGE_HTP = 1
};

struct StoreStruct {
  // StoreStruct version
  char version[4];

  uint8_t portApixOrder; // 0=RGB, 1=RBG, 2=GRB, etc.
  uint8_t portBpixOrder;

  // Device settings:
  IPAddress ip, subnet, gateway, broadcast, hotspotIp, hotspotSubnet, hotspotBroadcast, dmxInBroadcast;
  bool dhcpEnable, standAloneEnable;
  char nodeName[18], longName[64], wifiSSID[40], wifiPass[40], hotspotSSID[20], hotspotPass[20];
  uint16_t hotspotDelay;
  uint8_t portAmode, portBmode, portAprot, portBprot, portAmerge, portBmerge;
  uint8_t portAnet, portAsub, portAuni[4], portBnet, portBsub, portBuni[4], portAsACNuni[4], portBsACNuni[4];
  uint16_t portAnumPix, portBnumPix, portApixConfig, portBpixConfig;
  bool doFirmwareUpdate;
  uint8_t portApixMode, portBpixMode;
  uint16_t portApixFXstart, portBpixFXstart;
  uint8_t resetCounter, wdtCounter;
  
  enum PixOrder {
    PIXORDER_RGB = 0,
    PIXORDER_RBG,
    PIXORDER_GRB,
    PIXORDER_GBR,
    PIXORDER_BRG,
    PIXORDER_BGR,
    PIXORDER_MAX
};


} deviceSettings = {
  CONFIG_VERSION,
  
  // The default values
  IPAddress(10,0,17,1), IPAddress(255,255,255,0), IPAddress(10,0,17,1), IPAddress(2,255,255,255), IPAddress(10,0,17,1), IPAddress(255,255,255,0), IPAddress(2,255,255,255), IPAddress(2,255,255,255),
  true, false,
  "espArtLeDNode", "espArtLeDNode by Bombcheck", "", "", "espArtLeDNode", "espArtLeDNode",
  15,
  TYPE_WS2812, TYPE_DMX_OUT, PROT_ARTNET, PROT_ARTNET, MERGE_HTP, MERGE_HTP,
  0, 0, {0, 1, 2, 3}, 0, 0, {4, 5, 6, 7}, {1, 2, 3, 4}, {5, 6, 7, 8},
  680, 680, 0, 0,
  false,
  FX_MODE_PIXEL_MAP, FX_MODE_PIXEL_MAP,
  1, 1,
  0, 0
};


void eepromSave() {
  for (uint16_t t = 0; t < sizeof(deviceSettings); t++)
    EEPROM.write(CONFIG_START + t, *((char*)&deviceSettings + t));
    //Serial.println("save");
    //Serial.println(deviceSettings.wifiSSID);
    //Serial.println(deviceSettings.wifiPass);

    EEPROM.commit();
}

void eepromLoad() {

  // Store defaults for if we need them
  StoreStruct tmpStore;
  tmpStore = deviceSettings;

  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]) {

    // Copy data to deviceSettings structure
    for (uint16_t t = 0; t < sizeof(deviceSettings); t++)
      *((char*)&deviceSettings + t) = EEPROM.read(CONFIG_START + t);

    //Serial.println("load+");
    //Serial.println(deviceSettings.wifiSSID);
    //Serial.println(deviceSettings.wifiPass);

    // If we want to restore all our settings
    /*
    if (deviceSettings.resetCounter >= 5 ){//|| deviceSettings.wdtCounter >= 10) {
      deviceSettings.wdtCounter = 0;
      deviceSettings.resetCounter = 0;

      // Store defaults back into main settings
      deviceSettings = tmpStore;
    }
  */

  // If config files dont match, save defaults then erase the ESP config to clear away any residue
  } else {
    deviceSettings = tmpStore;
    eepromSave();
    delay(500);
    WiFi.persistent(false);
    ESP.eraseConfig();
    WiFi.disconnect();
    ESP.restart();
    // while(1);

  }
}
