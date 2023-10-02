# Deep learning

## Introduction (Chapter 1)

Solving problems via intuition requires experience and heirarchies 
of knowledge. Avoids formal specification.

Formal constrained environments like chess are easy for computers 
but hard for humans.
  * Knowledge base approach tries to (unsuccessfully) specify 

Choice of representation (features) is hugely impactful on 
model performance
  * Representation learning automates feature selection. E.g., 
  autoencoder
  * Factors are unobserved sources of influence. E.g., car color, 
  position, and light source angle.
  * Representation learning has issues when finding features is 
  as hard as original problem (e.g., identifying speech)

Deep learning expresses representations in basis of simpler 
representations.
  * NN also be considered a sequential program with parallelized 
  steps. States at each steps act like pointers to previous data.
  * Depth is length of longest path through network of operations 
  (add, multiply, softmax, ...) or concepts (colors, edges, 
  corners, ...). 

Software: input --> program --> output. 
ML: input --> designed features --> mapping --> output. 
Representation learning: input --> features --> mapping --> output. 
Deep learning: input --> simple features --> abstract features --> 
mapping --> output.

### History

Cybernetics (1940 - 1970), Connectionism (1980 - 2000), Deep learning 
(2006 - present)

Historic DL focused on reproducing / understanding animal brain. 
Modern DL focuses on multiple levels of composition. Neuroscience 
is no longer useful as a guide.

Linear models cannot learn XOR --> decline in NN research.

Single algorithm for whole brain could be possible. E.g., ferret 
brain can be rewired to process vision in auditory area of brain.

Connectionism used a distributed representation, which has inputs 
mapped to many features and features activated by many inputs. 
E.g., separate color and animal nodes rather than many color-animal 
combo nodes.

Connectionism also popularized backpropagation.

Geoffrey Hinton in 2006 developed greedy layer-wise pretraining to 
speed up deep belief network training process.

Big data has helped deep learning. Old algorithms now work 
beautifully due to abundance of training data.
  * Supervised DL needs ~5k examples per category for adequate 
  performance, ~10M examples total for superhuman performance.

Model size has increased. NNs have doubled in size every 2.4 
years. 
  * Animal brains have 1e2 - 1e4 connections per node 
  (relatively sparse!), but 1e4 to 1e11 nodes.
  * Animal brains can use more complicated activation functions.
  * Parallel and distributed computing, plus raw speedups, will 
  enable next-gen DL.

DL has improved object recognition, speech recognition, translation, 
and even self-programming.

Reinforcement learning performs task via trial and error. E.g., 
playing game or piloting robot.

## Linear algebra (Chapter 2)

Vector with negative subscript selects out all elements except 
that index.

Broadcasting is A + b where A is matrix and b is vector. Just 
create B s.t. all rows of B are b.

C = AB = Cij = sum of k ( Aik * Bkj ) = dot product of row Ai and 
column Bj.

Elementwise product is called Hadamard product.

Lp norm = ||x||p = ( sum of |xi|^p ) ^ 1/p
  * Norms always satisfy triangle inequality f(x+y) <= f(x) + f(y)
  * Squared L2 norm has property that derivative w.r.t. one element 
  depends only on that element, rather than entire vector.
  * L1 norm grows at same rate in entire space. Higher norms 
  grow slowly near origin. L1 useful for cases when small vectors 
  are still important.

Diagonal matrices simply scale corresponding vector elements. 
Inverse is simply inverse of each diagonal element. Rectangular 
diagonal matrices pad out zeros (m > n) or delete elements (m < n).

Symmetric matrices have A = A^T, and often are produced by function 
where order of 2 inputs doesn't matter (distance, e.g.). Orthogonal 
matrix has orthonormal rows and orthonormal columns, so inv(A) = A^T.

Prime factorization is pure representation of number. Holds regardless 
of base system!

Eigendecomposition of A = V diag(lambda) inv(V) where V is matrix 
with eigenvector columns. All real symmetric matrices have real 
orthogonal eigenvectors and real eigenvalues. Others can involve 
complex numbers.
  * Can choose different eigenvectors if there's a space sharing 
  eigenvalues. Just select two new orthogonal vectors. Thus, 
  eigendecomposition is unique iff eigenvalues are unique.
  * Matrix is singular (dependent cols) iff some eigenvalue = 0
  * Max/min of quadratic form of x with A s.t. L2 norm of x = 1 is 
  max/min eigenvalue of A.
  * Positive semidefinite matrices has quadratic form of x with A 
  always >= 0 because all eigenvalues are >=0.

Every real matrix has an SVD. A = U D V^T with U = (m x m), D = 
(m x n), V = (n x n). 
  * U and V are each orthogonal. D is diagonal. 
  * D's elements are called singular values of A. U's columns are 
  left-singular vectors. V's columns are right-singular vectors. 
  * Left-singular vectors are eigenvectors of A A^T and right-singular 
  vectors are eigenvectors of A^T A.
  * Nonzero singular values are square roots of eigenvalues of 
  A A^T and A^T A

Moore-Penrose pseudoinverse is A^+ = inv( A^T A + aI ) A^T = 
V D^+ U^T. This helps solve Ax = b when A isn't square. 
  * If m < n, solution has minimal L2 norm for x.
  * If m > n, solution has minimal L2 norm for Ax - y

Trace operator gives alternative way to write expressions
  * Frobenius norm = sqrt( Tr( A A^T ) )
  * Invariant under transpose 
  * Invariant under cyclic permutation of matrix products, even 
  for different matrix shapes!

Determinant gives volume scaling and equals product of eigenvalues.

### Principal component analysis

