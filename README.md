# MyPgp
Data Encryption and Decryption Tool

This tool represents data to be ciphered and encryption keys as sequences of bytes in hexadecimal. Each pair of hexadecimal characters represents a single byte in little-endian order.

## Compilation
To compile this project just run
```bash
make
```
This will create a binary named "mypgp" at the root of the repository.

## USAGE
Launch the program by executing the binary and providing the necessary arguments:

```
USAGE
	./mypgp [-xor | -aes | -rsa | -pgp] [-c | -d] [-b] KEY
	the MESSAGE is read from standard input
DESCRIPTION
	-xor computation using XOR algorithm
	-aes computation using AES algorithm
	-rsa computation using RSA algorithm
	-pgp computation using both RSA and AES algorithm
	-c MESSAGE is clear and we want to cipher it
	-d MESSAGE is ciphered and we want to decipher it
	-b block mode: for xor and aes, only works on one block
		MESSAGE and KEY must be of the same size
	-g P Q for RSA only: generate a public and private key pair from the prime number P and Q
```

> [!warning]
> The **MESSAGE** is read from standard input
> Without the "-b" modifier, your algorithm must work in stream mode, meaning the message to cipher/decipher can be of any length.

## Examples
Here are some usage examples of the mypgp tool:
### Ciphering
```bash
echo "c2486f4796f0657481a655c559b38aaa" | ./mypgp -pgp -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3

Output----------------
a5c84b72ad9d8f1bde9bf5cd07693442b6d63164187318d0ec55f82d3e30a690aabd65f24956a2db85ebe17d67108a682db546315923aa3a945b08261f11f77bb7736d6738ffc100390ce2bca9ebc0e5
```
Here we are ciphering the message `c2486f4796f0657481a655c559b38aaa` with the rsa public key `010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3`

And are getting the following ciphered message:
`a5c84b72ad9d8f1bde9bf5cd07693442b6d63164187318d0ec55f82d3e30a690aabd65f24956a2db85ebe17d67108a682db546315923aa3a945b08261f11f77bb7736d6738ffc100390ce2bca9ebc0e5`

### Deciphering
```bash
echo "a5c84b72ad9d8f1bde9bf5cd07693442b6d63164187318d0ec55f82d3e30a690aabd65f24956a2db85ebe17d67108a682db546315923aa3a945b08261f11f77bb7736d6738ffc100390ce2bca9ebc0e5" | ./mypgp -pgp -d 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3

Output----------------
c2486f4796f0657481a655c559b38aaa
```
Here we are deciphering the messages we have generated before with the rsa private key `81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3`

And are getting our original message as a result:
`c2486f4796f0657481a655c559b38aaa`
