# ESP8266 ArtNet-LED-DMX-Node [![GitHub release](https://img.shields.io/github/release/bombcheck/ESP8266_ArtNet-LED-DMX-Node.svg)](https://github.com/bombcheck/ESP8266_ArtNet-LED-DMX-Node/releases/latest)
ESP8266 based WiFi ArtNet V4 to DMX, RDM and LED Pixels.

Forked this from the great work of [Matthew Tong](https://github.com/mtongnz) because I love all kinds of shining/flashing/moving lighting stuff and needed some modifications to suit my needs.

## Getting Started
### Pre-Compiled binaries
Check the 'release'-section for the latest ready-to-flash-binaries. Download and flash with flasher of your choice. For example the [NodeMCU PyFlasher](https://github.com/marcelstoer/nodemcu-pyflasher/releases)

**Attention: These pre-compiled binaries are only for NodeMCU-boards!**

### Compiling from source
 - You need the latest ESP8266 Arduino Core files and the latest Arduino IDE version.
 - Make sure you placed the libraries from this project into your Arduino libraries folder.
 - Select the proper board. For me it is a "NodeMCU 1.0 (ESP-12E Module)".
 - Make sure to compile with a CPU Frequency of 160 MHz!

### First Boot
On your first boot, the device will start a hotspot called "espArtLeDNode" with a password of "espArtLeDNode" (case sensitive).  Login to the hotspot and goto http://10.0.17.1 in a web browser.

Note that the hotspot is, by default, only for accessing the settings page.  You'll need to enable Stand Alone mode in the web UI if you want to send ArtNet data to the device in hotspot mode.

### Web-UI
In hotspot mode, goto http://10.0.17.1 and in Wifi mode goto whatever the device IP might be - either static or assigned by DHCP.

In the Wifi tab, enter your SSID and password.  Click save (it should go green and say Settings Saved).  Now click reboot and the device should connect to your Wifi.

If the device can't connect to the wifi or get a DHCP assigned address within (Start Delay) seconds, it will start the hotspot and wait for 30 seconds for you to connect.  If a client doesn't connect to the hotspot in time, the device will restart and try again.

### Restore Factory Defaults
Hold GPIO14 to GND while the device boots.

## Features
 - sACN and ArtNet V4 support
 - 2 full universes of DMX output with full RDM support for both outputs
 - Up to 1360 ws2812(b) pixels - 8 full universes
 - DMX/RDM out one port, ws2812(b) out the other
 - DMX in - send to any ArtNet device
 - Web UI with mobile support
 - Web UI uses AJAX & JSON to minimize network traffic used & decrease latency
 - Full DMX Workshop support
 - Pixel FX - a 12 channel mode for ws2812 LED pixel control

## Pixel FX
To enable this mode, select WS2812 in the port settings and enter the number of pixels you wish to control.  Select '12 Channel FX'. 'Start Channel' is the DMX address of the first channel below.

Note: You still need to set the Artnet net, subnet and universe correctly.

| DMX Channel | Function | Values (0-255) |  |
|----|----|----|----|
| 1 | Intensity | 0 - 255   |               |
| 2 | FX Select | 0 - 49    | Static        |
|   |           | 50 - 74   | Rainbow       |
|   |           | 75 - 99   | Theatre Chase |
|   |           | 100 - 124 | Twinkle       |
| 3 | Speed     | 0 - 19    | Stop - Index Reset |
|   |           | 20 - 122  | Slow - Fast CW |
|   |           | 123 - 130 | Stop |
|   |           | 131 - 234 | Fast - Slow CCW |
|   |           | 235 - 255 | Stop |
| 4 | Position  | 0 - 127 - 255 | Left - Centre - Right |
| 5 | Size      | 0 - 255   | Small - Big   |
| 6 | Colour 1  | 0 - 255   | Red |
| 7 |           | 0 - 255   | Green |
| 8 |           | 0 - 255   | Blue |
| 9 | Colour 2  | 0 - 255   | Red |
| 10 |          | 0 - 255   | Green |
| 11 |          | 0 - 255   | Blue |
| 12 | Modify   | 0 - 255   | *Modify FX |

Modify FX is only currently used for the Static effect and is used to resize colour 1 within the overall size.

## NodeMCU & Wemos Pins
These boards use strange numbering that doesn't match the ESP8266 numbering.  Here are the main hookups needed:

| NodeMCU & Wemos | ESP8266 GPIO | Purpose |
|-----------------|--------------|---------|
| TX | GPIO1 | DMX_TX_A (Port A) |
| D4 | GPIO2 | DMX_TX_B (Port B) |
| RX | GPIO3 | DMX_RX (for A & B) |
| D1 | GPIO5 | DMX_DIR_A |
| D0 | GPIO16 | DMX_DIR_B |

## Special thanks to
[Matthew Tong](https://github.com/mtongnz) for the great work this fork is based upon.



work with arduino esp8266 board version 2.4.2 and arduinojson 5.13.5
