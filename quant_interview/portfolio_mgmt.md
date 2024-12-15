# Portfolio optimization

[Theoretical walkthrough](https://docs.mosek.com/MOSEKPortfolioCookbook-a4paper.pdf)

[Course notes](https://faculty.washington.edu/ezivot/econ424/portfolioTheoryMatrix.pdf)

Assume we have a collection of risky assets with expected returns mu and
covariance structure sigma. How do we construct our portfolio weights x to:
  * Maximize returns / variance = `x^T mu / x^T S x`
  * Minimize variance = `x^T S x`
  * Maximize returns - lamdba * variance = `x^T mu - l x^T S x`

While maintaining `x^T 1 = 1`

Quadratic goals with linear constraints are easy to solve. More general cases
(with upper bounds on risk, e.g.) require conic formulation. Can use
professional software like MOSEK to solve.

Conic problems arise after Cholesky decomposing (or factor modeling) `S = G
G^T`. Then minimizing `x^T S x = x^T G G^T x = |G^T x|^2`, where we can now
think of our solution as lying on a conic section.

This worked-through [question+answer](https://quant.stackexchange.com/questions/59202/derivation-of-mean-variance-portfolio-weights-as-closed-form-analytical-solution) 
shows:
  * Start with a Lagrangian `L = x^T mu - l x^T S x - g (x^T 1 - 1)`
  * Minimize w.r.t x and g. 
  * This leads to a system of linar eqns `[[lS, 1],[1^T, 0]] [x, g] = [mu, 1]`
  * Apply Schur complement finds nice form for optimal x and g
  * `xOPT = xMVP + 1/l muMVP / sMVP^2 (xTANG - xMVP)`, where TANG is the
    tangency portfolio `xTANG = S^-1 mu / 1^T S^-1 mu` and MVP is the min
    variance portfolio `xMVP = S^-1 1 / 1^T S^-1 1`
