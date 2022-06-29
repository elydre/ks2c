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

version = "g-0.4"

file_empty = """
#include "ks.h"

int main() {
    <code>
}
"""

class Generator:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"GEN - {level}| {fonc_name} : {text}")

    def cpplist2file(self, cpplist: list) -> str:
        return file_empty.replace("<code>", f"\n{' '*4}".join(cpplist))[1:]

    def convert_to_cpp(self, ast: dict, first: bool = False) -> str:
        # sourcery skip: low-code-quality

        if ast["type"] == "keyword" and ast["cnt"] == "END": 
            self.tab -= 1

        out = " " * 4 * self.tab if first else ""

        if ast["type"] == "keyword" and ast["cnt"] == "END":
            out += "}"

        if ast["type"] == "var" and "arg" in ast:
            if ast["cnt"][1:] not in self.var_list:
                self.var_list.append(ast["cnt"][1:])
                out += "int "
            out += f"{ast['cnt'][1:]} = {self.convert_to_cpp(ast['arg'][0])}{';' if first else ''}"

        elif ast["type"] == "func":
            out += f"{ast['cnt']}({', '.join(self.convert_to_cpp(e) for e in ast['arg'])}){';' if first else ''}"

        elif ast["type"] == "int":
            out += f"{ast['cnt']}{';' if first else ''}"

        elif ast["type"] == "string":
            print("les strings sont pas encore totalement supportés")
            out += f"{ast['cnt']}{';' if first else ''}"

        elif ast["type"] == "var":
            out += f"{ast['cnt'][1:]}{';' if first else ''}"

        elif ast["type"] == "keyword" and ast["cnt"] == "IF":
            out += f"if ({self.convert_to_cpp(ast['arg'][0])})" + " {"
            self.tab += 1

        elif ast["type"] == "keyword" and ast["cnt"] == "WHILE":
            out += f"while ({self.convert_to_cpp(ast['arg'][0])})" + " {"
            self.tab += 1

        elif ast["type"] == "keyword" and ast["cnt"] == "LOOP":
            out += f"for (int i = 0; i < {self.convert_to_cpp(ast['arg'][0])}; i++)" + " {"
            self.tab += 1

        elif ast["type"] == "keyword" and ast["cnt"] == "BREAK":
            out += "break;"

        return out


    def run(self) -> list:
        self.tab = 0
        self.var_list = []
        return [f"{self.convert_to_cpp(dico, True)}" for dico in self.inp]
