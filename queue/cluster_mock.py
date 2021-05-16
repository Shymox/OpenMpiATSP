#!/usr/bin/env python
import time
import sys

def main():
    time.sleep(5)
    with open(sys.argv[1], 'r') as file:
        print("**HERE WILL BE TSP RESULT**", file.readlines())

if __name__ == "__main__":
    main()