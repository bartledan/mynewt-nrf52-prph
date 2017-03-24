# mynewt-nrf52-prph

Sample peripheral applications for [NRF52 Development kit from Nordic Semiconductor](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF52-DK) to work with [ASF mynewt](https://mynewt.apache.org/)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

* [Linux distro such as Fedora](https://getfedora.org/) - Fedora 
* [GNU Toolchain for ARM](https://launchpad.net/gcc-arm-embedded) - Toolchain
* [newt tool](https://mynewt.apache.org/latest/newt/install/newt_linux/) - newt
* [Jlink for Linux](https://www.segger.com/downloads/jlink) - Segger Jlink flash utility for Linux

### Configuring workspace
Once you have configured the pre-requisites, create the workspace


```
git clone https://github.com/bartledan/mynewt-nrf52-prph.git
cd mynewt-nrf52-prph
newt install -v
```
### Build and install a sample blinky application for NRF52 DK

#### Configure targets (bootloader and application)
```
newt target create nrf52_boot
newt target set nrf52_boot app=@apache-mynewt-core/apps/boot
newt target set nrf52_boot bsp=@apache-mynewt-core/hw/bsp/nrf52dk
newt target set nrf52_boot build_profile=optimized
```
Now configure application
```
newt target create my_blinky_app
newt target set my_blinky_app app=apps/blinky
newt target set my_blinky_app bsp=@apache-mynewt-core/hw/bsp/nrf52dk
newt target set my_blinky_app build_profile=optimized
```
#### Build targets
Build bootloader

```
newt build nrf52_boot
```
Build application

```
newt build my_blinky_app
```
#### Load the firmware (bootloader and application)
Load bootloader on the target board (NRF52 DK)

```
newt -v load nrf52_boot
```
Before the application can be loaded on the target, the firmware
needs to have a versioning information and optionally a signing key
Hence, create application firmware with some version and then
load on the target.

```
newt create-image my_blinky_app 1.0.0
newt -v load my_blinky_app
```

## Versioning

We will use [SemVer](http://semver.org/) for versioning. No versioning information at the moment.

## Authors

* *Kumar Amit Mehta* - - [Sidekick](https://github.com/KumarAmitMehta)

## License

This project is licensed under the Apache License, Version 2.0 - see the [LICENSE.md](https://github.com/bartledan/mynewt-nrf52-prph/blob/master/LICENSE) file for details

## Acknowledgments

* mynewt communitiy


