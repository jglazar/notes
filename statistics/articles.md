# Articles

## Wikipedia - Covariance

Cov[X,Y] = E[(X - E[X])(Y - E[Y])] = E[XY] - E[X]E[Y]
  * Latter form can have catastrophic cancellation
  * Discrete form, pi equal: 1/n^2 sumi(sumj(1/2 (xi - xj) (yi - yj)))

Rules
  * Cov[X,a] = 0
  * Cov[X,X] = Var[X]
  * Cov[X,Y] = Cov[Y,X]
  * Cov[aX,bY] = ab Cov[X,Y]
  * Cov[X+a,Y+b] = Cov[X,Y]
  * Cov[aX+bY,cW+dV] = ac Cov[X,W] + ad Cov[X,V] + bc Cov[Y,W] + bd Cov[Y,V]
    * Cov is bilinear (distributes)!
  * Var[a^T x] = Var[sum(ai Xi)] = sumi(sumj(ai aj Cov[Xi,Xj]))
  * Hoeffding -- Cov[X,Y] = integral over x,y of (Fxy - Fx Fy) where F is cdf

Classic counterexample to independence = 0 cov is Y = X^2
  * Joint Normals actually do have independence = 0 cov

Cov is an inner product bc it is bilinear, symmetric, and positive
semi-definite. Thus, |Cov[X,Y]| <= sqrt(Var[X] Var[Y]) is Cauchy-Schwartz ineq.
  * Let Z = X - Cov[X,Y]/Var[Y] Y (like Gram-Schmidt orthog.), then 0 <= Var[Z]
    = Cov[Z,Z] = Var[X] - Cov[X,Y]^2 / Var[Y]

Rules for vector X
  * Cov[X,X] = E[(X-E[X])(X-E[X])^T] = E[X X^T] - E[X]E[X]^T
  * Cov[AX,AX] = E[(AX)(AX)^T]- E[AX] E[X^T A^T] = A Cov[X,X] A^T
  * Cov[X,Y] = Cov[Y,X]^T

## Matrix calculus

https://tminka.github.io/papers/matrix/minka-matrix.pdf

Derivatives are elementwise, but can be cleverly computed using matrices

S (scalar), V (vector), M (matrix) -- dS/dS, dV/dS, dM/dS, dS/dV, dV/dV, dS/dM
  * Partials w.r.t. numerator (denom) take numerator's (demom transpose's) shape
  * Thus, dV/dS is column vector and dS/dV is row vector

Define y(x + dx) = y(x) + A dx + O(small). Then A is Jacobian and A^T is grad(y)