Encode point in n-dimensional space into l-dimensional space s.t. 
l < n. Let decoder matrix be D (n x l). 
  * Force D to have orthonormal columns. Then encoder matrix E is 
  just D^T. 
  * Next consider l = 1 and minimize Frobenius norm of 
  ( X - X D D^T ). Rewrite using trace and cyclic permutations and 
  take derivative w.r.t. D. Eventually maximize Tr( D^T X^T X D ).
  * Optimal vector D is eigenvector of X^T X with largest eigenvalue.
  * Further vectors have next-largest eigenvalues.

Center columns of design matrix X, then get covariance matrix C = 
1/(n-1) X^T X. Correlation matrix standardizes columns also.
  * This can be diagonalized due to symmetry s.t. C = V L V^T. 
  * SVD of X = U S V^T, so C = X^T X = 1/(n-1) V S U^T U S V^T = 
  1/(n-1) V S^2 V^T
  * Principal components are X V = U S V^T V = U S

## Probability (Chapter 3)

Uncertainty comes from inherent stochasticity (shuffling, e.g.), 
incomplete observation (Monty Hall contestant, e.g.), or incomplete 
model.

Same rules/axioms control frequentist and Bayesian stats, despite 
different interpretations of end results.

Chain/product rule: P(a,b,c) = P(a | b,c) * P(b,c) = P(a | b,c) * 
P(b | c) * P(c)

Independent: P(x,y) = P(x) * P(y). Conditional independence given 
z: P(x,y | z) = P(x|z) * P(y|z).
  * Independence --> zero covariance. Independence excludes linear 
  relationships (hence zero covariance) AND nonlinear relationships.
  * Recall that Cov[X,Y] = E[(X - muX)(Y - muY)] = E[XY] - E[X]E[Y]. 
  * If X is uniform from -1 to 1 and Y is X^2, then E[XY] = 0 and 
  E[X] = 0 so Cov[X,Y] = 0. But P(Y = 1/4 | X = 1/2) = 1 != P(Y = 
  1/4)

Normal distribution is limiting dist for systems with many parts, 
making it a useful approximation. It is also the max entropy dist. 

Multivariate Normal has pdf `sqrt( 1 / ( (2 pi)^n det(S)) ) 
exp( -1/2 (x - mu)^T inv(S) (x - mu) ) = sqrt( det(B) / (2 pi)^n ) 
exp( -1/2 (x - mu)^T B (x - mu) ) `. S is covariance matrix and 
B = inv(S) is precision matrix, which is more convenient.

Exponential dist pdf is `l exp(-lx)` for positive x.

Laplace dist pdf is `1 / 2g exp(-abs(x - mu) / g)`, which is 
sharply peaked around x = mu.

Continuous data have empirical dist. = sum of delta functions = 
`1/m * sum( delta(x - xi) )`. Discrete data have empirical dist = 
multinomial with n = 1 and pi = normalized frequency of point xi.
  * Empirical dist maximizes likelihood of data.

Mixtures have `p(x) = sum( p(x | ci) * p(ci) )`. Component c is 
a latent variable.
  * Gaussian mixture model has p(x | ci) is Gaussian, where each 
  ci has unique associated mu vector and S matrix.
  * Gaussian mixture model is a universal approximator of densities.

### Useful functions

Logistic sigmoid function = `s(x) = (1 + exp(-x))^-1`. Commonly used 
to produce p in Bernoulli dist.
  * derivative = s(x) * (1 - s(x))
  * symmetry: s(-x) = 1 - s(x)
  * log( s(x) ) = -z(x) [see below]
  * inverse = log( x / (1 - x) )
  * integral from -infinity to x = z(x)

Softplus function = `z(x) = log( 1 + exp(x) )`. Commonly used to 
produce mu or sigma of Normal dist. Looks like smooth max(0, x) [RELU].
  * derivative = s(x)
  * inverse = log( exp(x) - 1 )
  * symmetry: z(x) - z(-x) = x
  * z(-x) is smooth max(0, -x)

Measure theory helps deal with funky sets like fractals or rational 
numbers. 
  * Sets with measure zero include a line in 2d space, a point, 
  all rational numbers in the real space. 
  * The union of sets with measure zero also has measure zero. 
  * A theorem that holds "almost everywhere" holds through all 
  space except for a set of measure zero

Deterministic functions of random variables induce volume changes, 
so the determinant of the Jacobian must renormalize pdf.
  * `px(x) = py( g(x) ) * det( dg(x) / dx )` for vector x

### Information theory

Likely events contain little information, rare events contain 
much information. Independent events linearly add information.

Self-information of event X is `I(x) = -log( P(x) )`
  * Has units of nats = info gained from event of prob 1/e
  * Shannons or bits are info units for base-2 log

Shannon entropy of pdf is E[I(x)] = expected information of 
event drawn from dist = lower bound of average bits needed to encode 
symbols from dist.
  * E.g., Bernoulli pdf with parameter p has upside-down parabola 
  style Shannon entropy graph.

Kullback-Leibler divergence = `D(P || Q) = E[log(P(x) / Q(x))] = 
E[log(P(x)) - log(Q(x))]`. Do expectation over P.
  * Gives extra info needed to send message containing symbols from 
  P using code designed to minimize message length for Q-messages.
  * Zero if P and Q are same. Always non-negative. Not a true 
  measure of distance because D(P || Q) != D(Q || P) generally.

Cross-entropy is sum of Shannon entropy of P and K-L divergence.

### Structured models

Chain rule gives P(a,b,c) = P(a | b,c) * P(b | c) * P(c). Can go 
one step further by assuming a and c are conditionally independent 
given b --> P(a,b,c) = P(a | b) * P(b | c) * P(c).
  * Here, c affects b affects a.
  * This exponentially cuts back on parameters 

