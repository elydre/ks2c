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


version = "p-0.8"

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


    def parse_line(self, line: list) -> list: ...



    def check(self) -> bool:
        for line in self.inp:
            old = 0
            for i in range(len(line)):
                dico = line[i]
                for a, b, c in ((dico["iph"], old, 0), (dico["oph"], len(dico["cde"]), 1)):
                    if not xor(a != b, (len(line) - 1 == i and c)):
                        old = dico["oph"]
                        continue
                    msg = f"'{''.join([d['cnt'] for d in dico['cde'][0]])}'"
                    self.debug_print("check", f"ERROR #push: ({a} != {b}) dans {msg}", 1)
                    return False
        return True

    def run(self, calm_mod: bool = False) -> list:
        out = []
        if not (self.check() or calm_mod):
            return out
        for line in self.inp:
            out.extend(self.parse_line(line))
        return out
