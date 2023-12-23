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

import core.tools as tools

version = "g-1.1"

file_empty = """
#include "ks.h"

<vars>

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
                "<vars>", ("/*" + "\n".join(f"\n{k}\n" + "\n".join(
                    f'  {x}: {i}' for i, x in enumerate(e)
                ) for k, e in self.vars.items())) + "\n*/" if self.vars else ""
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
                out += f"fi_clean_obj(f_{ast['cnt']}({len(ast['arg'])}, {', '.join(self.convert_to_c(e, func = func) for e in ast['arg']) if 'arg' in ast else ''}));" if 'arg' in ast else f"fi_clean_obj(f_{ast['cnt']}(0));"
            else:
                out += f"f_{ast['cnt']}({len(ast['arg'])}, {', '.join(self.convert_to_c(e, func = func) for e in ast['arg']) if 'arg' in ast else ''})" if 'arg' in ast else f"f_{ast['cnt']}(0)"

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
                tools.raise_error(f"keyword '{ast['cnt']}' not at the beginning of a line")
            elif ast["cnt"] == "IF":
                out += f"if (fi_is({self.convert_to_c(ast['arg'][0], func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "ELSE":
                out += f"else" + "{\n"
                self.indent += 1
            elif ast["cnt"] == "WHILE":
                out += f"while (fi_is({self.convert_to_c(ast['arg'][0], func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "LOOP":
                out += f"for (int i = fi_int_val({self.convert_to_c(ast['arg'][0], func = func)}); i > 0; i--)" + " {"
                self.indent += 1
            elif ast["cnt"] == "END":
                if not self.indent:
                    tools.raise_error("find 'end' but no block to close")
                else:
                    self.indent -= 1
                    out = out[:-4] + "}"
            elif ast["cnt"] == "BREAK":
                out += "break;"
            elif ast["cnt"] == "CONTINUE":
                out += "continue;"
            else:
                tools.raise_error(f"unknown keyword '{ast['cnt']}'")

        else:
            tools.raise_error(f"unknown type '{ast['type']}'")

        self.debug_print("convert_to_c", f"{out}", 3)
        return out

    def run(self) -> list:
        for dico in self.inp:
            self.generated.append(self.convert_to_c(dico, True))
        self.debug_print("run", f"vars: {self.vars}", 1)
