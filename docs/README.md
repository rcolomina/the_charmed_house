# The Charmed House

Where nothing is as it seems.

# Introduction

This is an old style convensational game based on command line interface (CLI) running under Linux OS. The project pretens to be a framework for creating conversational games aventures directly from configuration text files. 

The player may interacts with the word typing simple phrases formed by a single verb followed by one or more names as it is expresed as follow: 

\<command\> \<parameter1\> ... \<parameterN\>. 

Usually, these commands will accept a single command followed by one or more parameters. Rarelly a command will need more than two parameters, but anyway, it has been left opened to get the possibility to the engine to build more complex conversational game.

In this engine, the world has been divided on scenes. Once these scenes and its connection are defined, a player could navigate throughout the world using cardinal points. On the scenes, objects can be defined for the scenes, which a player can interat. 

All scenes and objects have its own descriptions, which give clues to a player to solve a proposal puzzle to struggle him. A player hava an inventory allowing the player bringing with him objects. A player can pick up, drop or bring objects between different scenes. Sometimes, if a game may be tricky to solve, if good descriptions have been defined, they will help to the player to avoid be stucked on the game moving forward on it.

The scenes have a mix of text and images that are shown as pure text which have been taken from converting pictures to text. The game presents to a player situations not only described with text, but ilustrated with old style console primitive graphics.

# Game argument

This is an example of argument that we would have to generate the world.

"Tony is a little extusiastic adventure boy . He is a natural explorer by default. Always had thought to enter in the old advandon, charmed and terrific house which is near from his home. One day, when he was dreaming, a strange force claimed him to entered in house. That felling persisted at next day, therefore he could not resist to explore the house. Here is where our adventure starts. "

# Installation process

This program has its own Makefile which make easy the compilation process using GCC compiler versiom 4.4.7.

# Playing

At the beginning of the game, the player starts with a prompt. In this prompt the player can type commands to move around the world, pickup or drop objects, use them or combined with others, push buttons, open doors, traps, etc. 

