import math
from collections import Counter
import numpy as np

def uniform_pdf(x,a,b):
    return 1/(b-a) if a <= x and x <= b else 0

def uniform_cdf(t,a,b):
    if t < a:
        return 0
    if t > b:
        return 1
    return (t-a)/(b-a)

def normal_pdf(x, mu, sigma):
    return (1/(sigma*np.sqrt(2 * np.pi))) * np.exp(-1*(x - mu)**2 / (2 * sigma**2))

def normal_cdf(x, mu, sigma):
    return (1 + math.erf((x-mu)/(sigma*np.sqrt(2))))/2

def binom_draw(n,p):
    """Generate one draw from a Binomial(n,p) distribution"""
    return np.sum(np.random.choice([0,1],size=n,p=[1-p,p]))   

def normal_approx_of_flips(n,p):
    """calculate mu and sigma of Normal approximation to Bimomial(n,p)"""
    mu = n*p
    sigma = math.sqrt(p*(1-p)*n)
    return mu, sigma

def inverse_normal_cdf(p, mu, sigma):
    """Approximate smallest x such that normal_cdf(x,mu,sigma) >= p"""
    low = -1 # TODO: make this dynamic based on mu and sigma
    while( normal_cdf(low, mu, sigma) > 1e-10 ):
        low *= 2
    high = 1
    while( normal_cdf(high, mu, sigma) < 1-1e-10 ):
        high *= 2
    
    # Structure of binary search: 
    #  - check middle: (high+low)/2
    #  - if cdf(middle) < p, low = middle
    #    else high = middle
    #  - stop when |high-low| < tolerance
    
    tol = 1e-5

    # as a backup to avoid weirdness when convergence takes too long,
    # could build in a max iteration count too...
    
    while abs(high-low) > tol:
        mid_x = (low+high)/2
        mid_p = normal_cdf(mid_x, mu, sigma)
        
        if mid_p < p:
            low = mid_x
        else:
            high = mid_x
            
    return mid_x

def normal_probability_above(t, mu, sigma):
    """Calculate P(X > t)"""
    # int from t to inf is 1 - int from -inf to t
    return 1 - normal_cdf(t,mu,sigma)

def normal_probability_between(a,b,mu,sigma):
    return normal_cdf(b,mu,sigma) - normal_cdf(a,mu,sigma)

def normal_probability_outside(a,b,mu,sigma):
    return 1 - normal_probability_between(a,b,mu,sigma)

def normal_upper_bound(p, mu, sigma):
    """Tell us what value z is such that P(X <= z) = p"""
    return inverse_normal_cdf(p, mu, sigma)

def normal_lower_bound(p, mu, sigma):
    """get z so that P(X >= z) = p"""
    return inverse_normal_cdf(1-p, mu, sigma)

def normal_two_side_bound(p, mu, sigma):
    """Get the range around mu so that P(a < X < b) = p"""
    tail = (1-p)/2
    
    # bottom because we want upper bound the left tail
    bottom = normal_upper_bound(tail, mu, sigma)
    
    # top because want to lower bound the right tail
    top = normal_lower_bound(tail, mu, sigma)
    
    return bottom, top

def two_sided_p(x, mu, sigma):
    if x >= mu:
        return 2 * normal_probability_above(x,mu,sigma)
    else:
        return 2 * normal_cdf(x,mu,sigma)

def ab_parameters(n, N):
    mu = n/N
    sigma = math.sqrt(mu * (1-mu) / N)
    return mu, sigma

def ab_statistic(nA, NA, nB, NB):
    mu_A, sigma_A = ab_parameters(nA, NA)
    mu_B, sigma_B = ab_parameters(nB, NB)
    return (mu_A - mu_B) / math.sqrt(sigma_A**2 + sigma_B**2)