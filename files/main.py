'''    _             _
  ___ | | _   _   __| | _ __   ___
 / _ \| || | | | / _` || '__| / _ |
|  __/| || |_| || (_| || |   |  __/
 \___||_| \__, | \__,_||_|    \___|
          |___/
___________________________________

 - codé en : UTF-8
 - langage : python3
 - GitHub  : github.com/elydre
 - Licence : GNU GPL v3
'''


from core.lexer     import Lexer     as LXR
from core.parser    import Parser    as PSR
from core.generator import Generator as GEN

import os

"""
LEXER -token-> PARSER -ast-> GENERATOR -> cpp
"""

version = "m-0.9"

path = os.path.dirname(os.path.abspath(__file__))

with open(f"{path}/input.ks", "r") as f:
    file = f.read()

lxr = LXR(file, debug_lvl = 1)
psr = PSR(lxr.run(), debug_lvl = 1)
gen = GEN(psr.run(), debug_lvl = 3)
cpp = gen.cpplist2file(gen.run())
print(cpp)