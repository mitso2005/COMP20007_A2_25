# COMP2007 Assignment 2 (Sem 1, 2025): Dynamic Programming Solutions

## Task 1: Feeding and Breeding Eels - Episode II

### Overview
You play the role of an eel in the river systems of the Kulin Nation, needing to reach the ocean for the breeding season (Iuk) while maximizing fat reserves for the journey to the Coral Sea.

### Problem Description
The eel must:
- Navigate through a system of lakes and rivers
- Reach the ocean within a time limit
- Maximize fat reserves upon reaching the ocean
- Maintain fat levels between 0 and maximum capacity
- Consider river traversal costs and lake food gains/losses

### Part A: Basic River Navigation
- River traversal takes exactly 1 day
- Each river crossing costs fat
- Lakes can increase or decrease fat reserves
- Must find optimal path maximizing final fat reserves

#### Input Format
```
N M S O       # Lakes, Rivers, Start ID, Ocean ID
K F C         # Initial fat, Max fat, Time limit
gain[0..N-1]  # Fat gain/loss at each lake
M lines of:   # River connections
u v w         # From lake u to v, cost w
```

#### Output Format
```
Max fat: X
Path: lake1, lake2, ..., oceanLake
```
Or if no valid path exists:
```
No path :(
```

### Part B: Advanced River Navigation
- River traversal time equals fat cost
- Modified dynamic programming solution required
- Same input/output format as Part A

### Part C: Written Analysis
Requirements for `written-1C.pdf`:

#### Part A Analysis
1. **State Representation**
   - Define DP states and parameters
   - Fat level management
   - Time limit handling

2. **Recurrence**
   - Formula and rules
   - Base cases
   - Correctness justification

3. **Time Complexity**
   - Time and space complexity analysis
   - Big-O notation with defined terms

4. **Backtrace**
   - Location of final answer
   - Solution reconstruction process

#### Part B Analysis
- Document only differences from Part A
- Reference overlapping elements
- Update relevant sections

### Implementation Notes
- Solutions must be implemented in C
- Program arguments: part letter (A/B) and input filename
- Recommended length for written analysis: 1-2 pages