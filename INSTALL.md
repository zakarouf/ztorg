# How to install Ncurses/Terminfo on your system

    +--------------------------------------------------------+
    | READ ALL OF THIS FILE BEFORE YOU TRY TO INSTALL ZTORG. |
    +--------------------------------------------------------+

## REQUIREMENTS

You will need the following to build and install Ztorg:

    * Ncurses           (ncurses, ncursest ...)
    * C99 compiler      (gcc, clang ...)
    * sh                (bash/zsh/fish/sh will do)

## INSTALLATION

### 0. Downloads

You can Get Ztorg by either ![Releases](https://github.com/zakarouf/ztorg/releases)

### 1. Config

Ztorg Installation is done by simple bash script namely `install`
Some of what you can change by editing the file directly
    
    CCF=clang
    CFLAGS='-Wall -Ofast'
    HEADER='zse/ '
    CFILES=''
    LDFLAGS='-lncursest'
    ZENGINE='zse/*'

Just change to whatever your liking

### 2. Install


```
```