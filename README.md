# DragonTap

DragonTap is a graphical utility for Linux to interact with WireGuard connections already configured in NetworkManager.

## Building
### Dependencies

The following pkg-config dependencies are required for building:

* gtk+-3.0
* libnm

### Instructions
DragonTap uses the [Meson build system](http://mesonbuild.com). Clone the repo, then do the following to produce an executable:

```
$ cd dragontap
$ mkdir build && cd build
$ meson ..
$ ninja
$ ./src/dragontap
```
