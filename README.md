# GeneralFifo
## Description:
A C program that generates test  maps for a Tents and Trees game, based on an already existent map. 

## Implementation details:
The fifo is implemented via a list of tables. When a table fills,
another one is allocated and the new table's size is proportional to the number of tables allocated.
  
## Function list:
### Initialization & Termination
- initFifo
- freeFifo 
### Properties
- isFifoEmpty

### Search
- itemExists

### Insertion & Removal
- queue
- dequeue

## Dependencies:
- stdlib.h
- stdio.h
- string.h

