# Description
THis is a simple fighter game 
# figures
Different from other fighter games,this game has taken some physical effects into account.the hero and enemies in this game both have accelloration,i.e. non-constant-velocity motion.what the player controls is the hero's accelloration,instead of position.The velocity of the bullets of the hero is calculated by relative velocity principle.
# Operates
Use the four arrow keys to control the plane,space to fire,b to use bomb,enter to pause game.
# Technical details
## classes
this game mainly contains the following classes:
**Fighter**
**Enemy**
**bullet**
**hitTestable**
*used to test whether to fighters are hitted*
**game scene**
**GameEventListener(interface)**
## Game period
this game has a main loop,at every loop,the function react() updates the posotions of every planes and bullet,and do others,such ad hit test.

