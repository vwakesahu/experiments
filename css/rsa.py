import random

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(a, m):
    m0, x0, x1 = m, 0, 1
    while a > 1:
        q = a // m
        m, a = a % m, m
        x0, x1 = x1 - q * x0, x0
    return x1 + m0 if x1 < 0 else x1

def generate_rsa_keys(p, q):
    n = p * q
    phi = (p - 1) * (q - 1)

    e = random.randint(2, phi - 1)
    while gcd(e, phi) != 1:
        e = random.randint(2, phi - 1)

    d = mod_inverse(e, phi)
    return (n, e), (n, d)

def rsa_sign(private_key, message):
    n, d = private_key
    signature = pow(message, d, n)
    return signature

def rsa_verify(public_key, signature, message):
    n, e = public_key
    verified_message = pow(signature, e, n)
    return verified_message == message

if __name__ == "__main__":

    # Input p and q
    p = int(input("Enter value of p: "))
    q = int(input("Enter value of q: "))

    # Input the message
    message = int(input("Enter the message (integer): "))

    # Generate RSA keys
    public_key, private_key = generate_rsa_keys(p, q)


    # Sign the message
    signature = rsa_sign(private_key, message)

    # Verify the signature
    verified = rsa_verify(public_key, signature, message)

    # Print whether the message is accepted or rejected
    if verified:
        print("Message Accepted")
    else:
        print("Message Rejected")




# Enter value of p: 5
# Enter value of q: 7
# Enter the message (integer): 8999545548
# Message Rejected
# (base) computer@computer-ThinkCentre:~/Desktop/Vivek$ python exp3.py 
# Enter value of p: 61
# Enter value of q: 53
# Enter the message (integer): 35
# Message Accepted
# (base) computer@computer-ThinkCentre:~/Desktop/Vivek$ python exp3.py 
# Enter value of p: 823
# Enter value of q: 953
# Enter the message (integer): 19070
# Message Accepted
# (base) computer@computer-ThinkCentre:~/Desktop/Vivek$ python exp3.py 
# Enter value of p: 823
# Enter value of q: 953
# Enter the message (integer): 19070
# Public Key:  (784319, 764539)
# Private Key:  (784319, 272467)
# Message Accepted