Can represent above structure with directed or undirected graph
  * Directed: `p(x) = product of ( p(xi | A(xi)) )` where A is 
  parents of xi. 
  * E.g., p(a,b,c,d,e) = p(a) p(b|a) p(c|a,b) p(d|b) p(e|c) for 
  graph with a --> b, a --> c, b --> c, b --> d, c --> e
  * Undirected: `p(x) = 1/Z * product of ( ai( ci ) )`, where Z is 
  a normalizing constant, ai is a factor function, and ci is a 
  clique.
  * E.g., same graph above but undirected gives p(a,b,c,d,e) = 
  1/Z * a1(a,b,c) * a2(b,d) * a3(c,e).

## Numerical methods (Chapter 4)

Iterative algorithms like optimization or linear solution solvers 
can have numerical issues.

Underflow approximates numbers as zero. Overflow approximates 
numbers as + or - infinity.
  * Especially problematic with softmax due to exponentials.
  * Softmax can be fixed by changing x to x - (max component of x), 
  since shifts cause no change in function evaluation.

Poor conditioning -- function changes rapidly w.r.t. inputs.
  * Condition number for eigen-decomposable matrix A = lmax / lmin. 
  Gives sensitivity to error when inverting

Gradient descent follows negative of local gradient with some scaling 
factor called the learning rate. 
  * Don't forget to calculate gradient with appropriate 
  Jacobian-style factors!

Jacobian is matrix `Jij = d fi(x) / dxj`

Second derivative says if gradient step will cause as much improvement 
as originally thought. Negative = better minimization, positive = 
worse minimization.

Hessian is matrix `Hij = d2f / dxi dxj`. 
  * Basically the Jacobian of the gradient
  * Hessian is symmetric if second partial derivatives are continuous
  * Symmetric + real --> real eigenvalues and orthogonal eigenvectors 
  * Eigenvector with max/min eigenvalue gives direction with 
  max/min second derivative (curvature)
  * d^T H d calculates second derivative in direction d.

Expand `f(x) = f(x0) + (x - x0)^T g + 1/2 (x - x0)^T H (x - x0)`. 
After step of ag (down gradient), you have `f(x0) - a g^T g + 1/2 
a^2 g^T H g`
  * Optimal step size if g^T H g is positive (competition between 
  gradient and curvature) is `a = g^T g / ( g^T H g )`. Worse case, 
  a = 1 / lmax

Second derivative test: 
  * If all Hessian eigenvalues > 0, then min. 
  * If all Hessian eigenvalues < 0, then max. 
  * Mixed positive and negative shows saddle points. 
  * If all nonzero eigenvalues have same sign and some 
  eigenvalue = 0, then inconclusive.

Condition number of Hessian gives ratio of max and min second 
derivatives at point.
  * Poor condition number --> tough to pick learning rate and gradient 
  cannot safely assume constant curvature regardless of direction.

Newton's method incorporates Hessian: `x1 = x0 - inv(H) g`. This 
is the minimum of the 2nd-order Taylor expansion of f around x0.
  * Jumps straight to correct solution if f is purely quadratic
  * Can be attracted to saddle points.

