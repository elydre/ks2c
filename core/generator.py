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

file_empty = """
#include "ks.h"

<vars>

<func>

int main(void) {
    vars_t local_vars = {NULL, 0};
    <vdef>
    <code>
    fi_clean_up(&local_vars);
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
        self.max_lvl = 0
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"GEN - {level}| {fonc_name} : {text}")

    def clist2file(self) -> str:
        output = file_empty.replace(
                "<code>", f"\n{' '*4}".join(self.generated)
            ).replace("<func>", "\n".join([])).replace(
                "<vars>", ("/*" + "\n".join(f"\n{k}\n" + "\n".join(
                    f'  \"{x}\": {i}' for i, x in enumerate(e)
                ) for k, e in self.vars.items())) + "\n*/" if self.vars else ""
            )[1:].replace("<vdef>", "fast_t " + ", ".join(f"a{i},b{i}" for i in range(self.max_lvl)) + ";")

        while "\n\n\n" in output:
            output = output.replace("\n\n\n", "\n\n")
        return output

    def convert_to_c(self, ast: dict, lvl: int = 0, func: str = "main") -> str:
        self.debug_print("convert_to_c", f"{ast}", 3)

        if lvl > self.max_lvl:
            self.max_lvl = lvl

        if lvl:
            out = ""
        else:
            out = " " * self.indent * 4

        if ast["type"] == "func":
            if lvl:
                out += f"f_{ast['cnt']}({lvl}, {len(ast['arg'])}, {', '.join(self.convert_to_c(e, lvl + 1, func = func) for e in ast['arg']) if 'arg' in ast else ''})" if 'arg' in ast else f"f_{ast['cnt']}(0)"
            else:
                out += f"fi_clean_obj(f_{ast['cnt']}({lvl}, {len(ast['arg'])}, {', '.join(self.convert_to_c(e, lvl + 1, func = func) for e in ast['arg']) if 'arg' in ast else ''}));" if 'arg' in ast else f"fi_clean_obj(f_{ast['cnt']}(0));"

        elif ast["type"] == "int":
            if lvl:
                out += f"fi_new_integer_obj({ast['cnt']})"
            else:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 1)

        elif ast["type"] == "string":
            if lvl:
                out += f"fi_new_string_obj({ast['cnt']})"
            else:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 1)

        elif ast["type"] == "float":
            if lvl:
                out += f"fi_new_float_obj({ast['cnt']})"
            else:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 1)

        elif ast["type"] == "bool":
            if lvl:
                out += f"fi_new_boolean_obj({1 if ast['cnt'] == 'true' else 0})"
            else:
                self.debug_print("convert_to_c", f"deleting unused object {ast['cnt']}", 1)

        elif ast["type"] == "var":
            if not func in self.vars.keys():
                self.vars[func] = []
            if not ast["cnt"][1:] in self.vars[func]:
                self.vars[func].append(ast["cnt"][1:])
            var_index = self.vars[func].index(ast["cnt"][1:])

            if lvl:
                out += f"fi_get_var(&local_vars, {var_index})"
            else:
                if ast['arg'][0]['type'] == "keyword" and ast['arg'][0]['cnt'] == "LOOP":
                    out = self.convert_to_c(ast['arg'][0], func = func)
                    out += "\n" + " " * (self.indent + 1) * 4
                    out += f"fi_set_var(&local_vars, {var_index}, fi_new_integer_obj(i));"
                else:
                    out += f"fi_set_var(&local_vars, {var_index}, {self.convert_to_c(ast['arg'][0], lvl + 1, func = func)});"

        elif ast["type"] == "keyword":
            if lvl:
                tools.raise_error(f"keyword '{ast['cnt']}' not at the beginning of a line")
            elif ast["cnt"] == "IF":
                out += f"if (fi_is({self.convert_to_c(ast['arg'][0], lvl + 1, func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "ELSE":
                out += f"else" + " {"
                self.indent += 1
            elif ast["cnt"] == "WHILE":
                out += f"while (fi_is({self.convert_to_c(ast['arg'][0], lvl + 1, func = func)}))" + " {"
                self.indent += 1
            elif ast["cnt"] == "LOOP":
                out += f"for (int i = 0, max = fi_int_val({self.convert_to_c(ast['arg'][0], lvl + 1, func = func)}); i < max; i++)" + " {"
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
            self.generated.append(self.convert_to_c(dico))
        self.debug_print("run", f"vars: {self.vars}", 1)
