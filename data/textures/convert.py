#! /usr/bin/python2.7

from PIL import Image
import struct, sys

im = Image.open(sys.argv[1] + ".png")

f = open(sys.argv[1] + ".tex", "wb")
f.write(b"".join(struct.pack("B", v) for v in im.getdata()))
f.close()