Can achieve guarantees for Lipschitz continuous functions, for whom 
the function's rate of change is bound by a constant: `abs(f(x) - 
f(y)) <= c * norm(x - y)`
  * All continuously differentiable functions are Lipschitz continuous
  * Implies that small changes in input cause small changes in output.
  
Convex optimization requires Hessian is always positive semidefinite, 
so there are no saddle points and all local minima are global minima.
  * Typically not obeyed in DL applications

### Constrained optimization

Can do normal gradient descent, then project step onto allowed space. 
Could also test different learning rates on-the-fly and only pick 
step that lands in allowed space.

Can try to convert to special coordinates that obey constraint.
  * E.g., use polar coords and set r = 1 to keep unit L2 norm

Karush-Kuhn-Tucker approach introduces generalized Lagrangian.
  * Lagrangian = `L = f(x) + sum( li gi(x) ) + sum( kj hj(x) )` 
  where gi(x) are equality constraints and hj(x) are inequality 
  constraints. gi(x) and hj(x) are each balanced to equal zero.
  * Just apply unconstrained optimization to L.
  * Maximizing L for li and gj yields f(x) when constraints are
  satisfied and infinity when constraints aren't satisfied. Thus, 
  no infeasible point may be optimal.
  * Necessary but insufficient for optimal point: gradient of L = 0, 
  constraints on x and multipliers are satisfied, and inequality 
  constraints have "complementary slackness" (k dot h(x) = 0)
  * Complementary slackness means at least one inequality constraint 
  is active (point lies on boundary)

E.g., minimize squared L2 norm of (Ax - b) s.t. x^T x <= 1. First, 
compute `dL/dx = A^T A x - A^T b + 2lx = 0` --> `x = inv(A^T A + 2lI) 
A^T b`. Then compute `dL/dl = x^T x - 1` because `h1(x) = x^T x - 1`. 
Finally, take turns maximizing L w.r.t. l and minimizing L w.r.t. x.
  * If unconstrained, use inv(A) * b or Moore-Penrose pseudoinverse. 
  * Could also use Newton's method with a single step bc fct. is 
  purely quadratic

## Machine learning (Chapter 5)

Learning = performance measured by P on task T improves with 
experience E.

Tasks:
  * Classification learns function from input vector to output classes. 
  May output pmf over output classes instead.
  * Classification with missing inputs learns 2^n functions, each 
  corresponding to a subset of available variables mapped to the 
  categories. This is best done with a single joint pdf, from which 
  missing variables may be marginally integrated out.
  * Regression maps R^n to R
  * Transcription converts unstructured data to structured sequence. 
  E.g., address from image or sentence from audio.
  * Translation translates symbols between languages.
  * Structured output tasks output a vector with relationships between 
  elements. E.g., parsing sentence into grammar tree, labeling parts 
  of image
  * Anomaly detection finds outliers. E.g., credit card fraud
  * Synthesis and sampling creates new examples. E.g., audio from text
  * Imputation replaces missing values in dataset.
  * Denoising predicts clean version in R^n from corrupted version in 
  R^n. Generally, predicts conditional pdf given corrupted version
  * Density estimation learns full pdf. Allows imputation via 
  p(xi | x-i)

Performance can be measured by accuracy (fraction of correct outputs), 
error rate (fraction of incorrect outputs), or log-likelihood, e.g.
  * Often difficult to develop good metric. E.g., intractable to 
  compute full joint pdf.

Experience can be supervised or unsupervised. Unsupervised typically 
clusters data or learns pdf p(x) for synthesis/denoising. Supervised 
learns p(y | x).
  * Chain rule shows p(x) is decomposed as n p(y | x) problems.
  * Conditional pdf defn shows p(y | x) = p(x,y) / sum(p(x,yi))

Design matrix assumes all data points are described by same size 
vector (same # of features)

### Errors

Minimizing training error is simple optimization. Minimizing 
test/generalization error is ML.

The iid assumptions imply training and test data are essentially 
the same, so E[train error] = E[test error] for fixed parameter set.
  * However, parameter set is fit to training data. Thus, train 
  error < test error. 

Goal is small train error (avoid underfitting) and small gap 
between train and test errors (avoid overfitting)

Tune under/overfitting via capacity. Can change hypothesis space 
or representational capacity (set of basis functions) 

Vapnik-Chervonekis dimension is max m s.t. ML can binary-label m 
different points xi.

Nonparametric methods have arbitrarily high capacity.
  * E.g., neighbor regression assigns prediction = yi of 
  nearest known xi
  * Can wrap parametric method in algorithm that dynamically 
  changes number of parameters. E.g., polynomial basis for linear 
  regression.

Bayes error = random error from true p(x,y)
  * Finite capacity models have the train error tend towards level 
  >= Bayes error as number of training samples increases.
  * Optimal capacity model has test error tend towards Bayes error 
  as number of training samples increases.

Optimal capacity should plateau after certain number of training samples.

No Free Lunch -- all classification algorithms, when averaged over 
all possible pdfs, yield same test error.
  * Luckily we only care about subset of possible pdfs
  * Lesson is to create ML for specific task, not all possible tasks.

Implement regularizer with parameter that punishes model complexity. 
E.g., a * b^T b punishes L2-norm of parameter vector for linear reg.
  * Regularization reduces test error but not train error

Validation set tunes hyperparameters like number of basis fcts or 
regularization constant.
  * All parameters controlling capacity must be hyperparameters. 
  Otherwise, train set will force highest capacity.
  * Cross-validation uses all data for train and validation. E.g., 
  k-fold cross-validation trains on all but i'th set, then tests 
  i'th set. Repeat for each of k partitions and report avg error.

### Estimation

Point estimation approximates true parameter with function of 
data ("statistic"). Function estimation appoximates true 
function y = f(x) + e, which is the same as point estimation but 
in function space.

Estimator bias = `bias( pm ) - E[pm] - p`, where pm is estimated 
parameter and p is true parameter.
  * Sometimes, biased estimators are nicer than unbiased

Variance of estimator (square root of which is "standard error") 
gives estimate variance with resampling data.
  * SE( sample mean ) = sigma / sqrt(m). There is no unbiased 
  estimator for sigma, but sqrt( unbiased var estimator ) comes 
  close.

Can construct 95% confidence interval for mean error using 
sample mean error +/- 2 * SE(sample mean error).

Choose between high-bias and high-variance by minimizing cross-validation 
error, or minimizing mean squared error = `MSE = E[(bm - b)^2] = 
Bias[bm]^2 + Var[bm]`.
  * Bias decreases with capacity as exp(-x), variance increases 
  with capacity as x log x. Test error = MSE.

Ideally, estimator is consistent: bias tends to zero with increasing 
number of samples.

Max likelihood estimator is `argmax L(x, b) = prod(p(x,b))` or upon 
log-transforming `argmax sum( log( p(x,b) ) )` which is same as 
`argmax E_data[ log( p(x,b) ) ]`
  * Same as minimizing KL divergence between empirical dist and 
  your pdf. Interpreted as minimizing cross-entropy between dists.

Conditional MLE is useful for supervised learning: 
`argmax P(y | X, b)` or `argmax sum( log( p(yi | xi,b) ) )`
  * E.g., define p(y | x, b) as Normal with mu = f(x,b), var = s^2 
  (s provided by user). So we argmax w.r.t. b for `sum( log( 
  p(yi|xi,b) ) ) = -m log s - m/2 log(2pi) - sum( 1/2s^2 (yi - 
  fi(x,b))^2 )`. Same optimization as minimizing MSE!

Cramer-Rao lower bound: no consistent estimator has lower MSE 
(efficiency) than MLE. CRLB is lower bound on variance for 
unbiased estimator

Bayesian uses `p(b | x) = p(x | b) p(b) / p(x)` for estimation. 
New samples are given by `p(xi) = integral of ( p(xi | b) p(b | x) 
db )`, which incorporates uncertainty in b.

Bayesian methods generalize better for small datasets, but incur 
high computational cost for big datasets.

Bayesian linear reg.
  * Define likelihood p(y | x,b) as multivariate Normal with mu = 
  y - Xb and identity matrix covariance. 
  * Set prior p(b) is multivariate Normal with mu0 vector and S0 
  covariance matrix. 
  * Posterior is therefore multivariate Normal with `Sm = inv( X^T X + 
  inv(S0) )` and `mum = Sm ( X^T y + inv(S0) mu0 )`. 
  * Discard constant (non-b) factors during posterior derivation, then 
  use multivariate Normal normalizing factor `sqrt( 1/(2pi)^n det(Sm) )` 
  at the end.
  * Same result as frequentist linear reg., but with weight decay 
  penalty of a * w^T w, where `S0 = 1/a * I` with I = identity matrix

Maximum a posteriori estimator = `argmax p(b | x) = argmax log( p(x | 
b) ) + log(b)` gets single number for b instead of full pdf.
  * log(b) term from prior introduces `w^T w` term, just like in 
  MLE with weight decay.
  * Uses bias from prior to decrease variance compared to MLE

### Supervised methods

Goal is estimating p(y | x).

Linear reg. has p(y | x) = Normal with mean y - Xb and variance I.

Logistic regression has p(y | x) = s(Xb) where s is the sigmoid fct.
  * Squishes linear reg. output and gives interpretation of 
  probability of class 1 (vs. class 2)
  * No closed-form solution. Max log-likelihood instead.

Support vector machines predict class 1/2 based on positive/negative 
f(x) = x b.
  * Kernel trick: f(x) = x b = sum( bi x^T xi ) --> sum( bi k(x,xi) ). 
  k(x,xi) = phi(x) dot phi(xi).
  * Kernel trick is same as applying phi(x) to all inputs, but 
  significantly more computationally efficient (esp. for infinite-dim 
  kernels like exp!)
  * Gaussian kernel with variable = x - xi, mean = 0, cov = s^2 I 
  is common. AKA radial basis function. Acts as template matcher 
  that assigns label as weighted average of all known labels, weighted 
  by distance.

Kernel machines have evaluation cost linear in training set size. 
Can overcome by setting most bi = 0. Training examples corresponding 
to nonzero entries are called "support vectors".

k-nearest neighbors takes weighted average of y-values for k nearest 
neighbors.
  * Nonparametric and has no training step. 
  * Only well-defined if an average can be taken. 
  * High capacity enables high accuracy for big datasets, but poor 
  generalization for small datasets and high computational cost. 
  * Cannot discern relevant features.

Decision tree partitions input space using specialized algorithms 
  * Nonparametric if any size tree can be made. Regularization 
  creates a parameter.
  * Creates vertical and horizontal lines, so performs poorly for 
  categorical splits that fall diagonally (e.g., x1 < x2)
  * Each leaf requires >= 1 training example, so DT cannot learn 
  fct with more local maxima than number of training examples.

### Unsupervised methods

Simpler representation achieved via:
  * Lower dimensionality
  * Sparse representation where most entries are zero. Typically 
  requires increasing dimensionality
  * Independent representation with independent sources of variation

PCA finds linearly independent lower-dimensional representation
  * Covariance matrix = 1/(n-1) X^T X for mean-centered X
  * Recall from linear algebra section: SVD of X = U S V^T where 
  V's columns are right-singular vectors, which are eigenvectors of 
  X^T X. 
  * Cov = 1/(n-1) V S^2 V^T. So SVD on X is same as orthogonalizing 
  covariance matrix X^T X.
  * Principal components are X V = U S. They have diagonal covariance 
  themselves: (X V)^T (X V) = V^T (V S^2 V^T) V = S^2
  * PCA rotates input space (preserving orthogonality of basis) to 
  find principal axes of variance.

K-means provides sparse representation with 1-hot k-dimensional 
encoding
  * Initialize k centroids, assign train data to nearest centroid, 
  then update centroid poisiton to mean of train data's positions.
  * Can measure goodness-of-fit = avg. distance of point to cluster 
  centroid.
  * Difficult to interpret clusters or select appropriate number
  * E.g., Red cars, red trucks, gray cars, gray trucks. Cluster 
  by car/truck, red/gray, or 4 separately? 
  * Distributed (multi-hot) representation gives more flexibility 
  beyond picking one relevant attribute, and yields more fine-grained 
  distance metric compared to yes/no same cluster.

### Stochastic gradient descent

Cost function is generally sum over training data (e.g., negative 
conditional log-likelihood). Gradient descent is thus O(n). 

Minibatch 10 - 100 training data drawn uniformly, then calculate 
gradient descent `g = 1/m sum( d/db L(x,y,b) )` and update 
parameters `b --> b - a * g` where a is learning rate.

Nonlinear models originally used kernel trick, which constructs 
n x n matrix of pairwise kernels with O(n^2) cost. Minibatch 
stochastic gradient descent allows O(m) [constant] training times.

### ML process

Define dataset, cost function, optimization, and model

Cost function is typically regularization + expectation of negative 
log-likelihood under model with current parameters
  * Cost for PCA is expectation of norm of `x - w^T x w`,  which 
  minimizes reproduction error

Optimizers typically use gradient information, but k-means and 
decision trees have cost functions with large flat regions and need 
therefore special optimizers.

Generalization is hard in high-dimensional spaces.
  * Curse of dimensionality -- many configurations of variables.

Normally impose "implicit prior" of smoothness / local constancy.
  * k-nearest neighbors assigns same output to region nearest 
  a training point
  * Kernel methods interpolate using local kernel like RBF
  * Decision trees require at least n training data to create n 
  leaves and n partitions of input space.
  * Smoothness handicaps performance when true function changes 
  rapidly or exists in high-dimensional space. Requires n training 
  data to tune n parameters to create n regions.

Smoothness fails to recognize nonlocal patterns. E.g., chess board 
pattern would require 64 training points.

Impose different + stricter constraints to represent rapidly-changing 
high-dimensional function with small model that generalizes well. 
E.g., can describe 2^k regions with k examples.
  * Assume data is created by composition of factors

Manifold is lower-dim space embedded in higher-dim space. E.g., 
Squiggly line within 2D plane.
  * Manifold can have additional dimensionality at intersections. 
  E.g., Figure-8 is 1-D except for center, which is 2-D.
  * Natural representation is coordinates along manifold, not in 
  higher-dim space. E.g., We use street addresses, not (x,y) 
  coordinates.
  * Manifold learning assumes most of higher-dim space comprises 
  invalid inputs. Interesting variations only occur along directions 
  on small embedded manifold or on transitions between valid manifolds
  * Also assumes that examples are connected, and can be traversed 
  with transformations. E.g., dim/brighten image, rotate objects, 
  alter colors.
  * AI tasks like images, sound, and text obey manifold assumption. 
  Uniform noise never resembles realistic examples.

## Deep feedforward networks (Chapter 5)

Deep learning learns basis, rather than using generic basis (poor
generalization) or custom basis (domain-specific)

Need nonlinear functions within NN. Use affine transformations with nonlinear
activation functions
  * ReLU is easy to optimize with gradient-based methods and generalizes well
    * Generalizations are max(0,zi) + ai min(0,zi). Abs val has ai = -1 (good
      for images); leaky has ai = 0.01; parametric learns ai
  * Maxout groups zi into k groups and outputs max of given group. Learns the
    activation fct. Has catastrophic forgetting issue.
  * Saturation of sigmoid causes low gradients, which is bad for learning

Loss function is typically negative log-lik of p(y|x,b) (same as cross-entropy)
rather than SSE or SAE, since those have vanishing gradients for saturated units

Linear units used for Gaussian outputs; sigmoid for Bernoulli; softmax for
multinoulli

Deep networks require fewer parameters and nodes than shallow. Deep
architectures express useful priors and learn many small building blocks

Skip connections allow gradient to flow more directly from output to input

Backprop uses dynamic programming to store intermediate derivs in chain rule

## Linear factor models (Chapter 13)

Linear factor model generates x by adding noise to linear 
transformation of h
  * Sample h from product of ( p(hi) ), then generate `x = Wh + b + 
  noise`. Also, `h = W^T (x - mu)`
  * PCA has x = V h + b, b = mean of x, W is orthogonal matrix V = 
  (selected) right singular vectors of X.

Graph model looks like directed version of RBM.

Factor analysis (probabilistic PCA)
  * p(h) is Normal with mean 0 and identity covariance matrix. 
  * Observed variables are conditionally independent given h. 
  * Noise is from Normal dist with mean 0 and diagonal covariance 
  matrix. 
  * Latent variables capture dependencies between xi.
  * p(x) is therefore Normal with mean b and covariance W W^T + 
  diagonal noise matrix
  * Iterative expectation maximization estimates W and noise.
  * Probabilistic PCA becomes PCA when noise --> 0. E[h | x] = 
  projection of x - b onto column space of W.

PCA learns pancake-shaped ellipse manifold in higher-dimensional 
space. Ellipse is purely linear and orthogonal
  * Reconstruction square-error is sum of left-out variance 
  (eigenvalues lower than cutoff)

## Structured probabilistic models (Chapter 16)

Use graph to represent dependencies, like structured model chain 
rule simplifications.

Tasks include classification (simple, and doesn't require understanding 
of full input), density estimation (prob. of getting input), 
denoising (image cleaning, e.g.), imputation, or sampling

Storing (colors)^(pixels) domain with assigned probability to each 
point is infeasible due to: 
  * Memory
  * Statistical efficiency (overfitting due to need for many 
  parameters)
  * Runtime for marginal pdf or conditional pdf calculations
  * Runtime for sampling.
  * This method accounts for all variable-variable interactions, 
  which is unnecessary. Most interactions will be indirect.

### Directed graphs

Directed graph is typically a tree (DAG), wherein `p(x) = product ( 
p(xi | parents) )`, e.g. `p(x0,x1,x2) = p(x0) p(x1 | x0) p(x2 | x1)`

E.g., Model a relay race with x0, x1, and x2. 100 values each --> 
10^6 - 1 values total (- 1 since sum is 1). Directed graph has 99 + 
(99 * 100) + (99 * 100) --> 19,899 values total.

Generally, reduce (values)^n to (values)^m, where m << n.
 
Tree structure enables fast marginal/conditional pdf calculations

Can further simplify conditional pdf structure at each node if 
there's more info, like simple scaling/shifting. Convert 
(values)^(parents) - 1 to smaller table.

### Undirected graphs 

Undirected graphs are used for unclear causality
  * E.g., model disease transmission (A can infect B or vice versa)

Also called Markov random fields / Markov networks

Factor phi(c) for each clique c measure affinty of same state.
  * Cliques are fully-connected subgraphs.
  * Factors are represented as tables with (values)^(clique members) 
  values. Each value is an unnormalized probability of that combo.
  * Factors can also have parameters. Some function or parameter 
  choices can make partition function diverge. Depends on domain.

`p(x) = product ( phii(ci) )` is unnormalized. Allows for weighting 
stronger cliques.

Normalizing factor = `Z = integral of ( p(x) dx )` = partition 
function. Typically computationally intractable. See Chapter 18.
 
Can force `p(x) > 0` for all x by setting `p(x) = exp(-E(x))`
  * Can now used unconstrained optimization due to guaranteed p(x) > 0
  * Called energy-based model or Boltzmann machine. BMs originally 
  designed for binary variables (Ising!). BMs without latent 
  variables are called Markov random fields or log-linear models.
  * Product of clique factors cause sum of energy terms.
  * Typically work with free energy `F(x) = -log( sum( exp(-E(x,h)) ) )` 
  where h are the latent (conjugate) variables

Separation: paths with only unobserved = active, paths with only 
observed = inactive. Unobserved variables are separated if there is 
no active path between them.
  * Called d-separation for directed graphs 
  * Not separated = dependent (even indirectly). Separated = 
  independent.
  * E.g., a and b are wind speed meters. s separates with state = 
  hurricane or not. Typically, a and b are dependent. If hurricane, 
  then a and b are independent (hurricane state takes precedence)
  * Graph must capture possible independence, and can (extraneously) 
  show dependence when there is independence

Typically use directed for drawing samples, undirected for approximate 
inference.

Can always use fully-connected undirected graph or complete ordered 
tree to describe any pdf, but inefficiently.

Can convert directed and undirected graphs to one another with 
"moralization" and "triangulation" processes.

Factor graph notation specifies exact clique structure.

### Sampling

Ancestral sampling: sample parents, then kids, then kids' kids...
  * Only for directed graphs
  * Inefficient if we're given kids and have to sample parents. 
  Posterior pdfs aren't parameterized, so inferring is costly.

Undirected graph has dependency issues. Use Gibbs sampling (or MCMC) 
instead. Just need to condition on neighbors.

### Learning and inference

Many dependencies between observed variables v. Introduce latent 
variables h to absorb dependencies and simplify graph.
  * Field of structure learning seeks minimal graph, typically with 
  greedy search.

Latent variables provide simple fixed structure and alternative 
representation for observed variables.
  * Use E[h | v] or argmax p(h, v) to find h given v.

Inference = compute p(h | v) or E[h | v]. Typically hard for deep models. 
  * See Chapter 19

Deep learning typically uses many latent variables without specified 
network structure or interpretation. Nonlinearity is represented 
through indirect connections.
  * Distributed representation: one v connected to many h, and one h 
  connected to many v.
  * Distributed representation yields difficult inference / loopy 
  belief propagation. Use Gibbs sampling / variational inference 
  instead.
  * Use matrix to connect groups of latent variables (in different 
  layers, e.g.) for efficient training and inference.

### Restricted Boltzmann machine

Only undirected connections between h and v. No h-h or v-v.

Energy = `E(v, h) = -b^T v - c^T h - v^T W h`
  * E.g., v is [polarization, magnetization], h is [electric field, 
  magnetic field], W gives (cross-)energy between h and v, b gives 
  biases on observables, and c gives biases on latents.

Restricted structure yields `p(h | v) = product ( p(hi | v) )` and 
`p(v | h) = product ( p(vi | h) )` due to no h-h or v-v connections.

Binary RBM (like Ising) yields `p(hi = 1 | v) = s(v^T W:,i + ci)` 
and `p(hi = 0 | v) = 1 - p(hi = 1 | v)`, where s is sigmoid function. ``
  * Set up `p(hi=1 | v) = exp( -E(hi = 1) ) * 1/Z` and see that 
  -b^T v drops out, leaving sigmoid function.
  * Allows efficient block Gibbs sampling. Sample all h, then all v, 
  then sample all h, ...

Derivatives w.r.t. parameters are simple: e.g., `dE / dWij = -vi hj`

Use methods in Chapter 18 to train.

Unrestricted Boltzmann machine has `E(x) = -x^T U x - b^T x`, which 
is just Ising model for binary x. Connections are between (visible) 
variables.
  * Probability of xi = 1 is logistic regression of neighbors 
  * Train with max likelihood. 
  * Learning is local: updating weight between two units only 
  depends on pmodel(v) and pmodel(h|v) * pdata(v). Obeys Hebbian rule.
  * Separating out hidden variables yields `E(v,h) = -v^T R v - v^T W 
  h - h^T S h - b^T v - c^T h`

## Monte Carlo (Chapter 17)

Sampling approximates sums and integrals like sum ( f(x) p(x) ). 

Average of samples is unbiased since `E[s_p] = 1/n * 
sum( E[f(x)] ) = s`.

Variance of samples dies with n since `Var[s_p] = 1/n^2 * sum( 
Var[f(x)]) = Var[f(x)] / n`

Central limit theorem says that averages tend towards Normal dist.

Ideally, sample directly from p. Alternatively, use importance 
sampling. For most real problems, use MCMC.

### Importance sampling

Select q to minimize variance in `s_q = 1/n * sum( f * p / q )`, 
where `Var[s_q] = Var[f * p / q ] / n`. This occurs when `q = f * p / 
Z` where Z is a normalizing constant. That is, q has most mass where 
integrand f * p is big
  * In fact, perfect q has `Var[s_q] = 0`!

Approach suffers in high dimensions because simple choices for q can 
easily lead to regions with very low f * p / q (useless samples) 
or very high p / q * f (never sample important region). High dimensions 
lead to more extreme big or small numbers.

Useful for forcing sampling over difficult examples.

### MCMC

MCMC guarantees usually apply only if no state has zero probability. 
Not an issue for Boltzmann-style distributions.

Markov chain transition matrix is a stochastic matrix since each 
column represents a probability distribution.

Perron-Frobenius theorem: If there's a way to get from a to b in 
some time t, then the largest eigenvalue of the matrix is 1.

Repeated application of transition matrix t times has A^t = 
(V diag(l) inv(V))^t = V diag(l)^t inv(V). All lesser eigenvalues 
die to zero, leaving only single eigenvector (the stationary 
distribution).

Ignore burn-in period. Sample every n timesteps where n is 
autocorrelation time, since successive samples are highly correlated.

Gibbs sampler:

Pick variable and sample from its conditional pdf, given current 
values of all other variables.
  * May pick many variables (block sampling) if they're 
  conditionally independent, given all other variables. 
  E.g., all hidden units or all visible units in restricted 
  Boltzmann machine.

MCMC tends to get stuck in energy wells when sampling high-dimensional 
space. Big issue if high energy barriers between deep wells and only 
small subset of variables are updated at a time.
  * E.g., E(a, b) = -w * a * b, so P(a | b=1) = sigmoid(w). 
  Simulation rarely flips sign of a and b even though (1, 1) and 
  (-1, -1) should be equally likely.
  * Possible solution is simultaneously updating big groups of 
  dependent variables. But dependencies are complicated.
  * Models with latent variables want high p(h | x) entropy but 
  high mutual information between h and x. The latter happens 
  when h is sharply peaked, like with categorization problems.

E.g., MCMC works great for sampling independent normal dists. 
Worse for highly correlated multivariate normal bc chain is unlikely 
to leave starting point or correlation axis. Terrible for mixture of 
separated Gaussians bc chain can't jump.

Tempering helps, but still gets stuck around critical temperatures.

Encode x deeply in h s.t. h is uniform and unimodal, encouraging 
mixing. Minimizes reconstruction error because different examples 
are further separated in h-space. Accomplished by deepening RBMs 
or autoencoders.

## Partition function (Chapter 18)

Maximize log-likelihood to learn parameters b from data x using 
gradient ascent.

Set `p(x) = f(x,b) / Z(b)`, so `d/db log( p(x,b) ) = d/db log( f(x,b) 
) - d/db log( Z(b) )`.
  * First term is easy bc it's the unnormalized Gibbs energy term
  * First term is positive phase in which data pdf is sampled and 
  increases f(x,b).
  * Second term is a pain.
  * Second term is negative phase in which model pdf is sampled and 
  decreases f(x,b). 
  * Overall effect is moving model pdf to data pdf.

Gradient of second term can be wrangled into `E_x~p[ d/db log( f(x,b) )]`. 
This can be approximated with Monte Carlo!

Naive gradient ascent for parameter vector b: 
  * Sample minibatch from train set to get starter `g = 1/m sum( d/db 
  log( f(xi, b) ) )`
  * Do MCMC Gibbs sampling on train set to generate new samples given 
  current parameters b, starting from random x samples.
  * Calculate gradient = `g = g - 1/m sum( d/db log( f(xi, b ) )` 
  across final samples xi
  * Update `b = b + a * g` where a is learning rate

Can use improved MCMC method like parallel tempering instead!

Contrastive divergence initializes above Markov chain with sample 
data.
  * Incorporates (small) bias since it doesn't smash down rare regions 
  in train data that aren't rare in model.
  * Works poorly for deep models since latent variables aren't observed 

Stochastic max likelihood / persistent contrastic divergence 
initializes Markov chain at previous step's final state.
  * Reduces bias issue
  * Works much better than CD for deep models

Fast PCD replicates parameters into fast and slow set, where fast 
set has larger learning rate for gradient ascent. This pushes 
Markov chain into new territory. Final parameters = fast + slow.

Other techniques include pseudolikelihood estimation, score matching, 
ratio matching, noise-contrastive estimation (treat 2nd term as 
paramter to be learned), annealed importance sampling, and bridge 
sampling

## Approximate inference (Chapter 19)

Want to compute p(h | v) or E[h | v].

Probabilistic PCA and RBMs have tractable posteriors that lead to 
direct sampling via SVD or Gibbs sampling. Deeper networks beyond 
1 layer have intractable posteriors.

If log( p(v,b) ) difficult, get evidence lower bound / variational 
free energy instead: 
  * `L(v,b,q) = log( p(v,b) ) - D( q(h|v), p(h | v,b) ))` where D is 
  Kullback-Leibler divergence and q is an arbitrary pdf over h.
  * `L = -E_h~q[ log( q(h | v) - log( p(h,v,b) ) ) ]` after algebra.
  * Therefore inference finds q to closest match p

Expectation maximization alternates until convergence:
  * Set q(hi | v) = p( hi | v, b0 )
  * Maximize sum ( L(vi, b, q) ) w.r.t. b

Maximum a posteriori finds best h, not whole p(h | v).
  * Set q ~ Dirac delta dist. around points mu. Then simply apply 
  gradient ascent on log( p(h,v) ) by updating h points.

E.g., sparse coding
  * Regularization: `p(hi) = l/2 exp(-l abs(hi))` 
  * p(x | h) is Normal with mean = W h + b and covariance s^2 I, 
  which is a linear transformation of the latent variables with noise. 
  * Latent variables are in one big clique due to directed graph 
  structure. Gaussian model would allow interactions via covariance 
  matrix, but sparse prior imposes non-Gaussian interactions. Thus, 
  p(h | v) is intractable.
  * Minimize cost = `J(H,W) = sum( abs(Hij) ) + sum( ( V - H W^T )^2 )`
  * Minimization w.r.t. W is linear reg., while min w.r.t. H needs 
  special algorithms like feature-sign search. Can also impose 
  regularization on W to prevent small H with huge W.

Mean field approach imposes `q(h | v) = product of ( q(hi | v) )` 
so that it's easy to compute `E_q[ log( p(h,v) ) ]`.
  * Ising MFT converts `E = sum over i,j ( J si sj )` to `E = 
  sum over i ( J m si )`, which is `p(x) = 1/Z product of ( exp( -J 
  m si ) )`. Removes cross-talk between si and sj.
  * Can impose different graphical structure, which is called 
  structured variational inference.

Use traditional optimization for discrete latent variables, or 
calculus of variations for continuous latent variables.
  * E.g., binary sparse hi --> `p(hi = 1) = s(bi)` where bi is a 
  bias parameter, p(v | h) is Normal with mu = W h and covariance 
  matrix is diag(s) where s is a vector of parameters.
  * `d/dbi log( p(v) ) = ... = E_h~p(h|v)[ d/dbi log( p(h) )  ]`
  * Set q(hi | v) as Bernoulli with parameter vector h.
  * Apply algebra to L(v,b,q) to get long but tractable equation 
  involving bi, hi, si, vi, and Wij.
  * Maximizing L with gradient descent requires storing h for each 
  v. Iterate over fixed point equations instead: `dL/dhi = 0`
  * Fixed point eqns yield `hi = s( bi v^T S W:,i - 1/2 W:,i^T S 
  W:,i - sum over j != i ( W:,j^T S W:,i hj ) )`. This is same as 
  recurrent neural network!
  * Can also interpret as iterative autoencoder trying to encode 
  residual error in v given code of other units.

Calculus of variations / Euler-Lagrange eqn is used to show that 
pdf with max entropy for given mean, std dev, and normalization to 1 
is the Normal dist.

Mean field fixed point updates given by normalizing `q(hi | v) = exp( 
E_h-i~q(h-i|v)[ log( p(v,h) ) ] )`
