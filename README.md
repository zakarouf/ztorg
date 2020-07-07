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
```
ZTORG
----------------------
0. PLAY
1. EDITOR (NEW)
2. EDITOR (OPEN)
3. QUIT
>> PLAY
```
- Press Num keys to traverse Menu.
- To Countinue w/ Selected option Press 'e'.
- Three options are self Explanatory.
- Select Play to Start At a map.
- Editor to make a Map. 
- Quit to quit.

### PLAY 
This mode as of current is just a free roam in a selected map.
I would however, would like to add RPG features in future.
### EDITOR
As of now Editor is my Main Focus, It is a tool to make Maps for the game.
```
ZTORG
----------------------
0. PLAY
1. EDITOR (NEW)
2. EDITOR (OPEN)
3. QUIT
>> EDITOR (NEW)
```
In Main Menu Press '1' to select Editor w/ A clean slate.
Starting the Editor will prompt the player to Enter Map X/Y Dimention (Map is always a Rectangle) & Map Name.
```
Enter Map Dimention
13 41
Enter Map Name
mymap
```
This will auto genarate a Blank Map where you can draw n' stuff.
```

             | 2
             | 3
             | 4
             | 5
             | 6
             | 7
             | 8
             | 9
        @    | 10
             | 11
             | 12
             | 13
             | 14
             | 15
             | 16
             | 17


Brush[OFF] -> Floor/Space || 0



X - 8 || Y - 10
```
Now you can Draw by pressing 'v', This will enable Brush mode
```
Brush - 1:
```
...and then press 'c' followed by ascii char in your keyboard which you want to draw.
Ohh, I forgot to mention, use "wasd" keys to move around.
```

             | 4
             | 5
             | 6
             | 7
             | 8                                                        0 - Floor/Space
             | 9                                                        1 - WALL
     ##..    | 10                                                       2 - WALL_MOVEABLE
     #       | 11                                                       3 - WALL_BREAKABLE
     @       | 12                                                       4 - WALL_INVISIBLE
             | 13                                                       5 - FLOOR_TOXIC
             | 14                                                       6 - FLOOR_WATER
             | 15                                                       7 - FLOOR_NULL
             | 16
             | 17
             | 18
             | 19


Brush[ON] -> WALL || 0



X - 5 || Y - 12
```
- You can Disable Brush mode by pressing 'v', and change ascii char to draw by pressing key 'c' followed by Character you want draw with. NOTE 'c' will Not work if Brush is disabled(0).

I'll add more Draw funtion Instruction Once I finalize them(they're there, look into g_main.c{g_editor} if ya want to use them.)

---
#### IF ANYONE READING THIS

IF you wonder upon this repo please send me the ways I can Improve
I'm not a CS student and I'm self learning most of my stuff.

Cheers !!!