Rules
  * dA = 0
  * d(aX) = a dX
  * d(X+Y) = dX + dY
  * d(tr(X)) = tr(dX)
  * d(XY) = (dX)Y + X(dY)
  * d(X x Y) = (dX) x Y + X x (dY), where x is Kronecker/Hadamard product
  * d(inv(X)) = -inv(X) dX inv(x)
    * Derived from 0 = dI = d(inv(X) X)
  * d|X| = |X| tr(inv(X) dX)
  * d log|X| = tr(inv(X) dX)
  * d(X') = (dX)' where ' rearranges elements (like transpose, vec, vec-trans)

Make into canonical form -- dS = S dS, dV = V dS, dM = M dS, dS = V dV, dV = M
dV, dS = tr(M dM)

Trace is typically dropped and 1/dX should cancel to leave answer

Recall that trace is invariant under cyclic permutation. 
  * Trace is basis-indep: A --> B A inv(B) yields tr(A) = tr(inv(B) B A) = tr(A)

Easier than Lagrange multiplier for symmetry constraint is baked-in:
  * dS(M) = tr(MdM) --> dS(M)/dM = (M + M^T) - diag(M)
  * If diagonal-only: dS(M) = tr(MdM) --> dS(M)/dM = diag(M)
    * If X is diagonal then so is dX.

E.g., PCA -- with E[X]=0, minimize E[(X-aV)^T (X-aV)] w.r.t. V with a = V^T X
  * E[...] = E[X^T X - a V^T X - X^T a V + a^2 V^T V] = Cov[X,X] - 2 a X^T V +
    a^2 V^T V --> maximize V^T C V - lambda(V^T V - 1) 
  * Taking derivative yields 2CV - 2 lambda V = 0, which occurs if V is eigenvec
  * This is maximized when v points in direction of eigenvector w largest val

E.g., Consider X = inv(A) U and ui ~ fi(wi). Observe X and W. Infer A to find U
  * p(U|W) = prod(fi(ui|wi)) and p(X|A,W) = |A| prod(fi(ui|wi))
  * log p(X|A,W) = log |A| + sum(log fi(ui|wi))
  * gradA log p(X|A,W) = inv(A)^T + (gradui fi(ui|wi) / fi(ui|wi)) X^T
    * I guess the intuition is d/dA = d/dU x where x is constant?
  * gradwi log p(X|A,W) = gradwi fi(ui|wi) / fi(ui|wi)
   
E.g., Infer cov matrix of zero-mean joint Normal pdf by max log-likelihood
  * log-lik = sum of -d/2 log(2pi) - 1/2 log|C| - 1/2 xi^T inv(C) xi
  * dS/dC gives M = sum of -1/2 inv(C) + 1/2 inv(C) xi xi^T inv(C)
    * Then apply symmetrization trick and set to zero. Yields C = sum(xi xi^T)/n
  * Answer is same as estimating each covariance. Note MLE uses n, not n-1

Kronecker product, vec, and vec-transpose allow for expression of multilinear
models that account for separate linear effects

Hadamard product is elementwise matrix mult.
  * If Z = X x Y, then CovZ = CovA x CovB

Partitioned matrix inversion uses A = Schur(D) = A - B inv(D) C
  * For multivariate Normal, Cov[X|Y] = Schur(D) where C = B^T (by symmetry) and
    E[X|Y] = E[X] + B inv(D) (Y - E[Y])
  * Sample covariance has Wishart distribution

Polar decomposition of A = PU, where P is positive-def and U is unitary (orthog)
  * This finds the closest unitary matrix to A, minimizing (A - U)
  * Same as taking complex decomposition of number, with magnitude and angle
  * Find most likely rotation matrix of identity matrix rotated plus white noise
    * Minimize tr((A-U)^T (A-U)) = tr(A^T A) - 2 tr(A^T U)
    * Maximize tr(A^T U) = tr(U A^T)
    * Find SVD of A^T = V S W^T --> tr(U A^T) = tr(W^T U V S) = tr(X S)
    * Now maximize tr(XS) = sum(Xii Sii) which is max when Xii = 1 and X = I.
      Thus, U = W V^T
  * Can change starting point to known B... just take SVD of B A^T

Hessian matrices are dS/(dV dV^T)
  * Take derivative of derivative. Note that d(dX) = 0
  * S(V + dV) = S(V) + A^T dVA + 1/2 dV^T H dV
  * Canonical forms -- d^2S = h(dS)^2, d^2S = dV^T H dV, d^2S = d vec(M^T) H d
    vec(M)
  * H must be symmetric

## Kalman filters -- Berkeley EECS 126

https://inst.eecs.berkeley.edu/~ee126/sp18/

Assume Xn = aX(n-1) + Vn and Yn = cXn + Wn. Observe Y, want E(Xn | Y1,2,...,n)
  * Assume for simplicity |a| < 1 (could introduce control term o/w) and c = 1
    (could rescale Y and W o/w)

Lemma: E(X|Y,Z) = E(X|Y) + E(X|Z - E(Z|Y)) 
  * E(Xn|Y1,...,Yn) = E(Xn-1|Y1,...,Yn-1) + E[Xn|Yn - E[Y|Y1,...,Yn-1]]
  * Conditional in second term is called innovation = In
  * Thus, Xn|n = Xn|n-1 + kn In and In = Yn - E[Xn + Wn | Y1,...,Yn-1] = Yn -
    Xn|n-1. Just determine kn = Kalman gain!

Geometric picture comes from constraints -- see article
  * Xn|n-1 is orthogonal to (Xn - Xn|n-1)
  * Innovation vector is orthogonal to original estimate E[Y|...] --> In is
    orthogonal to Xn|n-1
  * Yn = In + Xn|n-1 is now fixed
  * Project Xn onto In to get kn In. Project Xn - Xn|n-1 onto Yn - Xn|n-1 = Xn|n
  * Finally, use similar triangles to find kn = sn|n-1^2 / (sn|n-1^2 + sw^2)
  * Further, sn|n-1^2 = a^2 sn-1|n-1^2 + sv^2
  * Pythagorean theorem gives sn|n^2 = sn|n-1^2 (1 - kn)

Vector equations are simple generalizations of these equations

