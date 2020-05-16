# Zak's Ztorg

This is My First Attempt to have something remotely big Project
And As of Uploading this Repo to Github (5th May 2020), I have only
been coding for few months. I just wanted to do something in Quarentine
So I Decided to learn basic programming. This is it.

### Installation & Execution

For Installing it just run
```
./compile
```
And it Should Compile the binary in current directory named 'ztorg'
It can be executed by
```
./ztorg
```
## Game

After execting the game, it should look like this
```
ZACK v0.2c
/// MAIN MENU ///
PLAY
EDITOR
QUIT  
```
Three options are self Explanatory 
- Select Play to Start At a map.
- Editor to make a Map. 
- Quit to quit.

### PLAY 
This mode as of current is just a free roam in a selected map
- NO NPCs
- NO ENEMIES
- NO TERRAIN FEATURES
I would however, would like to add those features in future.
### EDITOR
As of now Editor is my Main Focus, It is a tool to make Maps for the game.
Starting the Editor will prompt the player to Enter Map X/Y Dimention (Map is always a Rectangle) & Map Name
```
Enter Map Size
X : 70
Y : 100
Map Name : maptest
```
This will auto genarate a Blank Map where you can draw n' stuff.
```
                               | 37
                               | 38
                               | 39
                               | 40
                               | 41
                               | 42
                               | 43
                               | 44
                               | 45
                               | 46
                               | 47
                               | 48
                               | 49
                @              | 50
                               | 51
                               | 52
                               | 53
                               | 54
                               | 55
                               | 56
                               | 57
                               | 58
                               | 59
                               | 60
                               | 61
                               | 62
X - 35 Y - 50
TRAIL - 0: 
```
Now you can Draw by pressing 'v', This will enable trail mode
```
TRAIL - 1:
```
...and then press 'c' followed by ascii char in your keyboard which you want to draw.
Ohh, I forgot to mention, use "wasd" keys to move around.
```
                               | 39
                               | 40
                               | 41
                               | 42
                               | 43
                               | 44
                               | 45
                               | 46
              .....            | 47
            ...   .            | 48
           ..     .            | 49
           .   ....            | 50
           .                   | 51
           .....@              | 52
                               | 53
                               | 54
                               | 55
                               | 56
                               | 57
                               | 58
                               | 59
                               | 60
                               | 61
                               | 62
                               | 63
                               | 64
X - 36 Y - 52
TRAIL - 1:.
```
- You can Disable Trail mode by pressing 'v', and change ascii char to draw by pressing key 'c' followed by Character you want draw with. NOTE 'c' will Not work if trail is disabled(0).
I'll add more Draw funtion Instruction Once I finalize them(they're there, look into g_main.c{g_editor} if ya want to use them.)

---
#### IF ANYONE READING THIS

IF you wonder upon this repo please send me the ways I can Improve
I'm not a CS student and I'm self learning most of my stuff.

Cheers !!!
