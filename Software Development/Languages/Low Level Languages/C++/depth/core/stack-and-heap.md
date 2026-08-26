# Stack And Heap

Stack ~2mbs.                Hot cache
Heap bigger and can grow.   

Both are in the ram. The main difference of them is how they alloc the memory.

## Stack

Fast af cuz its a stack 1 operation to just move the stack ptr and that kinda it

Scope stuff you know the drill

## Heap

Slower as requires a lot more cpu tasks

 0x0000000000000000
  |    Heap (Unlimited? (limited by virtual memory))
  |      Slow, pointer indirections, cache misses?
  |      "new" variables
  v

 Unused

  ^
  |
  |    Stack (Limited)
  |      Fast, known location
  |      "local" variables
  |
 0xFFFFFFFFFFFFFFFF
