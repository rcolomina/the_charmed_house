# The Charmed House

Where nothing is as it seems .

# Introduction

This is an old style convensational game based on a text line commander under Linux OS. The project pretens to be a framework that can be a machine for creating conversational games from text files or configuraiton files. 

The player interacts with the word typing simple phrases formed by verbs and names. It has a simple command line interface: 

\<command\> \<parameter1\> ... \<parameterN\>. 

Usually, these comands or verbs will accept one parameter or two parameters. Rarelly a command will have 3 or more parameters, but it has been left open to get the possibility to build a more complex conversational game or framework. 

The world is divided into scenes. A player much use cardinal points to oriented himself in around. In the scenes, there are many objects available that can be used with others objets. All scenes and objects have descriptions that give clues to the player to solve the puzzles. This game will have an inventario allowing the player to pick up, drop or  bring objects between different scenes. Sometimes the game would be a little tricky to solve but descriptions will help the player.

The scenes have a mix of text and images that are shown in all of them as pure text converting from pictures. The game presents to the current player situations not only described with text, but ilustrated with old styple console primitive graphics.

# Game argument

This is an example of argument that we would have to generate the world.

"Tony is a little extusiastic adventure boy . He is a natural explorer by default. Always had thought to enter in the old advandon, charmed and terrific house which is near from his home. One day, when he was dreaming, a strange force claimed him to entered in house. That felling persisted at next day, therefore he could not resist to explore the house. Here is where our adventure starts. "

# Installation process

This program has its own Makefile which make easy the compilation process using GCC compiler versiom 4.4.7.

# Playing

At the beginning of the game, the player starts with a prompt. In this prompt the player can type commands to move around the world, pickup or drop objects, use them or combined with others, push buttons, open doors, traps, etc. 

