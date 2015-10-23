__author__ = 'drathier'

from hashlib import *  # md5 2180a11d4d94fd6cc38c36e26e80a594
import fileinput       # line-by-line md5 bdaa10d
f = [x.strip() for x in fileinput.input()]
print md5("".join(f)).hexdigest()
print "".join([md5(x).hexdigest()[0] for x in f])
