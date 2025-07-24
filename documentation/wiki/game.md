# How to play my game Creation Termination

Creation Termination is a simple bullet hell adjacent game, where the player is a witch that is trying to hit a creature on the right side of the screen that is seemingly flying away while trying to survive against a multiple waves of enemies. 
The end goal is to obtain a score of 5000 which is reached by managing to hit the creature enough and not die until the goal has been reached. 

1. Start
 The first thing the player is greeted with is a cut scene that explains the short story behind the character (the witch) that represents the player. 
 This cut scene can be skipped with a click on the a button in the upper right corner. 

2. Input
 - The keys W A S D move the character along the y and x axis. The movement outside the window frame is not possible. 
 - There are four types of shooting abilites:
    - The first is the default shooting triggered with the SPACE key. A relativley average sized fireball is being fired in a straight line. Default fireballs reduce enemies health by 2 each and a hit on the creature
    gives 40 points
    - The second type is the spread or wave shot, triggered by the E key. Those fireballs are smaller but 6 are fired at once and each is spreaded out with different angles, making hitting enemies and the creature
    a lot easier, but each wave fireball only reduces enemies health by 0.5 and on creature hit only gives 20 points.
    - The last type is the charge shot and like the name implies: While holding the F key the fireball is being charged and gets bigger but it has a maximum size. Not only the size increases but the damage output as 
    well, so that at maximal size the fireball reduces enemies health by 6 and on creature collision 150 points. While it is being charged, it does not collide with the enemies, so it can only show its potential
    after it has been fired (after the key F has been released). 
    - With pressing the L_SHIFT key a shield activates. This shield kills everything it touches except the creature. The shield also has cooldown or must first recharge after use. It can't produce points if it touches the creature, its main purpose is to get out of difficult situations. 

3. Core Mechanics
 Like previously said the goal of the game is to reach a score of 5000 which is only achieved by hitting the creature with your fireballs. 
 The witch has 7 hit points and after every collision with an enemy or a misssile form an enemy, loses a hit point. After every hit their is an invurnable state of around 2 seconds, where the witch can't be hit.
 A clock is ticking in the background increasing the difficulty of the game, meaning that at the beginning it is adviced to increase the score as much as possible, because later in the game it will be very hard to reach the creature. The first difficulty phase only spawns little enemies, the bats who have only 2 hit points. During the first phase the bat waves are also rather small and sparse. The second wave introduces medium big enemies, the big birds that are a bit bigger in size, have 5 hit points. The waves sizes increase and waves appear more often. The third and the last phase includes the biggest enemy type, the dragons,
 which have 20 hit points. They also are the only type of enemy capable of firing fireballs themselves. 
 The movement pattern of the bats and big birds is the same and fluctuates randomly between a diagonal line accross the screen or a block of enemies moving along either a cosine or sine function.
 The dragons appear from above to the middle of the screen and continues to move along the y axis randomly up and down. The same movement is what the creature is doing on the far right end of the screen. 
 No matter the enemy type, the witch always looses one hit point on collision. 

4. How to Quit mid game
 Press the Key O