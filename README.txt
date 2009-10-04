h1. U.B.E

This is the trunk of U.B.E, a puzzle game by Pierre-Henri Trivier.

The game is an extension to 'boots-puzzle'.

h2. Install

TBD (hint : use scons)

h2. Game design

The game board is divided in cell. You must go from the starting cell
to the ending cell.  

Not every cell is reachable at soon. For example, at the beginning you
can only move to any adjacent cell, but you cannot jump gaps. 

By collecting power-ups, you gain new ways of moving. For example, the 
double-cell jumper mode lets you jump over gaps of one cells.

To move in the board you hover the mouse over
cells. If a cell is reachable, a path from your position to the cell
is drawn. If the cell is not reachable, you see a "forbiden" sign.

You collect power-ups by reaching some cells.

Grids contains special cells, such as : 

 - tunnels that take you from a cell to another
 - switch cells that activates mechanism (destroy cells, create new cells, etc...)

The game is an infinite succession of puzzles of increased difficulty. 

Your goal is to solve puzzles in as little time and ass little moves as possible.

h2. Technicalities

The game will be written in C++.

It is in 2D. Sprites will be animated at all time.

It should be cleanly i18n-ized from day one (strings will be externalized properly, using po files ? )

It will use the SDL for display and input handling.

It will use SCons as its build System. 

It will use Google Test for its unit testing.

It should be possible to run it under GNU/Linux and Win32 at least 
(MacOS X should be handled, as SDL is too).

