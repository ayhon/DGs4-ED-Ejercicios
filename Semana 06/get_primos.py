from sympy import isprime

def ifelse(a,b,c):
    if a:
        return b
    return c

primes = [ ifelse(isprime(x), "true", "false") for x in range(2, 5010) ]

print("vector<bool> is_prime = {false, false, ",", ".join(primes),"};",sep="")

