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

from operator import xor


version = "p-0.5"

class Parser:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl

        self.CONVERT_TABLE = {
            "**": "pow",
            "*": "mul",
            "/": "div",
            "+": "add",
            "-": "sub",
            "==": "eq",
            "!=": "neq",
            "+=": "sup",
            "-=": "inf",
            "!": "not",
        }

        self.PRIORITY = ["**", "*", "/", "+", "-", "==", "!=", "+=", "-=", "!"]
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"PSR - {level}| {fonc_name} : {text}")

    def parse_line(self, line: list) -> dict: ...


    def check(self) -> None:
        for line in self.inp:
            old = 0
            for dico in line:
                for a, b, c in ((dico["iph"], old, 0), (dico["oph"], len(dico["cde"]), 1)):
                    if xor(a != b, (line.index(dico) == len(line) - 1 and c)):
                        print(f"nombre de push non valide: {a} != {b}")
                    old = dico["oph"]

    def run(self) -> list:
        self.check()
        return [self.parse_line(line) for line in self.inp]