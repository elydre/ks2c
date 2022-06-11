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

version = "p-0.3"

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
