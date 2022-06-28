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

version = "g-0.2"

class Generator:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"GEN - {level}| {fonc_name} : {text}")

    def convert_to_cpp(self, ast: dict) -> str:
        # print(ast)
        if ast["type"] == "var" and "arg" in ast:
            out = f"int {ast['cnt'][1:]} = {self.convert_to_cpp(ast['arg'][0])}"

        elif ast["type"] == "func":
            out = f"{ast['cnt']}({', '.join(self.convert_to_cpp(e) for e in ast['arg'])})"

        elif ast["type"] == "int":
            out = ast["cnt"]

        elif ast["type"] == "var":
            out = ast["cnt"][1:]

        return out


    def run(self) -> None:
        out = [f"{self.convert_to_cpp(dico)};" for dico in self.inp]
        print("\n".join(out))
