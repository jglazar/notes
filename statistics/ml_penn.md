# Machine Learning -- UPenn CIS 520

## Introduction (Chapter 1)

Generative unsupervised methods like Guassian Mixtures model `P(X)`, 
generative methods like Naive Bayes model `P(X,Y)`, discriminative 
methods like Logistic Regression model `P(Y|X)`.

Regularization is like MLE plus prior, or MAP.

## Local learning

Requires defining a distance metric.
  * Norms have scaling, triangle inequality, and L(0) = 0
  * Ln norm is sum( abs(xi)^n )^(1/n)
  * Distance metric has non-negativity, zero if x=y, symmetry, and 
  triangle inequality. 
  * All norms of difference vectors are distance metrics.
  * L2 is circular, L1 is diamond, Linf is square.

K-nearest neighbors is nonparametric. 
  * Expressive and flexible, but can overfit.
  * Can achieve zero bias with enough data.
  * Increase K to trade variance for bias.

Local learning is expensive to store, performs poorly in high dimensions 
because all data is far away, and is sensitive to irrelevant features.
  * E.g., 100-dim binary space with random inputs has about 50 matches, 
  so each point is about sqrt(50) away from one another.

## Decision trees

See my walkthrough on Google Colab

Information gain = `IG(X) = H(Y) - H(Y|X)`, and `H(Y|X) = sum over x ( 
P(x) H(Y|X=x) ) = -sum over x,y ( P(X=x,Y=y) log( P(Y=y|X=x) ) )`

Lower in tree --> few data points surviving --> likely fitting to noise
  * Can limit tree depth / number of leaves, or employ pruning

Much faster than kNN for large datasets. O(log n) vs O(p n^2). Also 
more robust against noise.

Rescaling doesn't affect predictions

## MLE and MAP

MLE is same as maximizing log-likelihood. 

Bayesian conjugate prior causes nice posterior, whose MAP looks like 
adding regularization
  * MAP gets mode, but mean and variance could be useful too.

E.g., coin flips
  * MLE = h / total
  * MAP = (h + a - 1) / (total + a + b - 2), where a and b are 
  Beta prior parameters.

E.g., Gaussian
  * MLE mean = 1/n sum(xi), variance = 1/n sum( xi - mean )^2 [biased!]
  * Bayesian conjugate prior for mean is Gaussian, for variance is 
  Inverse Gamma.
  * MAP for mean with prior is sum of data weighted by data's precision with 
  prior mean weighted by prior's precision. Precision = inv. variance.
  * MAP --> MLE when sample size increases or prior precision decreases.

## Linear Regression

Assume y = xi w + N(0, var). 

MLE maximizes `-n log( sqrt(2 pi var) ) - 1/(2 var) r^T r`, where `r` 
is residual vector `y - Xw`
  * Same as minimizing square error!

`d/dw 1/2 r^T r = -X^T r = 0 --> w = inv(X^T X) X^T y`
  * `X^T X` isn't invertible if features linearly dependent.

Interpretation is projecting y onto column space of X, which finds the 
closest coefficient vector to y.

Bayesian way takes Gaussian prior with zero mean and constant variance 
for independent coefficients wi. 
  * Use cross-validation to get variance.
  * MAP minimizes `1/(2 var) r^T r + 1/(2 var_prior) w^T w`
  * `w = inv( X^T X + var/var_prior I ) X^T y`
  * Same as MLE plus regularization!
  * Also called ridge regression due to quadratic weights.

Rescaling doesn't affect predictions, except for regularized regression.

Linear regression with varying noise parameters `var_i` does weighted 
regression, with weight proportional to point's precision.

Nonlinear regression like assuming `y ~ N( sqrt(w + xi), var )` has 
no nice value for w. Need to use:
  * Line search, simulated annealing, gradient descent, conjugate 
  gradients, Levenberg Marquandt, Newton's method, Expectation maximization.

## Overfitting and Regularization

