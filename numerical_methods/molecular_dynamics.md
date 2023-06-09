# Molecular dynamics

Notes from NanoHub tutorial

## Forces

Potential energy has 2 contributions
  * Interatomic: pair, Coulomb, EAM
  * Intramolecular: bond, angle, torsion, out-of-plane

Pair potentials are popular, especially Lennard-Jones
  * LJ models long-range attractions due to instantaneous dipoles
  * LJ has short-range repulsion for overlapping electron clouds
  * `U(r) = k e ((s/r)^n - (s/r)^m)`, with `k = n/(m-m)*(n/m)^(m/(n-m))`, `n =
    12`, `m = 6`
  * Typical parameters are `e/kB = 30`, `s (pm) = 300`

Truncate LJ interaction for computational efficiency
  * Need to shift to remove discontinuity --  `U(r) - U(rc)`
  * Account for shift in post-processing

The united atom model clumps together molecule into one big atom

Coulombic interaction is important for significant electrostatic effects
  * `U(qi, qj, r) = 1/(4 pi eps0) qi qj / r`
  * Use Ewald summation, fast multipole methods, or particle-mesh methods to
    efficiently calculate long-range interactions
    * Ewald sum assumes particle is has Gaussian screening cloud of opposite
      charge. Then correct for screening cloud with compensating charge density

Embedded atom model assumes atoms are surrounded by sea of electrons
  * `U_total = sum(F(di)) + 1/2 sum(phi(rij))`, `di = sum(f(rij))`
* `di` is electron density at particle `i`, `F(di)` is embedding function,
  `phi(rij)` is pair potential between particles `i` and `j`, and `f(rij)` is
  the electron density function at particle `i` due to particle `j`

Reactive potentials model chemical reactions like bond formation/disassociation
  * E.g., Tersoff, reactive empirical bond order (REBO)
  * Common for silicon, carbon, oxygen, and hydrogen

Intramolecular interactions model bonds, angles, and torsion
  * Bond stretching
    * Harmonic `U = k/2 * (r - r0)^2`
    * Morse `U = D * (1-exp(-a(r-r0)))^2` (better for large displacements)
  * Bond angle
    * Harmonic `U = k * (theta - theta0)^2`
    * Cosine `U = k * (1 - cos(theta))`
  * Torsion (dihedral)
    * Harmonic `U = k * (1 + d * cos(n phi))`
  * Out-of-plane (uncommon, only relevant for planar molecules)
    * `U = k * h^2`

## Integration

Want a reversible, energy-conserving, efficient integrator with 1 force
evaluation per timestep

Want a middle-ground timestep
  * Short integration timestep has high round-off error, limits phase space 
  * Long integration timestep has high truncation error, numerical instability
  * Ideally, want timestep 10x shorter than shortest motion timescale
    * Atoms -- translation -- `10^-14`
    * Rigid molecules -- translation, rotation -- `5 * 10^-15`
    * Flexible molecules with rigid bonds -- translation, rotation, torsion --
      `2 * 10^-15`
    * Flexible molecules with flexible bonds -- translation, rotation, torsion,
      vibration -- `10^-15`

Verlet combines Taylor expansions for `r(t + dt)` and `r(t - dt)`. 
  * Final answer is `r(t + dt) = 2r(t) - r(t-dt) + d2r/dt2 dt^2 + O(dt^4)`
  * Velocity is implicit -- `v(t) = 1/(2 dt) * (r(t+dt) - r(t-dt))`
  * Requires prior two steps
  * Simple, with good stability. Error of `O(dt^2)`

Velocity Verlet improves accuracy. Combines expansions of position and velocity
  * Calculate mid-step velocity, calculate next-step position, calculate
    next-step accelerations, update velocities

Predictor-corrector alternates between prediction and correction
  * Predict next-step positions and velocities, calculate next-step
    accelerations from those, correct predictions
  * Algorithm-dependent coefficients maximize stability

Gear predictor-corrector uses 5th-order expansion
  * There are tabulated coefficients for nth-order predictors
  * Error is `O(dt^(n+1))`

## Temperature control

`T = M/(3 N kB) <sum(vi * vi)>`, where `M` is the total mass
  * Scale velocities to maintain T -- `v_new = v_old * sqrt(T_new / T_old)`

Berendsen adjusts coupling parameter between bath and system
  * `dT / dt = 1/tau (T_bath - T(t))`, with `dt / tau ~ 0.0025` recommended

Andersen has stochastic impulsive forces acting on randomly selected particles
  * Increase coupling by increasing collision frequency
  * Probabiltiy of selection is `nu dt`, and new velocities are taken from
    (Maxwell-?)Boltzmann distribution at desired temperature
  * `nu = 3 nu_c / N^2`, where `nu_c` is the collision frequency (itself a
    function of density and thermal conductivity)

Langevin dynamics simulates interactions with solvent
  * Frictional drag removes energy, random term adds it back
  * `ma = F - m gamma v + R`

Nose-Hoover has extra degree of freedom for heat bath
  * Also need time scaling parameter `s` with mass `Q` and velocity `s'`
  * Hamiltonian is `H = sum(pi^2 / 2ms^2 + U(r) + ps^2/2Q + (f+1)kB T ln(s))`
  * `Q` controls coupling
    * Large --> loose coupling --> poor temperature control
    * Small --> tight coupling --> high-frequency temperature oscillations
    * `Q = C f kB T`, where `C` is found via testing

## Boundary conditions

Fixed repulsive walls are simplest
  * `U(z) = eps (z/s)^-12`, but can have more complicated 10-4-3 potential

Can also have atomistic walls made of static particles
  * Can be rigid or semi-rigid, where wall particles are held with springs

