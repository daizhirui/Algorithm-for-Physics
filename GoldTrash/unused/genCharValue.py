for x in range(0,26):
    print("\tChar_{} = 1<<{},".format(chr(x+ord('a')),x))
for x in range(0,26):
    print("\tChar_{} = 1<<{},".format(chr(x+ord('A')),x+26))