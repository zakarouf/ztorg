# Zak's Ztorg

This is My First Attempt to have something remotely big Project
And As of Uploading this Repo to Github (5th May 2020), I have only
been coding for few months. I just wanted to do something in Quarentine
So I Decided to learn basic programming. This is it.

### Installation & Execution

For Installing it just run
```
git clone https://github.com/zakarouf/ztorg.git
cd ztorg
./install
```
And it Should Compile the binary in current directory named 'z' in directory 'data'.
It can be executed by
```
cd data
./z
```
## Game

After execting the game, it should look like this
[main_menu](https://github.com/zakarouf/ztorg/blob/master/doc/scr/main_menu.png?raw=true)
- Press Num keys to traverse Menu.
- To Countinue w/ Selected option Press 'e'.
- Three options are self Explanatory.
- Select Play to Start At a map.
- Editor to make a Map. 
- Quit to quit.

### PLAY 
This mode as of current is just a free roam in a selected map.
I would however, would like to add RPG features in future.
Well for Reffernce It looks like This. In 3D raycasting mode.
![play](https://github.com/zakarouf/ztorg/blob/master/doc/scr/play.png?raw=true)
### EDITOR
As of now Editor is my Main Focus, It is a tool to make Maps for the game.
![editor_select](https://github.com/zakarouf/ztorg/blob/master/doc/scr/editor_select.png?raw=true)
In Main Menu Press '1' to select Editor w/ A clean slate.
Starting the Editor will prompt the player to Enter Map X/Y Dimention (Map is always a Rectangle) & Map Name.

![editor_setup](https://github.com/zakarouf/ztorg/blob/master/doc/scr/editor_setup.png?raw=true)

This will auto genarate a Blank Map where you can draw n' stuff.

![e_intro](https://github.com/zakarouf/ztorg/blob/master/doc/scr/e_intro.png?raw=true)

Press 'c' followed by ascii char in your keyboard which you want to draw.
Ohh, I forgot to mention, use "wasd" keys to move around.

![e_c](https://github.com/zakarouf/ztorg/blob/master/doc/scr/change_tile_0.png?raw=true)

Now you can Draw by pressing 'v', This will enable Brush mode

![move](https://github.com/zakarouf/ztorg/blob/master/doc/scr/move_brush_on.png?raw=true)

- You can Disable Brush mode by pressing 'v', and change ascii char to draw by pressing key 'c' followed by Character you want draw with. NOTE 'c' will Not work if Brush is disabled(0).

I'll add more Draw funtion Instruction Once I finalize them(they're there, look into e_main.c{e_mainloop} if ya want to use them.)

---
#### IF ANYONE READING THIS

IF you wonder upon this repo please send me the ways I can Improve
I'm not a CS student and I'm self learning most of my stuff.

Cheers !!!
