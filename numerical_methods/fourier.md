# Fourier methods

Note: I use m as imaginary number and i as an index

## Chapter 12 from Numerical Recipes -- Fourier transform spectral methods

Basic properties
  * `H(f) = integral from -inf to inf of h(t) exp(2 pi m f t)`
  * `h(t) = integral from -inf to inf of H(f) exp(-2 pi m f t)`
  * Linear -- F(a + b) = F(a) + F(b), F(ca) = cF(a)
  * `h(t)` is even/odd --> `H(t)` is even/odd
  * `h(t)` is real/imaginary --> `H(-f) = H*(f)` / `H(-f) = -H*(f)`
  * `h(t)` is real+even/real+odd/imag+even/imag+odd --> `H(t)` is
    real+even/imag+odd/imag+even/real+odd
  * Time scaling -- `h(at) = 1/abs(a) H(f/a)`
  * Frequency scaling -- `1/abs(b) h(t/b) = H(bf)`
  * Time shifting -- `h(t - t0) = H(f) exp(2 pi m f t0)`
  * Frequency shifting -- `h(t) exp(-2 pi m f0 t) = H(f - f0)`
  * Convolution thm -- `g * h = integral(g(t') h(t-t') dt') = G(f) H(f)`
  * Correlation thm -- `Corr(g, h)(t) = integral(g(t+t') h(t')dt') = G(f) H*(f)`
    * `Corr(g, h)(t) = Corr(h, g)(-t)`
    * Wiener-Khinchin thm -- `Corr(g, g)(0) = |G(f)|^2`
  * Parseval's thm -- Power = `integral(|h(t)|^2)` = `integral(|H(f)|^2)`
    * One-sided power spectral density (PSD) = `Ph(f) = |H(f)|^2 + |H(-f)|^2`

Data is sampled every `delta` steps for sampling rate `1/delta`
  * Nyquist critical frequency = `fc = 1/(2 delta)`
  * Sampling thm -- `h(t) = delta * sum(hi sin(2 pi fc(t-i*delta))/(pi
    (t-i*delta)))` if `H(f) = 0` for all `f > fc`.
  * Aliasing -- all PSD outside of `(-fc, fc)` is spuriously
    moved into the region

Approximate `H(f)` at `fi = i / (N delta)` from `i = -N/2` to `i = +N/2`
  * First and last values are equivalent, leading to `N` overall terms (with 0)
  * `H(fj) = sum(delta hi exp(2 pi m fj ti))`
  * Discrete Fourier transform -- `Hj = sum(hi exp(2 pi m i j / N))`
  * Discrete inv Fourier transform -- `hj = 1/N sum(Hi exp(-2 pi m i j / N))`
  * Discrete Parseval's thm -- `sum(|hi|^2) = 1/N sum(|Hi|^2)`
  * `H(fj) ~= delta * Hj`
  * Periodicity gives `H_-n = H_N-n`

Fast Fourier Transform
  * Reduces `Hn` calculation for each `n` from `O(N^2)` to `O(N log N)`
  * Uses divide and conquer -- `Fi = Fie + Fio * exp(2 pi m i / N)`, where e is
    even and o is odd.
  * Transform of length 1 is just one of the data points, whose index (in
    binary) is the reverse of the pattern taken to get there with e=0 and o=1
  * Easiest is to pad out data with zeros until reaching length = power of 2

Convolution moves response `r(t)` over signal `s(t)`
  * Discrete version -- `ri` maps multiple of input `j` onto output `j+i`. `(r *
    s)j = sum(s_(j-i) * ri)`
  * Assumes signal is periodic with period N. Pad out signal data with zeros to
    avoid wrapping around
  * Perform `O(N log N)` convolution by taking FFT of `r` and `s` separately,
    then multiply FFTs, then inverse FFT that to get convolution `r * s`
  * Deconvolute by solving N equations in time domain (see above eqn) or divide
    (rather than multiply) FFTs of convolution and response to get `s`
    * Sensitive to noise, zeros in FFT of response, 

Correlation at lag `t` measures similarity between 2 functions with offset `t`
  * Discrete correlation = `Corr(g, h)j = sum(g_(j+i) hi) = Gj H*j`
  * FFT both datasets, multiply one by complex conjugate of other, inverse FFT.
    Final result is real and represents correlation at different lags
  * Use padding of zeros to negate periodicity assumption

Optimal (Wiener) filtering finds a filter P to apply to signal C, which is then
deconvolved by given response function R to produce noiseless signal U.
  * All capital letters are functions of frequency (Fourier versions)
  * Approximation of uncorrupted signal `U' = C P/R`. Smeared signal due to
    device = `S = R U`
  * Minimize distance bt approximation and true = `integral(|(S+N)P/R - S/R|^2)`
  * Optimizing w.r.t `P` gives `P = |S|^2 / (|S|^2 + |N|^2)`
  * Estimate `|S|^2 + |N|^2 ~= Pc(f) = |C|^2`, then plot PSD as function of f.
    Assume `|S|^2` goes to 0 at high f (leaving only `|N|^2`), then extrapolate
    `|N|^2` back and subtract from PSD to get `|S|^2`
    * 2nd order accuracy! 10% error from true filter yields 1% error in results

Estimating the PSD
  * Periodogram has formula `P(fi) = 1/N^2 (|Ci|^2 + |C_(N-i)|^2)`, with `P(0) =
    1/N^2 |C0|^2` and `P(fc) = 1/N^2 |C_(N/2)|^2` (Nyquist frequency)
    * `fi` goes from 0 to `N/2`
  * Leakage pours some power into `s` bins away -- `W(s) = 1/N^2 (sin(pi s) /
    sin(pi s / N))^2` = window function
  * Sampling with finer resolution causes bigger Nyquist range. Sampling more
    data makes more bins. Neither improves `Var[P]`/helps converge to true PSD
    * Can sum multiple k nearby samples into single big sample or average k
      independent FFTs. Both reduce variance by `1/k`
  * Window function is actually Fourier transform of unit-square. Replace with
    smoother window to reduce leakage!
    * Now multiply `P(fi)` by `1/Wss`, where `Wss = N sum(wi^2)`
  * Maximum entropy (all poles) method: map frequency to `z = exp(2 pi m f delta)`. 
  `P(f) = |sum(ci z^i)|^2` is a Laurent series. Approximate with `P(f) ~= a0 /
  |1 + sum(ai z^i)|^2`, whose poles represent delta functions (infinite power at
  some frequency). Pick desired number of poles and set up Toeplitz matrix to
  solve for `ai` coefficients
    * Works well for peaky data
    * More poles --> more sensitivity to noise

Digital filtering in real-time is useful for data streams
