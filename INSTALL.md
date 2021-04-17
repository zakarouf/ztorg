# How to install ZSE/Ztorg on your system

    +--------------------------------------------------------+
    | READ ALL OF THIS FILE BEFORE YOU TRY TO INSTALL ZTORG. |
    +--------------------------------------------------------+

## REQUIREMENTS

You will need the following to build and install Ztorg:

    * C99 compiler      (gcc, clang ...)

Depending on your [io]() setup ZSE can require following libs.
* Vulkan
* Ncurses
* SDL
* Opengl


## INSTALLATION

### 0. Downloads

You can Get Ztorg by either [Releases](https://github.com/zakarouf/ztorg/releases)
OR, by cloning the git repo itself.
```sh
git clone https://github/zakarouf/ztorg
```

### 1. Config

Ztorg Installation is done by simple python3 script named `cbuild.py`
Some of what you can change by editing the file directly
```python
    CC="clang"              # Compiler
    CFLAGS=[-Wall,-Ofast]   # CFLAGS
    LDFLAGS=[-lncursest]    # LDFLAGS
    OUTEXE='build/z'        # Executable Path
```
Just change to whatever your liking

### 2. Install

```sh
cd ztorg
python3 cbuild.py
tar -xf data.tar
cp build/z data/z
```
