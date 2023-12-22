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

version = "g-1.0"

file_empty = """
#include "ks.h"

<func>

int main(void) {
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

    def clist2file(self, func: list, code: list) -> str:
        output = file_empty.replace("<code>", f"\n{' '*4}".join(code)).replace("<func>", "\n".join(func))[1:]
        while "\n\n\n" in output:
            output = output.replace("\n\n\n", "\n\n")
        return output

    def convert_to_c(self, ast: dict, first: bool = False) -> str:
        self.debug_print("convert_to_c", f"{ast}", 3)
        out = ""

        if ast["type"] == "func":
            out += f"f_{ast['cnt']}({len(ast['arg'])}, {', '.join(self.convert_to_c(e) for e in ast['arg']) if 'arg' in ast else ''}){';' if first else ''}"

        elif ast["type"] == "int":
            out += f"INTEGER_OBJ({ast['cnt']}){';' if first else ''}"

        elif ast["type"] == "string":
            out += f"STRING_OBJ({ast['cnt']}){';' if first else ''}"

        else:
            print(f"ERROR: unknown type '{ast['type']}'")


        self.debug_print("convert_to_c", f"{out}", 3)
        return out

    def run(self) -> list:
        code = []
        for dico in self.inp:
            code.append(self.convert_to_c(dico, True))

        return code
