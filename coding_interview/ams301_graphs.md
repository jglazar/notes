# Applied combinatorics -- graphs

## Mastermind

Guess secret code of 4 colored pegs, with repeats allowed

Answerer gives # right color + right spot and # right color + wrong spot

Just like sudoku -- deduce only possible slots first, then move on
  * Assumptions generate helpful consequences

## Chapter 1 -- Basic graphs

Connected = path between every pair of vertices
  * Non-connected graphs can be decomposed into components

Bipartite = edges only connect V1 to V2, not within V1 or V2
  * iff every circuit has even length

Trees have a unique path between any pair of vertices
  * Minimal connecting sets are always trees with v-1 edges

✅ Build a directed graph for turn-based games, then backtrack from 
win condition to force opponent to give you the win

### Edge covers and independent sets

For edge cover, min number of watchers is x * max degree = total edges

An independent set comprises vertices like islands w.r.t. each other

Vertices left over from an edge cover ARE an independent set, since the 
edge cover acts as an intermediate
  * So, finding the biggest independent set is same as 
  finding the smallest edge cover

### Planar graphs

Planar = no crossing edges

All planar graphs can be 4-colored. k-complete subgraphs require k colors.
  * 5-color proof takes away deg-5 vertex, then posits that re-inserting 
  it can use a color not used for the neighboring deg-<5 vertices

Must contain a vertex with degree <= 5 bc if all were 6+, then 
e = 3v > 3v - 6

Circle-chord method: make circle circuit with all vertices, then draw 
chords inside or outside circle as-needed

❗️ Nonplanar graphs always contain K33 or K5 complete subgraphs
  * so, finding a K33 means a graph must be nonplanar!
  * find K33 by removing deg-2 vertices and combining their edges
  * circle-chord construction helps identify K33

❗️ Number of regions is invariant across different drawings
  * Euler formula: R = E - V + 2 (incl. outside)
  * also, e <= 3v - 6 because regions have sum of degrees = 2e >= 3r
    * e <= 2v - 4 for bipartite because no deg-3 regions allowed

### Misc

Vertex basis is set of vertices who have directed path to all other 
vertices
  * Generally easier to draw out all paths directly, then work with 
  expanded graph for vertex covering, e.g.

Isomorphic graphs must have same # vertices and edges, and all vertices 
must have matching degrees (`set` of vertex degrees must match)
  * Subgraphs of corresponding vertices must be isomorphic
  * Chordless circuits (pure circuits) must be preserved
  * Compare subgraphs of degree-n vertices
  * Compare complementary graphs (connect unconnected and 
  disconnect connected)

❗️ Sum of vertex degrees = 2 * num of edges
  * so, number of odd-degree vertices must be even

## Chapter 10 -- Graph games

Progressively finite = two players take turns until one wins

Cannot contain directed circuit! Otherwise game could loop forever. 
No ties allowed either.

Vertices adjacent to winners are losers. Prewinners force opponent 
to go to loser. Want to go to winner first.
  * all winners are in the "kernel", which is the set of vertices 
  s.t. no edge joins pair and each vertex has edge to non-kernel vertex

Grundy number gives a vertex the smallest non-neg int not 
assigned to vertex's successor. Assign 0 to winners.

### Nim

k piles with variable values. Can remove as much from a pile as desired. 
Player who clears last pile wins.

Graph is too big. (n1+1)(n2+1)...(nk+1) possible positions.

Digital sums (binary sums modulo 2) give solutions to Nim.

## Chapter 2 -- Circuits and colorings

Multigraph = multiple edges b/t 2 vertices allowed

Euler cycle visits all edges once and lands where started
  * ❗️ iff even degree at each vertex, and connectedness
  * Euler trail exists if all but 2 vertices have even degree

Directed Euler cycle iff connected (ignoring directions) and each 
vertex has deg-in = deg-out

Hamilton circuits/paths visit each vertex exactly once
  * No easy way to determine, problem is NP-complete
  * ❗️ Exactly 2 edges incident to each vertex (delete others from 
  consideration), no proper subcircuits allowed (no triangles, e.g.)

Tournament = endow direction to each edge in complete undirected graph. 
Guaranteed to have a Hamilton path.

✅ For grids, try coloring vertices to emulate a chessboard. There's a 
bipartite structure.
  * m x n grids with m,n odd have no Hamilton cycle

✅ Sitting around circular table is Hamilton cycle. Possible pairings 
forms complete graph.
  * Useful theorem: n! different Hamilton cycles on complete-n graph
  * Useful theorem: (n-1)/2 unique Hamilton cycle partitions on 
  complete-n graph for prime n

❗️ Complete-n subgraphs require n colors. Can ignore other vertices with 
degree < n
  * Color problems are easy -- just follow the chain reactions

Generally, wheel graphs with perimeter + central spokes require 3 colors 
for even # of spokes and 4 colors for odd # of spokes

Examples:
  * Vertex coloring -- Committee scheduling where vertices are committees 
  and edges indicate overlap
 * Edge coloring -- Tournament scheduling where vertices are players 
  and edges are matches
    * Find a rule! 10 edges, max 2 games / day -> min 5 days
  * ✅ Try identifying what corresponds to vertices, edges, and colors 

### Color theorems

Vertices of triangulated polygon (external planar shell) can be 3-colored

Color number <= max degree if no odd circuits and not complete graph

Color number for edge coloring = max degree or max degree + 1

Chromatic polynomial gives number of valid colorings with x colors
  * k(k-1)^n for trees / paths
  * k! / (k-n)! for complete-n graphs
  * break into separate cases and add

## Chapter 3 -- Trees

Undirected tree has no circuit. Can define root that contains 
a unique path to any other vertex. Any vertex can be root. Removing 
any edge disconnects tree.

Directed tree has only 1 root

❗️ Contains n vertices and n-1 edges. m-ary tree has n = mi + 1 and 
l + i = n, where l = leaves and i = internal vertices. l <= m^height
  * n-1 because each team is eliminated in a tournament except 1

Balanced trees have all leaves at bottom and bottom-1 levels, minimizing 
overall height

There are n^(n-2) possible undirected trees with n vertices. This is due 
to a correspondence to (n-2) length sequences and trees, through Prufer 
sequencing.


