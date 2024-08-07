# sqrtOpt
An optimizer for my own square root formula

```math
\sqrt(x) \approx \frac{x + (H(x) + \frac{x}{20 + \frac{x}{n}})^{2}}{2(H(x)+\frac{x}{20+\frac{x}{n}})}
```
- Where `H` is the Harmonic number of `x`
- Smaller numbers tend to be more accurate with a higher `n`
- Larger numbers tend to be more accurate with a smaller `n`
- I have calculated that for numbers 1-1000, `43.993` works generally OK
- `41.905` works well for smaller numbers (1-100)
- [desmos](https://www.desmos.com/calculator/d2kerh6zgs)
## To try yourself, in `main`
- Change `lower` for the lowest number to optimize for
- Change `upper` for the highest number to be optimizing for