Test set error is unbiased estimate of true error = `E[ h(x) != y ]`

Validation -- train 10 models with different complexity on the 
same training set, then pick best performer on validation set.

LOOCV is good for small datasets

K-fold CV is good for large datasets. Typically pick K = 10

Can try nested CV for extensive hyperparameter tuning

Linear regression has regularization on: 
  * L2 norm = Gaussian prior = ridge regression. Shrink all weights by 
  constant factor
  * L1 norm = Laplace prior = LASSO / LARS. Shift all weights by constant 
  amount.
  * L0 norm = spike and slab = stepwise regression (not convex). Zero-out 
  some weights and leave others unchanged.
  L0 regularization is scale invariant!
  * L2 + L1 is called elastic net

## Bias and Variance

Bias = E[ phat - p ] = E[phat] - E[p]. Variance = E[(phat - p)^2]. 
Expectation is taken over training datasets D.

Expected error = E[(h - y)^2] = E[(h - hbar)^2] + E[(hbar - ybar)^2] + 
E[(ybar - y)^2] = variance + bias^2 + noise.
  * Decrease variance with simpler model or more data
  * Decrease bias with more complex model
  * Cannot decrease noise

Adding regularization induces bias, but reduces variance.
  * More data --> less regularization is optimal.

## Logistic Regresson

Logistic regression has `h = 1/(1 + exp(-w^T x))`, `P(y | x,w) = h^y 
(1-h)^(1-y)` and thus derivative of log-likelihood is `dl/dwj = sum ( 
yi - hi) xj`. This yields gradient ascent rule.
  * Gradient also given by `sum ( yi xi ( 1 - P(yi | xi,w) ) )`
  * Prediction h = sign of w^T x
  * Use gradient descent or AdaGrad to optimize.
  * Adding Gaussian prior appends `-1/(2 var_prior) * w^T w` to cost 
  function.

Linear decision boundary found with `P(y=1 | x,w) = P(y=-1 | x,w) --> 
w^T x = 0`

For k classes, need k-1 sets of weights. Also called softmax function. 
MAP uses k sets of weights to avoid unintended bias

Use logistic reg over Naive Bayes if more data than parameters. Logistic 
reg is special case of Naive Bayes with shared variances for Gaussian 
features.

## General linear regression

Prediction = `f( sum ( wi xi ) )` (in general) = `sum( wi fi(x) )` (for 
linear basis models)

Radial basis functions increase or decrease dimensionality based on 
number of basis vectors
  * Use centers of k-means clusters as kernel centers.
  * New features are RBF distances to each center
  * Tune RBF width via CV

## Gradient descent

Optimal step size is usually 1/sqrt(iteration number).

Adaptive step size increases step size by 10% each time, but cuts by 
half if error increases

Stochastic gradient descent updates after each data point

Mini-batch updates every k points

Adagrad defines per-feature learning rates. Rare features get higher 
learning rates.

## Kullback-Leibler Divergence

`KL(P || Q) = -sum ( Pi log(Qi / Pi) ) = H(P,Q) - H(P)` where H(X,Y) is 
cross-entropy between distributions X and Y, and H(X) is entropy 
of distribution X.

Measures how well Q approximates true distribution P.

Non-symmetric and doesn't satisfy triangle inequality, but is non-negative.

KL divergence is good loss function for classification over k classes. 
Softmax (from logistic reg or NN) gives distribution over k classes, which 
one can compare to empirical dist.

`KL(P(y|x,x') || P(y|x) )` measures info gain from query `x'`. Want to 
maximize KL divergence in this case.

## Boosting

Bagging doesn't work on linear regressors, since that results in a 
new linear regressor. Does work for decision trees and NNs.

Boosting reweights data at each iteration.

Final prediction is `sign( sum( ai hi ) )` over weak learners i

