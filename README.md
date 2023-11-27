## Project description
The project is a programme for encrypting text using different encryption algorithms. The user can select one of the available algorithms, specify the text to be encrypted, the key and, if necessary, the input/output files.


### Main Functions
Encryption algorithm selection: The following algorithms are supported:

- XOR
- RC4
- Vigenère
- RSA (GMP library required)

Text encryption: The user can specify the text to be encrypted directly via the command line or provide a text file.

Key specification: For algorithms requiring a key, the user must provide the appropriate key.

Output encrypted data: Encrypted data can be printed to the console or saved to a file.


### Usage

Follow the steps below to use the programme:
 - make all 
 - cypher_main --help

## Examples of use:

### Encrypting text using XOR:

cypher_main -C xor -t Hello, World! -k secret

### Encrypt a file using RC4 and save the output to a file:

cypher_main -C rc4 -f input.txt -k secret -o encrypted.txt

### Encrypting text using the Vigenère cipher:

cypher_main -C vig -t Hello, World! -k keyphrase

### Encrypting a file using RSA:

cypher_main -C rsa -f input.txt

## Notes

RSA works in test mode without writing to a file

Make sure that the provided key is compatible with the chosen encryption algorithm.
RSA encryption uses the GMP library, so make sure it is installed and properly linked to your project.

## Conclusion

This project provides a handy tool for encrypting text using various algorithms. It can be useful for training, testing, or just to protect your data.