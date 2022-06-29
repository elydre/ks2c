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

version = "g-0.7"

file_empty = """
#include "ks.h"

<func>

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


    def cpplist2file(self, func: list, code: list) -> str:
        return file_empty.replace("<code>", f"\n{' '*4}".join(code)).replace("<func>", "\n".join(func)).replace("\n\n\n","\n\n")[1:]


    def convert_to_cpp(self, ast: dict, first: bool = False) -> str:
        # sourcery skip: low-code-quality

        self.debug_print("convert_to_cpp", f"{ast}", 3)

        if self.in_func and self.tab == 0:
            self.in_func = False

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
            out += f"f_{ast['cnt']}({', '.join(self.convert_to_cpp(e) for e in ast['arg']) if 'arg' in ast else ''}){';' if first else ''}"

        elif ast["type"] == "int":
            out += f"{ast['cnt']}{';' if first else ''}"

        elif ast["type"] == "string":
            self.debug_print("convert_to_cpp", "les strings sont pas encore totalement supportés", 1)
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
            out += f"for (int _i = 0; _i < {self.convert_to_cpp(ast['arg'][0])}; _i++)" + " {"
            self.tab += 1

        elif ast["type"] == "keyword" and ast["cnt"] == "BREAK":
            out += "break;"

        elif ast["type"] == "keyword" and ast["cnt"] == "FUNC":
            out += f"int f_{ast['arg'][0]['cnt'][1:-1]}({', '.join(f'int {self.convert_to_cpp(e)}' for e in ast['arg'][1:]) if 'arg' in ast else ''})" + " {"
            self.tab += 1
            self.in_func = True

        elif ast["type"] == "keyword" and ast["cnt"] == "RETURN":
            out += f"return {self.convert_to_cpp(ast['arg'][0])};"


        self.debug_print("convert_to_cpp", f"{out}", 3)
        return out

    def run(self) -> list:
        self.tab = 0
        self.var_list = []
        self.in_func = False
        func, code = [], []
        for dico in self.inp:
            s = self.convert_to_cpp(dico, True)
            if self.in_func:
                func.append(s)
            else:
                code.append(s)

        return func, code
