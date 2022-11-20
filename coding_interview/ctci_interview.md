# Cracking the coding interview -- interview prep

## Interviewing Process

Explain the thought process out loud

Interviewer is looking for:
  * structured thought + clean code
  * discussion of tradeoffs and errors
  * optimality
  * quickness

Focus on big picture, abstracting away helper methods + structures

Your performance is relative to other applicants

## Behavioral Questions

| questions   | project 1 | project 2 | project 3 |
|----------   | --------- | --------- | --------- |
| challenges  |           |           |           |
| failures    |           |           |           |
| enjoyed     |           |           |           |
| lead        |           |           |           |
| conflicts   |           |           |           |
| if re-doing |           |           |           |

Ask interviewer questions at the end:
  * personal -- what brought you here? what's been most challenging?
  * insightful -- do research and ask questions about products / methods
  * passion -- what opportunities are there here to learn about x?

Think about how you would scale your projects

Leave nitty gritty technical details out, and just say "I can go 
into more details later if you'd like"

Lead with punchline, then go into STARER story (see career/interview.md)

Avoid rambling on during S (situation) step

Hobbies are fluff, but can be especially good if unique, technical, or 
show positive personality trait. Highlight any successes.

## Technical Questions

Solve problems yourself (with 30 min time limit, according to others)

Consider space and time efficiency

Code on paper!

Type paper code verbatim into computer to test

Don't worry about obscure DSA. Focus on:

| data structures | algorithms    | tools        |
| --------------  | ------------- | ------------ |
| linked list     | breadth-1st   | bit manip    | 
| tree/trie/graph | depth-1st     | memory       |
| stack/queue     | binary search | recursion    |
| heap            | mergesort     | dynamic prog |
| arraylist       | quicksort     | big o        |
| ❗hash table❗  |               |              |

Understand use cases, space+time complexity, advantages, disadvantages

Memorize some powers of 2
  * 2e7 = 128
  * 2e10 = 1024 ~ 1 thousand
  * 2e20 = 1 million
  * 2e30 = 1 billion
  * 2e40 = 2 trillion

Problem walkthrough:
1. Note details and repeat back to interviewer
  * write notes on whiteboard
2. Do big example
  * realistic, large, not special case
3. Find quick brute force method, with runtime
4. Optimize 
  * consider best possible runtime
  * use extra info
  * try new example
  * make time-space tradeoff, with hash table
  * precompute info or save with memoization
5. Walk through approach in detail
  * write high-level pseudocode
6. Implement with modularization
  * pretend you have small initializers / helpers, then fill in later
  * pretend you have classes / structs, then fill in later
  * write small functions
  * note that you would implement asserts/if statements to check input
7. Test w small cases, paying attention to hotspots

Optimization:
1. Bottlenecks, Unnecessary work, Duplicated work (BUD)
2. Do examples by hand, then notice pattern
3. Try a simpler version of the problem, then scale back to full version
4. Reverse recursion -- build up from base case
5. Think of appropriate data structures and similar algorithms
  * e.g. adapting merging 2 sorted arrays algo to find matches

Admit if you've seen an exact problem before

Be excited about tough problems!
