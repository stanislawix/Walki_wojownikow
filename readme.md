# Warrior Fights - a simple C++ studies project for understanding inheritance and polymorphism

## Introduction
This project showcases the use of inheritance and polymorphism in C++ by creating a program with classes `Wojownik`, `Mag`, `Polimorf`, and `Rycerz`.

## Classes
### Wojownik (Warrior)
This is the base class for all warrior classes. It includes basic information about the warrior such as their name and level.

### Mag (Mage)
This class extends the `Wojownik` class and adds information about the mage's spells and magical abilities.

### Polimorf (Polymorph)
This class extends the `Wojownik` class and adds information about the polymorph's shape-shifting abilities.

### Rycerz (Knight)
This class extends the `Wojownik` class and adds information about the knight's weapons and armor.

### Skills
Each of the classes has a dedicated skillset that is specific to the class. The skillsets of `Mag`, `Polimorf`, and `Rycerz` classes inherit the skillset of the `Wojownik` class.

The program simulates, through a verbal description, fights of warriors.
You can create up to 10 warriors.
Warriors can be of three types: knight, mage and polymorph.
All warriors have a few features and skills in common, such as 'life level' or 'attack' and features that belong only to a given type.
Before the fight, the characteristics of the opponents are set randomly.
When there is a fight, the 'attack' power of each opponent is calculated based on the value of all their attributes.
The fighter with the most attack power wins.
The winner takes on all the traits of the loser that he did not have before.
The loser is annihilated.
Battles continue until only one warrior remains.
