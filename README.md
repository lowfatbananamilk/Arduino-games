# Arduino games

This project focuses on **creatively designing** games on **limited I/O**

I'm using an Arduino UNO with only three buttons, one 16x2(char) LCD and one buzzer

You can find the detailed wiring in the code
***

I know stuffing everything in one file is a huge mess... This is due to my limitation.

check out `game-code-separation` branch! Maybe give a little hand too??
***

I have uploaded the `ready_steady_bang_(original).ino`

If you wanna try it out, make a 'sketch' folder named `ready_steady_bang_(original)`. It should work there.

It also requires `pitches.h`. You should be able to find it in the repository.

It also uses the same wiring as the current project.
***

To-Do list: RSB
+ Add penalty when a player shoots too early
+ Add ability to quit the game
+ New play() function that uses `tone(PIZO, pitch, length);` method
+ Add one-player mode
