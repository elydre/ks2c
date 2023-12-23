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

/*
<vars>
*/

<func>

int main(void) {
    <code>
    fi_clean_up();
    return 0;
}
"""

class Generator:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl
        self.vars = {}
        self.generated = []
        self.indent = 0
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"GEN - {level}| {fonc_name} : {text}")

    def clist2file(self) -> str:
        output = file_empty.replace(
                "<code>", f"\n{' '*4}".join(self.generated)
            ).replace("<func>", "\n".join([])).replace(
                "<vars>", "\n".join(k + '\n' + '\n'.join(
                    f'  {x}: {i}' for i, x in enumerate(e)
                ) for k, e in self.vars.items())
            )[1:]

        while "\n\n\n" in output:
            output = output.replace("\n\n\n", "\n\n")
        return output

    def convert_to_c(self, ast: dict, first: bool = False, func: str = "main") -> str:
        self.debug_print("convert_to_c", f"{ast}", 3)

        if first:
            out = " " * self.indent * 4
        else:
            out = ""

        if ast["type"] == "func":
            if first:
                out += f"fi_clean_obj(f_{ast['cnt']}({len(ast['arg'])}, {', '.join(self.convert_to_c(e, func = func) for e in ast['arg']) if 'arg' in ast else ''}));"
            else:
                out += f"f_{ast['cnt']}({len(ast['arg'])}, {', '.join(self.convert_to_c(e, func = func) for e in ast['arg']) if 'arg' in ast else ''})"

        elif ast["type"] == "int":
            if first:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 3)
            else:
                out += f"INTEGER_OBJ({ast['cnt']})"

        elif ast["type"] == "string":
            if first:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 3)
            else:
                out += f"STRING_OBJ({ast['cnt']})"
        
        elif ast["type"] == "float":
            if first:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 3)
            else:
                out += f"FLOAT_OBJ({ast['cnt']})"

        elif ast["type"] == "bool":
            if first:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 3)
            else:
                out += f"BOOLEAN_OBJ({1 if ast['cnt'] == 'true' else 0})"

        elif ast["type"] == "var":
            if not func in self.vars.keys():
                self.vars[func] = []
            if not ast["cnt"][1:] in self.vars[func]:
                self.vars[func].append(ast["cnt"][1:])
            var_index = self.vars[func].index(ast["cnt"][1:])
            func_index = list(self.vars.keys()).index(func)

            if first:
                out += f"fi_create_var({func_index}, {var_index}, {self.convert_to_c(ast['arg'][0], func = func)});"
            else:
                out += f"fi_get_var({func_index}, {var_index})"

        elif ast["type"] == "keyword":
            if not first:
                self.debug_print("convert_to_c", f"error: keyword '{ast['cnt']}' not at the beginning of a line", 0)
            elif ast["cnt"] == "IF":
                out += f"if (fi_is({self.convert_to_c(ast['arg'][0], func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "ELSE":
                out += f"else" + "{\n"
                self.indent += 1
            elif ast["cnt"] == "WHILE":
                out += f"while (fi_is({self.convert_to_c(ast['arg'][0], func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "END":
                if not self.indent:
                    self.debug_print("convert_to_c", f"error: nothing to end", 0)
                else:
                    self.indent -= 1
                    out = out[:-4] + "}"
            elif ast["cnt"] == "BREAK":
                out += "break;\n"
            else:
                self.debug_print("convert_to_c", f"ERROR: unknown keyword '{ast['cnt']}'", 0)

        else:
            print(f"ERROR: unknown type '{ast['type']}'")

        self.debug_print("convert_to_c", f"{out}", 3)
        return out

    def run(self) -> list:
        for dico in self.inp:
            self.generated.append(self.convert_to_c(dico, True))
        self.debug_print("run", f"vars: {self.vars}", 1)
