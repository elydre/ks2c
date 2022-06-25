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

import mod.cytron as cytron

"""
LEXER -token-> PARSER -ast-> GENERATOR -> cpp
"""

version = "m-0.6"

file = cytron.rfil("./_ks", "main.ks")

print(file)
lxr = Lexer(file, debug_lvl=3)
psr = Parser(lxr.run(), debug_lvl=3)
psr.run()