AdaBoost updates dataset with `1/Z Di exp( -a yi hi )`, which reweights 
each data point's weight`Di` with an exponential term that emphasizes 
incorrect predictions. `Z = sum( Di exp(a yi hi) )`
  * Set iterations with CV
  * `a` is set dynamically with each iteration. `a = 1/2 log( (1-error)/error )`
  * Same as log-odds of correctness, which is always < 1/2 (could always 
  flip prediction if consistently wrong).

AdaBoost has exponentially decreasing training error.

Boosting minimizes `exp(-yi fi)` whereas logistic reg minimizes `log( 1 + 
exp(-yi fi) )`, where `fi = sum(ai hi)` across weak learners `hi` with 
weights `ai`. Basically boosting is like logistic reg. with functions 
rather than features.

## Support Vector Machines

Minimize hinge loss rather than `exp(-yi fi)` or `log( 1 + exp(-yi fi) )`
  * Still convex so optimization is easy
  * Slowly growing below zero -- milder misclassification penalty
  * Zero after 1 -- no boost for increased confidence
  * Gradient doesn't work due to hinge at zero.

Finds maximum margin separating hyperplane. This uses KKT optimization.

Binary classes: minimize `1/2 w^T w` s.t. `yi (w^T x + b) >= 1` for all i
  * Lagrangian: `L = 1/2 w^T w + sum( li ( 1 - yi(w^T xi + b) ) )`
  * dL/db = 0 --> sum( li yi ) = 0, dL/dw = 0 --> w = sum( li yi xi )
  * Plugging w back in: `sum(li) - 1/2 sum over i,j ( li lj yi yk xi^T xj )` 
  to maximize with sum(li yi) = 0 
  * This converts quadratic objective and linear inequality constraints 
  to quadratic objective and one linear equality constraint.
  * `li = 0` for xi away from hyperplane.

Only the points closest to boundary define the hyperplane. These are called 
support vectors.
  * Storing only the support vectors is a huge boon compared to storing 
  all examples. Only need to keep li != 0.

Kernel trick -- replace `xi^T xj` with `k(xi, xj) = f(xi)^T f(xj)`

Introduce slack variables such that no li gets set to infinity when 
one point cannot satisfy conditions.
  * `minimize 1/2 w^T w + C sum( si )` s.t. `yi(w^T xi + b) >= 1 + si`
  * `si = max(0, 1 - yi(w^T xi + b))` -- hinge function.
  * Regularization penalties above can be generalized to any norm.

## Kernels

Kernels map between primal space X^T X (features) and dual space X X^T 
(observations).
  * pred = w^T x, `w = inv(X^T X + cI) X^T y`
  * pred = x^T X^T l, `l = inv(X X^T + cI) y`. l vector gives relative 
  weight of each yi, like intelligent nearest-neighbors. Also helps balance 
  clusters in OLS. Huge storage boon because most li = 0.
  * Subbing `X X^T --> K(xi, xj)` yields kernel ridge regression.

MAP estimate for linear reg model with Gaussian prior is `w = var_prior/var 
sum( (yi - w^T xi)xi )` after setting derivative to zero (iterative 
formula to be used with gradient descent). 
  * Can be interpreted as `w = X^T l` where `li = yi - w^T xi` is a vector 
  that weights each observation by its residual. 
  * This maps the weights to a linear combination of the data.

MAP estimate for logistic reg model with Gaussian prior is similar: 
`w = var_prior sum( yi xi (1 - P(yi | xi,w)) ) = X^T l`.

Subbing `w = X^T l` in objective function (log-likelihood + log-prior) 
and defining `X X^T = K` gives everything in terms of y, K, and dual 
weights l. 
  * K is Gram / Kernel matrix is `Kij = xi^T xj`
  * MAP for l gives `l = inv(K + var/var_prior I) y`

For new data, `y = x^T w = x^T X^T l_map` and change `X x = k(x) --> 
x^T X^T = k(x)^T`
  * Prediction only involves linear combination of training data and 
  new data.

Kernel has interpretation of inner product of two basis-expanded 
data points. For p-polynomial kernels, the fully expanded version has 
O(m^p) terms whereas computing the inner product and exponentating 
only has O(m) terms.