Periodic boundary conditions allow macroscopic property prediction
  * Replicate primary cell in all directions to get image cells
  * Can be cubic, hexagonal prism, ... any space-filling 3D shape
  * Only 1 image is ever a distance less than `L/2` -- just truncate pair
    forces to `r_c = L/2`!

## Neighbor and cell lists

Neighbor list has index of nearest neighbors -- just check your adjacent
particles, your neighbors, and their neighbors
  * Update neighbor lists every 10-20 timesteps. Lower is inefficient, higher
    causes force errors
  * Need to correct for excluded energy at the end of the simulation

Cell lists divide simulation box, and only consider interactions between
particles within the same cell
  * Cell list maintains squares, scales as `O(N)`
  * Verlet list maintains radius, scales as `O(N^2)`

## Initialization and equilibrium

Initialize positions with Monte Carlo or on default lattice
  * Lattice initialization requires melting at start

Initialize velocities by temperature, with zero overall velocity
  * Can simply load from previous simulation
  * Uniform dist -- `v = rng(-1, 1) * sqrt(T)`, then `v = v - <v>` to center
  * Maxwell-Boltzmann dist -- `f(v) = sqrt(m/(2 pi kB T) exp(-mv^2 / (2 kB T)))`

Equilibration isn't guaranteed, but check for
  * Constant total energy (for NVE)
  * Stable velocity dist
  * Stable positional disorder -- `lx = 1/N sum(cos(4 pi xi / a))`, `l = (lx +
    ly + lz)/3`
  * Reasonable and stable thermodynamic properties like temperature and pressure
    * Magnitude of fluctuations should be related to `sqrt(N)`
  * Stable properties against small perturbations, like small amount of heat
  * Stable Boltzmann's H-function -- `Hx = sum over dvx(f(vx) ln(f(vx)) dvx)`,
    `H = (Hx + Hy + Hz)/3`

## Static properties

Pressure is typically calculated using Irving-Kirkwood equation ("pressure
virial")
  * `P = 1/V ( sum(m * v^2) + sum_pairs(f * r) )` considers energy moving 
  across space and interactions through space
  * `P_ab = -1/V < sum(mi uia uib) + sum_pairs(rija Fijb) >`

Mean square force gives information on share of repulsive potential
  * One atom -- `<F0^2> = <sum((del U(r0))^2)>`
  * All atoms has similar formula, but considering PBC

Calculate thermodynamic property w.r.t. changes by:
  * Tracking changes across different simulations
  * Evaluating derivatives analytically via statistical mechanics
    * Typically less accurate due to roundoff errors (?)
  * E.g., `C = dU/dT = 1/(kB T^2) Var[U]`
  * Similar for adiabatic compressibility `k = -1/V dV/dP` and thermal pressure
    coefficient `gamma = dP/dT`

Entropic properties require calculations beyond time-averaging MD
  * Thermodynamic integration casts entropy change as integral of `U` and `T`.
    Just perform multiple simulations to approximate integral 
  * Test particle method estimates chemical potential, but fails at high density
  * Coupling parameters redefine `U` as `U(r, lambda)`. `lambda_0` is typically
    ideal gas model. Systematically vary `lambda` to calculate entropy

Static structure is evaluated with radial distribution function `g(r)`
  * `density * g(r) = 2/N sum_pair(delta(r - rij))`
  * `density / (N-1) g(r) V(r, dr)` is prob. that atom lies within shell
  * Ideal gas has `g(r) = 1`. Low-density gas has `g(r) = exp(-U(r)/(kB*T))` 
  * RDF can be used to identify phases near fluid-solid boundaries

## Dynamic properties

`C(t) = 1/tau * integral from 0 to tau (a(t0) b(t0 + t) dt0) = <a(t0) b(t+t0)>`
  * Correlation function is invariant under shift of `t0`
  * Static correlation function -- `t0 = 0`. Should factorize to `<a><b>` as `t
    -> infinity`
  * Autocorrelation function must have zero slope at `t = 0`

Velocity and stress autocorrelation functions are useful for mechanical
properties
  * Derivative of stress autocorrelation near `t = 0` gives shear modulus

Transport coefficients can be calculated by:
  * Einstein relations, which take time derivative of correlation function
  * Green-Kubo relations, which integrate correlation function over time
  * Flux = -resistance coefficient x gradient -- think diffusion
  * E.g., `Var[X(t) - X(0)] = 2Dt` for large times compared to atomic collisions
  * Similarly, `D = integral from 0 to infinity (1/(3N) sum(VACF))` and
    `viscosity = integral from 0 to infinity (density/(3 N kB T) sum(stress
    ACF))`

## Non-equilibrium MD

Improves efficiency of transport coefficient calculations
  * Time correlation functions are error-prone because fluctuations are small
  * NEMD imposes large fluctuation, from which we can measure response
  * Need large perturbations (bigger than experiments)
  * Hard to extrapolate to low perturbation characteristics

Direct measurement uses boundaries where particles have external momentum
  * Can also heat walls and let heat seep into bulk

Modified dynamics perturb equations of motion
  * New Hamiltonian `Hnew = H + A F`, where `A` is coupling matrix
  * Constant perturbation -- response proportional to time-integrated
    correlation functions
  * Pulse perturbation -- response proportional to correlation functions
  * Oscillation perturbation -- response proportional to real and imaginary
    parts of Fourier-Laplace transformed correlation functions

Calculate viscosity and thermal conductivity with:
  * Couette flow -- shear top wall, keep bottom wall stationary
  * Poiseuille flow -- keep both walls stationary and push bulk

Other perturbations
  * Expand/contract to get diagonal components of stress tensor 
  * Induce energy flux to get thermal conductivity 
  * Tag particles to track diffusion coefficients
