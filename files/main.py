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
from core.compiler import Compiler

import mod.cytron as cytron

"""
LEXER -token-> PARSE -ast-> COMPILER -cpp->
"""

version = "m-0.4"

file = cytron.rfil("./_ks", "main.ks")

print(file)
lxr = Lexer(file)
print(lxr.run())