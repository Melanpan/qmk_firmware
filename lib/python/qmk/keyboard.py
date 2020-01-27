import hashlib

# Generate the USB Product ID
def generate_pid(str):
    str = str.encode('utf-8')
    str = hashlib.sha1(str).hexdigest()[0:4].upper()
    return str
