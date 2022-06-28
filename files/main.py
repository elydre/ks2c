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


from core.lexer import Lexer
from core.parser import Parser
from core.generator import Generator
import os

"""
LEXER -token-> PARSER -ast-> GENERATOR -> cpp
"""

version = "m-0.7"

path = os.path.dirname(os.path.abspath(__file__))

with open(f"{path}/input.ks", "r") as f:
    file = f.read()

print(file)
lxr = Lexer(file, debug_lvl = 1)
psr = Parser(lxr.run(), debug_lvl = 1)
psr.run()
