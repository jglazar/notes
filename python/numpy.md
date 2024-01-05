# Numpy and Numba

## Numpy copying

Arrays are contiguous, whereas lists can be scattered in memory
  * Numpy defaults to row-major (like C). Can specify, though

Intermediate copies degrade performance, as in C++

Good things:
  * In-place operations -- `arr *= 2` is 2x faster than `arr = arr*2`
  * Ravel 
  * Broadcasting -- `a1 * a2` is 10x faster than `np.tile(...) * np.tile(...)`
  * Views -- `arr[i:j]` points directly to area in memory. Can overwrite!

Sometimes bad things:
  * Reshaping -- good alone, but requires copy if transposing too
  * Transposing -- good alone, but requires copy if reshaping too

Bad things:
  * New arrays -- `arr * 2` creates new array
  * Flatten
  * Copy
  * Tile
  * Fancy indexing -- `arr[arr>0]` creates copy

Reshaping changes strides
  * `Location = arr.strides[0] * i0 + arr.strides[1] * i1`
  * E.g., transpose reverses stride order. Flattening transpose requires copy

Broadcasting stretches size-1 dimensions to fit operation at hand
  * Work backwards from last dimension to first

## Numpy speed

Python ints are objects with lots of overhead, and lists can handle
heterogeneous elements. Numpy arrays are simple and homogeneous

Summing matrix of float64 is fastest via `np.sum(a.dot(np.ones(a.shape[1])))`.
Summing matrix of float32 is fastest via `np.sum(a)`
  * Weird architecture-specific quirk?

Prefer broadcasting to looping. Sometimes, though, mixing broadcasting and
looping can be worse than simply looping due to cache misses
  * E.g., `np.sqrt(Xsq[:, np.newaxis]) - 2.0 * X.dot(Y.T) + Ysq` is fastest way
    to compute X x Y matrix of pairwise distances
  * Try to broadcast arrays as small as possible to avoid cache misses
