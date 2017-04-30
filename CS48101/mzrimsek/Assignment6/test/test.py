import sys

def add(x, y):
    xInt = int(x)
    yInt = int(y)
    return xInt + yInt

def main(argv):
    arg1 = argv[0]
    arg2 = argv[1]

    print add(arg1, arg2)

if __name__ == "__main__":
    main(sys.argv[1:])