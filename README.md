# JuiceBar

Battery levels of your wireless mouse, keyboard, headset and controller, right on the Windows taskbar,
each one in its maker's color: **Razer** green, **Logitech** blue, **SteelSeries** orange, **Corsair** yellow
and 11 more brands. Branded devices get a soft glow and a thin level bar under the percentage, like Razer Synapse
or Logitech G HUB. Everything else keeps the plain Windows look.

![JuiceBar: battery levels of 15 brands, each in its own color](docs/juicebar.png)

![Taskbar: Logitech headset, mouse and keyboard in blue, Razer mouse and keyboard in green](docs/screenshot-razer-logitech.png)

All 15 brands on a dark and a light taskbar (top: taskbar widget, below: tray icon mode):

![Brand colors of all 15 brands on a dark and a light taskbar](docs/brand-colors.png)

JuiceBar is a fork of [Wireless Battery](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor)
(Wireless-Device-Battery-Monitor) by krisgfx9, version 1.0.5, GPL-3. All device support comes from the original.
JuiceBar changes the look and fixes a few things.

## Brands

| Brand | Color | Recognized by |
| --- | --- | --- |
| Razer | green `#44D62C` | Razer receivers and Bluetooth, BlackShark / Barracuda headsets, "Razer …" names |
| Logitech | light blue `#00B8FC` | Unifying, Bolt, Lightspeed, Bluetooth; names like "MX …", "G915", "K380" |
| SteelSeries | orange `#FF5200` | SteelSeries receivers; "Arctis", "Aerox", "Rival" |
| Corsair | yellow `#F5E41A` | Corsair receivers, Corsair headsets via HeadsetControl |
| HyperX | red `#E31837` | HyperX receivers; "HyperX …", "Pulsefire" |
| ASUS ROG | red `#FF0029` | ROG receivers; "ROG …" |
| ZOWIE | red `#E2231A` | ZOWIE receivers |
| PlayStation | blue `#0070D1` | DualSense, DualShock 4, INZONE headsets |
| Xbox | green `#107C10` | Xbox controllers and headsets |
| Samsung | blue `#1428A0` | Galaxy Buds, Galaxy phones (Phone Link) |
| Apple | silver | AirPods, Magic Mouse / Keyboard / Trackpad |
| Jabra | amber `#FFC800` | Jabra Link dongle; "Jabra …" |
| JBL | red-orange `#FF3D00` | JBL Quantum headsets; "JBL …" |
| Cooler Master | purple | Cooler Master mice |
| Steam | blue `#1A9FFF` | Steam Controller |

The brand is picked from the driver that found the device first, then the USB / Bluetooth vendor ID, then the name.
Dark brand colors (Xbox, PlayStation, Samsung) are brightened on a dark taskbar, and yellow and silver are deepened on
a light one, so every color stays readable on both. Shared vendor IDs don't leak colors: HP mice (shared with HyperX),
Microsoft Surface mice (shared with Xbox) and Sony WH- / WF- headphones (shared with PlayStation) stay plain.

Colors and rules live in one file, [`src/brands.cpp`](src/brands.cpp). Adding a brand takes one enum value in
[`src/brands.h`](src/brands.h) and a line in each table.

## Download and install

1. Open **[Releases](../../releases/latest)** and download `JuiceBar-Setup-….exe`.
2. Run it and click Next. No administrator rights and no other software needed. Setup can turn on
   "start with Windows" for you.

Prefer no installer? Download `JuiceBar-…-portable.zip`, unzip anywhere and run `WirelessBattery.exe`
(the program file keeps the original app's name).

**"Windows protected your PC" warning:** the app has no paid code-signing certificate, so Windows doesn't know it yet.
Click *More info → Run anyway*. The files are built by GitHub Actions from the code in this repo (see the *Actions* tab).
Nobody uploads them by hand.

Already using the original Wireless Battery? Exit it and uninstall it first: both apps share the same settings and
startup entry, and only one of them can run at a time.

## Usage

- The indicators sit on the taskbar next to the clock. They refresh every minute, and right away when a device
  connects.
- **Click** for the menu: device list (click a device to hide or show it), refresh, start with Windows, exit.
- A red number means 15% or less. A blue bolt means charging. A dimmed indicator is the last known reading
  (the device is asleep).
- Hover to see full device names and status.

## What's different from the original

- **Brand colors** for 15 brands (table above), with a glow and a level bar in widget mode and a colored bar in
  tray icon mode.
- **Friendlier names:** "DSV2 Pro" becomes "Razer DeathStalker V2 Pro", and the "LE-" prefix disappears from
  Bluetooth headset names.
- **Bluetooth fix:** dual-mode headsets (classic Bluetooth plus LE Audio, e.g. Bose QC Ultra) no longer drop off the
  taskbar when Windows lists the unused connection first.
- **Sleeping Razer mice stay on the taskbar**, dimmed, with their last reading. In the original they disappeared and
  came back up to a minute after waking.
- **Sony INZONE H9 / H7 (first generation):** read over their dongle's USB serial port, which the original didn't
  support.
- **Command line:** `--demo` shows sample Razer and Logitech devices, `--demo=all` one device of every brand (for
  screenshots or checking colors without the hardware). `--preview file.bmp` draws every brand on a dark and a light
  taskbar into one image. `--list` prints the devices it finds with the detected brand.

## Supported hardware

Same as the original: mice, keyboards and headsets from Logitech (Unifying, Bolt, Lightspeed, Bluetooth), Razer
(HyperSpeed receivers, Bluetooth, BlackShark headsets), SteelSeries, Corsair, HyperX and many more, plus anything
that shows its battery in *Settings → Bluetooth & devices*. Full list:
[original README](docs/ORIGINAL-README.md#supported-devices).

Logitech G HUB, Razer Synapse and other vendor apps can keep running alongside it. The exception is the first-generation
INZONE H9 / H7: INZONE Hub holds their dongle's serial port while it runs, so close INZONE Hub to see the headset.

## Privacy and safety

The app never connects to the internet and downloads nothing. It only asks devices for their battery status.
In the registry it writes just its own settings (`HKCU\Software\WirelessBattery`) and, if you turn it on, a startup
entry. It shares those settings with the original app, so don't run both at once.

## Building from source

You need [MinGW-w64](https://www.mingw-w64.org/), e.g. the portable [WinLibs](https://winlibs.com/) build:

```
mingw32-make CXX=g++ WINDRES=windres
mingw32-make test CXX=g++
```

`installer\build-installer.ps1` builds the installer and the portable zip
(needs [Inno Setup](https://jrsoftware.org/isinfo.php)). Pushing a `v…` tag builds and publishes a release
automatically (GitHub Actions).

## License and credits

[GNU GPL v3.0 or later](LICENSE), same as the original. The original app and all device protocols:
[krisgfx9 and contributors](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor) (their credits are in the
[original README](docs/ORIGINAL-README.md#credits)). The installer bundles
[HeadsetControl](https://github.com/Sapd/HeadsetControl) (GPL-3).

All brand names in the table are trademarks of their owners. This project is not affiliated with any of them.
The colors only help you tell your devices apart on the taskbar.
