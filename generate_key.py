

from cryptography.fernet import Fernet

# Generate the encryption key
key = Fernet.generate_key()

# Print the key (you'll copy and save this in your .env file)
print(key.decode())  # This prints the key as a string