Kernels express similarity between data points (opposite of distance 
metric). K must be symmetric and positive semi-definite. K cannot have 
negative determinant (bc det = product of eigenvalues).

`k(x, x') = x^T x'` can be scaled, linearly combined, multiplied, 
made arguments of polynomials, bookended by `f(x) k(x,x') f(x')`, 
exponentiated, and expressed as `x^T A x'`

Kernels can be defined for more abstract objects like images or sets

## Online learning

OLS least mean squares with stochastic gradient descent converges 
with rate proportional to ratio of min / max X^T X eigenvalues.
  * Converges if learning rate must be less than max eigenvalue of X^T X

Perceptrons -- step function( w^T f(x) ) where f(x) is basis
  * Converges if linearly separable
  * Number of mistakes < square L2 norm of biggest x / margin ( = yi w^T xi )
  * Use average of intermediate perceptrons if not linearly separable
  * Passive-aggressive: maximize hinge loss, use margin-infused relaxed 
  algorithm

## Neural Networks

Loss functions include L2, L1, L0 norms of (y - ypred), log-likelihood, 
hinge, exponential, cross-entropy/KL divergence, softmax.

Prediction functions include logistic function and tanh (slow to train), 
or ReLU (fast to train). 

NNs are semi-parametric, have flexible model form. Useful for 
big data. Embeds representations at many levels of abstraction.

Supervised NN generalizes logistic regression. Unsupervised NN generalizes 
PCA. Also semi-supervised, adversarial, and reinforcement.

Each node performs logistic regression. Stack nodes to create NN. 
Connections have parameters.
  * Convolutional layers convolve input with bank of filters, then 
  applies pointwise non-linearity.
  * Fully connected layer applies linear filters to input, then applies 
  pointwise non-linearity.
  * Locally receptive fields connect only nearby neurons.

Pooling provides translational invariance and reduces computational 
complexity. E.g., max pooling takes max of block and coarse-grains.

Lots of parameters need lots of data. Use invariances!
  * Bake invariance into model. E.g., use same feature detectors
  * Augment data. E.g., images can be mirrored or cropped to make new ones.
  * Bake invariance into loss fct. E.g., avoid language repetition. 

Train with mini-batch gradient descent. Use backpropagation.
  * Dropout randomly removes fraction of nodes, usually 1/2. This helps 
  escape local minima. Shrink all weights by above fraction for final 
  network.
  * Momentum learning uses gradient descent plus momentum of 
  previous weight change. 
  * Learning rate adaptation. E.g., Adagrad increases learning rate 
  for sparse parameters.
  * Use feature scaling for hidden layer outputs and for each minibatch.

Transfer learning trains on one dataset to find basis f(x), then feeds 
into final NN to predict y. Can reuse first basis-finding NN parameters 
on new problem.

Interpretation: display pattern of hidden unit activations and feed 
into linear predictor, show input which maximizes a node's output, show 
error effects of occluding parts of images.

## Singular Value Decomposition

A = U L V^T, where U's columns are eigenvectors of A A^T and V's columns 
are eigenvectors of A^T A. A is n x p, U is n x n, L is n x p, V^T is p x p. 
U and V are each orthonormal.

Matrix can be decomposed into weighted sum of singular vectors.
  * Often take thin SVD with U is n x k, L is k x k, V^T is k x p

sqrt( sum of squares of singular values ) equals Frobenius norm.

SVD gives pseudoinverse (U inv(L) V^T)^T = V inv(L) U^T, assuming L is 
invertible. Use thin SVD to make invertible.

Randomized (fast) SVD: A is n x p, hidden state dimension is k, extra 
l singular vectors
  1. Generate (k + l) x n random matrix O
  2. Get SVD of O A = U1 D1 V1^T and keep top k+l components of V1
  3. Get SVD of A V1 = U2 D2 V2^T and keep top k+l components of U2
  4. Get SVD of U2^T A = U3 D3 V3^T and keep top k components of V3
  5. Get SVD of A V3 = U4 D4 V4^T and keep top k components of U4
  6. Output U4 and V3^T 

