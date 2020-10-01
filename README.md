# Zak's Ztorg

![licence](https://img.shields.io/badge/licence-GPL--3.0-important)

This is My First Attempt to have something remotely big Project.

- Its a tile-based terminal game.
- The Source Code is Made to be Independent. I'll release a more Refined Library which is not tied w/ ztorg In Future. But if You are fairly competent in programming. You can use my source and modify however you like.
- Its more of a Demo rather than a game.


# Notice
    
    The Project is On hold as I'm thinking on how to implement the render api.
    I mean ncurses is great and all but Im also thinking on creating an sperate
    OpenGl based renderlib.
    Thing is I dont know OpenGl ;_;
    For the next few days I'll be learning OpenGl.
    So yeah..._

### Installation & Execution

#### Dependencies
Ztrog, as of curent only need ```ncurses``` and standerd C library.

For Installing it just run
```
git clone https://github.com/zakarouf/ztorg.git
cd ztorg
./install
```
And it Should Compile the binary named 'z' in newly created directory 'data'.
It can be executed by
```
cd data
./z
```
## Game

After execting the game, it should look like this
![main_menu](https://github.com/zakarouf/ztorg/blob/master/doc/scr/main_menu.png?raw=true)
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

- You can Disable Brush mode by pressing 'v', and change ascii char to draw by pressing key 'c' followed by Character you want draw with.

I'll add more Draw funtion Instruction Once I finalize them(they're there, look into e_main.c{e_mainloop} if ya want to use them.)


NOTE: The Project is everchanging so if the program conflicts w/ any of documentation. Open a issue and I'll fix it up.
---
#### IF ANYONE READING THIS

If you wonder upon this repo and think my coding bollocks.
I'm Still a Novice so if you have ways for me to improve. By all regards hit me up.

Cheers !!!
