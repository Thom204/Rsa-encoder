## Compile with g++ as follows

**g++ -o RSA.exe RsaEncrypt.cpp MDC.cpp**   for windows

**g++ -o RSA RsaEncrypt.cpp MDC.cpp**    for linux



## Considerations

all the input text has to be stored in crypt/input.txt before runnign the program

the program does not support non ascii characters

when using the program on crypt mode the original files will be deleted after encryption/decryption

The private key for decryption will be one of the prime factors of the public key z



## Functionalities

1. Encrypt
   > Encrypts the content from crypt/input.txt using the current public keys and writes it in crypt/encrypted.txt.
   > 
   > If the program is on crypt mode the input file will be deleted after encryption.
   > 
   > If the program is on test mode it will leave the input file untouched.
   
2. Decrypt
   > Decryts the content from crypt/encrypted.txt using one of the private keys provided by the user (doesn't matter wich one).
   > 
   > If the program is on crypt mode the decrypted content will be written in crypt/input.txt and the encrypted file will be deleted.
   > 
   > If the program is on test mode the decrypted content will be written in crypt/decrypted.txt and the encrypted file will remain untouched.

3. Set public keys via private key insertion
   > Ask the user to provide two prime numbers p and q, those primes will be the private keys for decryption, the number z= pq will be the public key z.
   > 
   > Ask the user to provide a number n such that GCD(n, phi(pq))= 1, the number n will be the public key n.
   > 
   > If n does't fillfull the requirement the program will encourage the user to choose n as a prime number, n is recomended to be samller than z.
   > 
   > Once set, the pair of public keys z, n will be stored in keys.txt.
   > 
   > Once the public key pair is set it will remain set even if you terminate excecution.
   > 
   > p and q will NOT be stored anywhere outside the program.

4. Set public keys via public key insertion
   > Ask the user to provide the public key z.
   > 
   > Ask the user to provide the public key n.
   > 
   > For this mode n has to be prime.
   > 
   > Once set, the pair of public keys z, n will be stored in keys.txt.
   > 
   > Once the public key pair is set it will remain set even if you terminate excecution.
   > 
   > For this insertion mode you don't need to know the private keys, it allows a user to encrypt files using another user's public pair.

5. Switch mode
   > The program has two main modes wich modify how the program behaves.
   > 
   > crypt mode: in this mode the input file for any operationwill be deleted after success leaving only the output (see more details above).
   > 
   > test mode: in this mode the input files will remain untouched.

# Aditional considerations
the general encryption method and some algorithms have been taken from the following textbook:
https://books.google.com.co/books/about/Discrete_Mathematics.html?id=KJwvt2Zz2R8C&redir_esc=y
