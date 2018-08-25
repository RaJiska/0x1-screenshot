# The Non-Null Pointer Screenshot
This tool is an extension of the ["The Non-Null Pointer" (0x1)](https://github.com/RaJiska/0x1) project which allows one to capture and upload a screenshot with live cropping much like Gyazo's tool. The captured screenshots can be uploaded at any [0x0](https://github.com/lachs0r/0x0) clones / sub derivatives or websites accepting direct POST uploads.
At this moment, only Linux platform is supported.

## Installation
```
$ add-apt-repository ppa:rajiska/0x1-screenshot
$ apt-get update
$ apt-get install 0x1-screenshot
```

## Configuration
The tool reads a simple configuration file which can be found either in `/etc/0x1-screenshot/general.cfg` or next to the binary `config.txt` (overriding the previous one). Sample configuration file:
```
uploadurl=0x1.rajiska.fr
screenshottool=gnome-screenshot -a -f
```
The entry `screenshottool` is enterpreted as a shell command and is followed by a temporary file name which will hold the screenshot until the upload is achieved.

## Build From Sources
```
$ git clone --recursive https://github.com/RaJiska/0x1-screenshot
$ mkdir build && cd build
$ cmake ..
$ make
```

## Credits
[libstb](https://github.com/nothings/stb) by Sean Barrett