# Graph neural networks

## A gentle introduction

https://distill.pub/2021/gnn-intro/

Started around 2009

Node info is identity and degree; edge info is identity and weight; global info
is number of nodes and longest path

Example data:
  * Images are encoded as adjacency matrix (w diagonals)
  * Text is encoded as directed graph
  * Molecules have atoms as nodes and bonds as edges
  * Social interactions, incl social media and scientific communities

Graph neural networks can do graph-level, node-level, and/or edge-level preds
  * Graph-level: label entire molecule or image
  * Node-level: label each node as belonging to class, like image segmentation
  * Edge-level: Predict relationships b/t elements

Representations
  * Sparse adjacency matrices are inefficient. Require permutation invariance
  * Adjacency lists may be good for sparse graphs

Message passing gathers neighbor embeddings, then aggregates and updates
  * Node embeddings are still n-dimensional
  * Similar to convolutions
  * Can pass messages between nodes+edges, nodes+nodes, or edges+edges
  * Master node (global context vector) serves as hub to pass global messages

Can have different edge types, edge weights, hypernodes (representing clusters)

Aggregators must output same value for all nodes in a group
  * Mean takes normalized view, max highlights outliers, sum does both (popular)

GCN of k-layers with 1-degree neighbor lookup is same as k-subgraph embeddings

Attention weights node-node pairs during aggregation. Transformers are just
dense GNNs with attention

## Convolution on graphs

https://distill.pub/2021/understanding-gnns/

Graph Laplacian = D - A, where D = A dot 1
  * Polynomials = pw(L) = sum(wi L^i) act as weighted filters
  * Feature vector convolved with filter = pw(L) x
    * L x = Dx - Ax = Dx - sum(x), where sum is taken over 1st neighbors
    * Higher degree --> further neighbors

ChebNet defines polynomials as sum(wi Ti(L')), where Ti is degree-i Chebyshev
polynomial and L' is normalized = 2L / lambda - I, where lambda is biggest eval
  * Makes interpolation more numerically stable
  * Has eigenvalues in range [-1,1], preventing blowups

Basic GNN iterates g = pw * h, then h = sigmoid(g), where h is feature vector

Message-passing generalizes to any aggregator and combiner fcts
  * Graph convolution network -- mean of neighbor embeddings
  * Graph attention network -- weighted mean of neighbor embeddings
    * Weights are Boltzmann with energy = ReLU(weighted avg of node and neigh)
  * Graph sample and aggregate (GraphSAGE) -- mean/max/LSTM/RNN aggregators with
    neighborhood sampling, which provides good performance on large graphs
  * Graph isomorphism network -- sum of neighbor embeddings

Laplacian tells how smooth x is w.r.t graph
  * Rayleigh quotient = x^T L x / x^T x = sum((xi - xj)^2)) for neighbors

Eigenvectors of smaller evals represent higher frequencies and are less smooth
  * Smooth evecs capture global info, wiggly evecs capture local info

Convolution of spectral representations of features is more efficient than raw
  * Also forces neighbor nodes to get similar representations
  * Can be too expensive for large graphs
  * Need eigenvectors for each new graph

Global properties can also be captured by aggregating all node info and message
passing (via master node, e.g.). Ignores topology, tho, unlike spectral methods
  * Default -- Predict on aggregation of node representations
  * SortPool -- apply NN to top n nodes
  * DiffPool -- cluster nodes and coarsen, then recurse until 1 cluster remains
  * SAGPool -- keep top n % of nodes, then repeat until 1 remains

General form presented in these notes: `hk = inv(D) A h(k-1) Wk^T + h(k-1) Bk^T`
  * Dropout works well, esp. in form of DropEdge
 
## Stanford notes

Traditional approach engineers node-level, edge-level, and graph-level features
from graph and performs ML

Graph representation learning automatically learns features

Desire embedding that preserves similarity bt nodes
  * Must define similarity function bt nodes. Similarity bt embeddings is simply
    dot product
  * Encoder could simply be Z dot v, where Z is matrix of each node's encoding

Random walk embedding has zu^T zv = prob that u and v are on same random walk
  * DeepWalk -- random walk; node2vec -- biased local and global walks
  * These can be formulated as graph Laplacian matrix factorization

Node degree counts neighbors; node centrality accounts for node importance
  * Eigenvector centrality = 1/lambda * sum of neighbors' centr.  = big evector
  * Betweenness centrality = sum (paths from s to t with v / total paths s to t)
  * Closeness centrality = 1/sum(shortest path length bt u and v)
  * Clustering coefficient = edges among neighbors / neighborsC2 = # triangles
  * Graphlet degree vector = # graphlets a node touches

## Spectral graph theory

### Tutorial on spectral clustering

Graph Laplacian is discrete analog to continuous Laplacian, which is 2nd deriv
  * Highlights edges in images, where there's high "curvature"

Eigendecomp of Laplacian (or original adj. matrix) is permutation invariant

Lowest eigenvector is 1-vector, since all rows must sum to 0
  * Degeneracy of eigenvalue 0 is number of clusters

Normalization reduces influence of a few highly connected nodes
  * Unnormalized = L = D - A, where D is diagonal degree matrix
  * Symmetric = Lsym = D^-1/2 L D^-1/2 = I - D^-1/2 A D^-1/2
  * Random walk = Lrw = D^-1 L = I - D^-1 A = I - P, where P is Markov matrix
  * Use normalized Laplacian, esp. random walk. 
    * Normalized Laplacians maximizes within-cluster similarity and are
      statistically consistent (converge with more sampling)
    * Symmetric's evecs are multiplied with D^1/2

Clustering algorithms:
  * Collect first few evecs of L, then perform k-means clustering on rows, using
    evec values as features
  * Collect first few generalized evecs that solve Lv = l Dv (evecs of Lrp),
    then proceed as above
  * Collect first few evecs of Lsym, then normalize row sums to 1, then proceed

DeepWalk has similar performance, wherein you run random walks from each node
(simulating the Markov matrix rather than calculating its eigenvalues)

Works on feature-free (non-attributed) graphs
