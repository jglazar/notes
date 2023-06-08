# Molecular dynamics

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

## Dynamic properties

## Non-equilibrium MD