Fast SVD generalizes power method for square matrices: represent 
A^4 x = sum ( zi li^4 vi ) where zi = vi^T x, using A vi = li vi.

## Principal Components Analysis

Linearly project data onto lower subspace, preserving as much variation 
as possible.

Reconstruction error is sum of squares of projection coefficients 
corresponding to discarded eigenvectors.
  * Projection coefficients are called scores. The eigenvectors 
  are called loadings (since they're represented in original coordinates)
  * Reconstruction error is also Frobenius norm of X - Z V^T, where 
  Z is n x k score matrix and V is m x k loadings matrix.

Reconstruction error = n * sum ( quadratic form ui^T S ui ) where S is 
covariance matrix and sum runs over discarded basis vectors.
  * Minimum reconstruction error occurs when ui are eigenvectors of S.
  * Lagrangian = u^T S u - l ( u^T u - 1 ) --> S u = l u, so u is 
  eigenvector.
  * In this case, error = n * sum( li )

Minimizing reconstruction error is same as maximizing variance, since 
Var = n * sum ( quadratic form ui^T S ui ) where sum runs over included 
basis vectors.
  * So Var + Error = n * sum( li ) = n * trace( S ).

Just need top k eigenvalues and their eigenvectors -- use SVD.
  * Construct SVD of (X - Xmean) then take top k rows of V^T with 
  largest singular values.
  * Forming and getting eigenvectors from X^T X is numerically unstable. 
  SVD is stable and quick via randomized (fast) SVD
  * X = U D V^T = Z V^T. Or, Z = U D = X V

Alternative interpretation -- low-dimensional Gaussian latent variable z 
has likelihood N( W z + mu, s^2 I ). MLE on W and mu with s tending to 
zero yields W as eigenvectors of data's covariance matrix.

Random projections method is fast: Form random m x k matrix R using 
std. Normal dist for each entry. Normalize columns. Project X R.

Can perform PCA without mean-centering (e.g., if data matrix is sparse) 
then remove top eigenvector (which corresponds to mean). This works if 
variance is significantly smaller than mean.

Add L1 norm penalties to Z and V matrices to regularize (sparse PCA). 
This means basis is no longer eigenvectors.
  * Solve using alternating gradient descent.

Do OLS regression using Z instead of X to get y = W z. W = inv(Z^T Z) Z^T y.
  * New z = V^T x, then plug in to get prediction for y
  * Useful for semi-supervised cases when there are many x with unknown 
  y. Do PCA on whole X matrix and fit to y = W z. Then apply to unknown x. 

Non-negative matrix factorization is similar to PCA with requirement 
of purely positive entries.

## Autoencoders

Inverse generally doesn't exist and is replaced with pseudoinverse.

Latent dimension should be less than data dimension.

Penalities for regularization can be added. E.g., encourage orthogonality 
or independence.

PCA: Xpred = Z V^T, Z = X V are embeddings and V^T are loadings. V^T and 
V are pseudoinverses.

ICA: Don't force orthogonality. Xpred = S pinv(W), S = X W. Minimize 
KL divergence / mutual information between full pdf and product of sources 
p(si).
  * Typically, first "whiten" X via multiplying by sqrt( X^T X )
  * Many ways to quantify independence beyond KL divergence

Denoising autoencoders: Embed x with noise to lower-dim x which 
hopefully removed noise. Learn embedder and de-embedder NNs. Noise is 
typically blacked-out pixels or masked-out words.

Variational autoencoder: Same as above, but don't add noise to input and 
instead add bottleneck.
  * Minimize reconstruction error, maximize component independence (like 
  mixture model)

Examples concentrate on low-dimensional manifold with limited valid 
directions in which changes can be made.

Unsupervised NNs are typically trained recursively, learn overcomplete 
basis, and learn non-linear manifold.

## Model Evaluation

Precision = P(true | predicted true) = TP / (TP + FP)

Recall / Sensitivity = P(predicted true | true) = TP / (TP + FN)

Specificity = P(predicted false | false) = TN / (TN + FP)

F1 = 2 * precision * recall / (precision + recall)

Build ROC curve given outputted class probabilities. Just need to sweep 
the true/false threshold to generate curve now.

Training error << test error --> overfitting

Training error and test error high --> underfitting

Show items at cluster center and inputs which maximize a certain output / 
node activation

Explore method-specific and method-agnostic feature importances.
  * Check regression coefficients / significance
  * Check accuracy loss when leaving out variable / pegging to mean value
  * Use permutation feature importance.

Find correlations between features. Check Pearson and Spearman

Look for outliers and clusters

Check for obeying symmetry, like translational/scale invariance

Add variable for missing feature, or use imputation for truly random missing 
data. Can make "missing" its own category type for categorical features.

## Clustering 

New error metric is needed because task is unsupervised -- there are no 
labels to compare against.

K-means: initialize k cluster centroids then repeat: assign data to 
nearest centroid, update centroid position to mean of cluster.
  * Check kmeans++ for better initialization method.
  * Useful for compressing data
  * Minimizes distortion = sum of distances to centroids = sum over i and 
  k ( `r_ik * ( centroid_k - x_i )^2`  ) where i is data and k is cluster, 
  rik gives 1/0 membership
  * Greedy algorithm runs faster than NP-hard problem. Uses alternating 
  gradient descent.
  * PCA can help lower dimension to 10-20. Keep k around 5-10.
  * Can be kernalized, setting centroids in feature space. Efficient 
  method never explicitly stores centroids.

K-means is special case of clustering with mixture of independent Gaussians 
with equal variances.
  * Basically, k-means assumes spherical clusters with shared size.

Gaussian mixture: `p(x) = sum( p_k Normal(mu_k, S_k) )`, where pk is the 
probability of being in cluster k. 
  * Full Sk has k m^2 / 2 parameters
  * Shared Sk has m^2 / 2 parameters
  * Diagonal Sk (Naive Bayes) has k m parameters (most common pick) 
  * Shared diagonal Sk has m parameters
  * Spherical Sk = sk I has k parameters
  * Shared spherical (k means) Sk = s I has 1 parameter
  * Can force pk = 1/k or allow arbitrary weights

Expectation maximization algorithm iteratively optimizes marginal 
likelihood of data (with latent variables summed out)
  * Estimate latent variables given model, then estimate model given 
  latent variables. 
  * E.g., calculate cluster assignment probabilities for each cluster 
  for each point, then estimate new cluster mean as weighted sum of all 
  data points' positions (weight is probability of assignment) AND pk is 
  the average assignment probability AND covariance matrix is covariance 
  of each point weighted by probability of assignment.
  * Uses Jensen's inequality to show that lower bound on log-likelihood 
  is KL divergence between true latent pdf given data and estimated latent 
  pdf given data.

Can use EM to impute data -- set missing data to average, then recalculate 
average, then set missing data to average of that set, then ...
  * Extend by estimating covariance between columns
  * Can also do regression on all other columns to predict missing 
  values, then train regression model, then ...
  * Imputation assumes that missing data is pulled from same dist as 
  existing data.

## Naive Bayes

Decompose P(x,y) = P(y) P(x|y) then approximate P(x|y) ~= product ( P(xi|y) )

Use MAP with appropriate prior instead of MLE to avoid zero probabilities.
  * E.g., add one count to each word, then add number of words to each 
  class count (Laplace smoothing). Jeffrey's prior adds 0.5 to each word and 
  half of the number of words to the class count.

Ignore order and consider counts of words to perform Naive Bayes on documents, 
using multinomial distribution as likelihood (bag of words).
  * Assumes no information in unobserved words

Latent Dirichlet Allocation picks topic with Dirichlet dist., then 
for each word picks topic and word with multinomial dists. Use 
variational inference for E step in EM optimization, or Gibbs sampling.
  * Requires fewer topics than Naive Bayes
  * Each document is mixture over topics, and each topic looks like Naive 
  Bayes model.

## Bayes Nets

Joint distribution has 2^m - 1 parameters in general. Naive Bayes simplifies 
to m parameters. General net with binary nodes has 2^p parameters per node, 
where p is the number of parents

Naive Bayes corresponds to network with one base node (result) and m 
child nodes, with directed edges from base to child.

Easiest case is specifying conditional pdfs at each node, given parent 
node values.

Use local Markov assumption to decompose overall joint pdf 

Be aware of active trails and directed separation to estimate parameters.
  * Variables connected by active trails aren't conditionally independent.
  * Directed separation if no active trail.

Stochastic gradient descent or annealing optimizes parameters. Can also 
randomly change network than accept/reject based on loss fct according to 
MCMC.

Do EM if some variables are unobservable.

HMM is dynamical Bayes Net. Assume each part of sequence is only dependent 
on previous part.
  * Useful for speech recognition.
  * 3 basic problems: evaluate probability of observed sequence, decode 
  hidden states behind observed sequence, learn parameters to maximize 
  P(sequence | params). Solve using EM.
  * Nonlinear HMM is modeled with dynamical recurrent NNs (like LSTM)

## Reinforcement Learning

Learn a policy maximizing long-term reward. Useful for playing games.

Never sees results of untaken action, gets told what best action was, and 
doesn't see consequences immediately.

Model-based methods include Markov decision processes. Model-free methods 
learn expected value of state given policy, expected value of state and 
action, and optimal policy.

* Model-based, has response to all possible actions, search to end: exhaustive 
search. 
* Model-based, has response to all possible actions, search one step: 
dynamic programming. 
* Model-free, has response to one action, search to end: Monte Carlo. 
* Model-free, has response to one action, search one step ahead: temporal 
difference learning.

Bellman's equation gets recurrence relation for value in MDPs.

Monte Carlo is high variance, low bias, insensitive to initial Q values ( 
expected values of each state and action). 
Q-learning (temporal differences) has low variance, high bias, can 
do online learning, and converges faster than MC.

Deep Q-learning represents Q as NN.

## AutoML

Learns best hyperparameters for ensemble of sklearn models. Can also 
automate NN architecture. 
  * Uses Combined Algorithm Selection and Hyperparameter optimization (CASH)

Use random forest to predict performance from hyperparameter. Discard values 
that perform poorly on 1st fold in 10-fold CV.

Use emsemble of best classifiers. Iteratively add model minimizing validation 
loss.

Performs as good as best humans, and less likely to overfit.

Do nested CV to really avoid overfitting: for each fold, do 10-fold CV 
on kept 90% to find best method, then observe performance on remaining 
10%.

Active learning picks most uncertain point as next point to investigate. 
  * Uncertainty measured as confidence, entropy, proximity to SVM margin.
  * Similar to decision trees, want to maximize KL divergence between 
  posterior and prior (most info gain).

Minimize variance of weight parameters. Can minimize trace, det, or max 
eigenvalue of inv(X^T X) over training data.

## Explanation

LIME does locally-weighted regression, which has simple interpretation of 
linear coefficients.

Interventional / marginal changes one feature with others fixed. Conditional 
changes other features to preserve correlations.

Model-based explores model, model-agnostic explores data space.

Local checks feature importance for one example, global takes average 
over all examples.

Shapley values average over coalitions (subsets of features) the 
change in prediction accuracy resulting from replacing removed 
features with baseline values.
  * Feature contributions add to difference of prediction and 
  average
  * Obey linear additivity
  * Features with no effects have zero Shapley value
  * Features with identical effects have identical Shapley values

Causality is difficult to capture in data (corrlations are easy). Bayes 
Nets model causality.
