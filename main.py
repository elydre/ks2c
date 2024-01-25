'''    _             _
  ___ | | _   _   __| | _ __   ___
 / _ \| || | | | / _` || '__| / _ |
|  __/| || |_| || (_| || |   |  __/
 \___||_| \__, | \__,_||_|    \___|
          |___/
___________________________________

 - langage : python3
 - GitHub  : github.com/elydre
 - License : GNU GPL v3
'''

from core.lexer     import Lexer     as LXR
from core.parser    import Parser    as PSR
from core.generator import Generator as GEN

from optparse import OptionParser
import os, core.tools as tools

"""
LEXER -token-> PARSER -ast-> GENERATOR -> C
"""

version = "2.1"

parser = OptionParser()

parser.add_option("-d", "--debug", dest="debug", default=0, help="debug level")
parser.add_option("-f", "--file", dest="file", default=False, help="file to compile")
parser.add_option("-o", "--output", dest="output", default=f"{os.path.dirname(os.path.abspath(__file__))}/o_src/main.c", help="output file")
options = parser.parse_args()

if options[0].file == False and len(options) >= 2:
    if len(options[1]) > 1:
        tools.raise_error("Too many files specified")
    if len(options[1]) == 1:
  	  	options[0].file = options[1][0]
options = options[0]

if options.debug:
    try:
        options.debug = int(options.debug)
    except ValueError:
        print("Debug level must be an integer")
        exit(1)

def get_data(file_name: str):
    if file_name:
        try:
            with open(file_name, "r") as f:
                return f.read()
        except FileNotFoundError:
            tools.raise_error(f"File '{file_name}' not found")

    print("No file specified, please enter your code")
    print("Press Ctrl+D to end input, Ctrl+C to exit")

    user_input = ""
    while True:
        try:
            user_input += input("~ ") + "\n"
        except EOFError:
            break
    print()
    return user_input

lxr = LXR(get_data(options.file), debug_lvl = options.debug)
psr = PSR(lxr.run(), debug_lvl = options.debug)
gen = GEN(psr.run(), debug_lvl = options.debug)
gen.run()
c = gen.clist2file()

with open(options.output, "w") as f:
    f.write(c)
