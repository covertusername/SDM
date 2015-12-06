# SDM
Simulator for the Small Demonstration Machine.

Please not that this machine does not yet (and may never) have a physical form,
and that this instruction set is of my own design. As it is purely for
demonstration purposes, it will never do anything useful, or be marketed,
unless I accidentally get sent back in time to around 1950, where this machine
could actually compete.

It has a 16-bit word size and an 8-bit data size. The leftmost 4 bits define the
instruction, and the rest define the data that the instruction works with. Only
the `stoa` instruction actually uses this as data, the rest either don't use it
at all or use it to reference a memory or device address.

Futher details are located within the "specs" file.
