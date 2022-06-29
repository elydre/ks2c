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


version = "p-1.6"

class Parser:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl

        self.CONVERT_TABLE = {
            "**": "pow",
            "%":  "mod",
            "*":  "mul",
            "/":  "edv",
            "+":  "add",
            "-":  "sub",
            "==": "eql",
            "!=": "neq",
            "+=": "sup",
            "-=": "inf",
            "!":  "not",
        }

        self.PRIORITY = {
            "**": 1,
            "%":  2,
            "*":  2,
            "/":  2,
            "+":  3,
            "-":  3,
            "==": 4,
            "!=": 4,
            "+=": 4,
            "-=": 4,
            "!":  5,
        }


    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"PSR - {level}| {fonc_name} : {text}")


    def get_best_op(self, inp):
        get_priority = lambda x: self.PRIORITY[x]
        best_priority = 0
        best_index = 0
        for i in range(len(inp)):
            if inp[i]["type"] == "op" and get_priority(inp[i]["cnt"]) > best_priority:
                best_priority = get_priority(inp[i]["cnt"])
                best_index = i
    
        self.debug_print("get_best_op", f"{inp} => {best_index}", 3)
        return best_index

    def ast_parse(self, inp: list) -> dict:
        if len(inp) == 1:
            return inp[0]
    
        best_index = self.get_best_op(inp)

        out = {
            "type": "func",
            "cnt": self.CONVERT_TABLE[inp[best_index]["cnt"]],
            "arg": [
                self.ast_parse(inp[:best_index]),
                self.ast_parse(inp[best_index + 1:])
            ] if len(inp) > 2 else [self.ast_parse([inp[not best_index]])]
        }
        
        self.debug_print("ast_parse", out, 2)
        return out

    def parse_merge(self, old: list, out: list) -> list:
        if not old:
            return out

        for i in range(len(old)):
            r = len(old) // len(out)
            j = i // r if r else 0
            j = j if j < len(out) else len(out) - 1
            self.debug_print("parse_merge", f"{i}//{r} => {j}", 3)
            if "arg" not in out[j]:
                out[j]["arg"] = []
            out[j]["arg"].append(old[i])

        return out

    def parse_line(self, line: list) -> list:

        out, sortie, old = [], [], []

        self.debug_print("parse_line", line, 2)
        
        for dico in line:
            for elm in dico["cde"]:
                out.append(self.ast_parse(elm))

            self.debug_print("parse_line", f"merge de: {old}", 3)
            self.debug_print("parse_line", f"avec: {out}", 3)

            out = self.parse_merge(old, out)

            self.debug_print("parse_line", f"fin du merge: {out}", 2)

            for i in range(len(out)):
                if out[i]["type"] == "var":
                    self.debug_print("parse_line", f"var: {out[i]}", 3)
                    sortie.append(eval(str(out[i])))
                    if "arg" in out[i].keys():
                        del out[i]["arg"]

            old, out = out, []

        sortie.extend(old)

        while any(sortie[i]["type"] == "var" and "arg" not in sortie[i].keys() for i in range(len(sortie))):
            for i in range(len(sortie)):
                if sortie[i]["type"] == "var" and "arg" not in sortie[i].keys():
                    del sortie[i]
                    break

        return sortie


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
    
        self.debug_print("run", "ckeck passed!", 1)

        for line in self.inp:
            out.extend(self.parse_line(line))

        self.debug_print("run", out, 1)
        return out
