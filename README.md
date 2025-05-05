# Bite-Club-1989

## Mac Compile Command
g++ -std=c++11 *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/sfml@2/lib

## Authors:
    Chris Bailey
    Tyler Osso
    Joe Davitt
    
### SetUp on Linux (Ubuntu) system
1. Open the terminal
2. Update the Ubuntu package lists 
```
$sudo apt update && sudo apt dist-upgrade
```
3. Install the GNU compiler tools (gcc/g++) and the GDB debugger
```
$ sudo apt install build-essential gdb
```
4. Install git
```
$ sudo apt install git
```
5. Install SFML libraries
```
$ sudo install libsfml-dev
```
### Clone, Compile and Run
1. Clone the repository
```
$ git clone https://github.com/Bite-Club-1989/Bite-Club-1989.git BiteClub1989
```
2. Go to the BiteClub1989 directory
```
$ cd BiteClub1989
```
3. Go to source file
''
$ cd src
''
4. Compile the project (Mac)
```
$ g++ -std=c++11 *.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/sfml@2/lib
```
5. Run the game 
``
$ ./sfml-app
``
## Game description
Game will greet player with a splash screen. They will be able to press enter to start the game.

### Title Screen

![Splashscreen with press enter](/assets/readmeScreenshots/SplashScreen.jpeg)

### Controls
The game will allow players to:
    '#000000' **W A S D** '#ffffff' to move
    '#000000' **SHIFT** '#ffffff' to sprint
    '#000000' **L-Click** '#ffffff' to shoot
    '#000000' **Mouse Direction** '#ffffff' shoot direcrtion

### Gameplay/Hud
Player must avoid enemies while eliminating all enemies for that level to continue

![Gameplay Image](/assets/readmeScreenshots/Gameplay.jpeg)

Player Health and Stamina is displayed in the top left corner

![Health/Sprint](/assets/readmeScreenshots/HealthSprint.jpeg)





