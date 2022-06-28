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


version = "p-1.3"

class Parser:
    def __init__(self, inp: list, debug_lvl: int = 0) -> None:
        self.inp = inp
        self.debug_lvl = debug_lvl

        self.CONVERT_TABLE = {
            "**": "pow",
            "*":  "mul",
            "/":  "div",
            "+":  "add",
            "-":  "sub",
            "==": "eql",
            "!=": "neq",
            "+=": "sup",
            "-=": "inf",
            "!":  "not",
        }

        self.PRIORITY = {
            "**": 5,
            "*":  4,
            "/":  4,
            "+":  3,
            "-":  3,
            "==": 2,
            "!=": 2,
            "+=": 2,
            "-=": 2,
            "!":  1,
        }
    
    def debug_print(self, fonc_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"PSR - {level}| {fonc_name} : {text}")


    def get_index_best_priority(self, inp):
        get_priority = lambda x: self.PRIORITY[x]
        best_priority = 0
        best_index = 0
        for i in range(len(inp)):
            if inp[i]["type"] == "op" and get_priority(inp[i]["cnt"]) > best_priority:
                best_priority = get_priority(inp[i]["cnt"])
                best_index = i
        return best_index

    def ast_parse(self, inp: list) -> dict:
        if len(inp) == 1:
            return inp[0]
    
        best_index = self.get_index_best_priority(inp)
        out = {
            "type": "func",
            "cnt": self.CONVERT_TABLE[inp[best_index]["cnt"]],
            "args": [
                self.ast_parse(inp[:best_index]),
                self.ast_parse(inp[best_index + 1:])
            ]
        }
        self.debug_print("ast_parse", out, 2)
        return out

    def parse_merge(self, old: list, out: list) -> list:
        # TODO: debug
        if not old:
            return out
        if len(out) == 1:
            out[0]["arg"] = old
            return out
        if len(out) == len(old):
            for i in range(len(out)):
                out[i]["arg"] = old[i]
            return out
        print("ERROR: merge")
        

    def parse_line(self, line: list) -> list:
        # TODO: keywords

        out, sortie, old = [], [], []

        print(line)

        for dico in line:
            for elm in dico["cde"]:
                out.append(self.ast_parse(elm))

            print("besoin de merge:", old)
            print("avec:", out)
            print()

            out = self.parse_merge(old, out)

            print("apres merge:", out)
            print("\n")

            for i in range(len(out)):
                if out[i]["type"] == "var":
                    print("var:", out[i])
                    sortie.append(eval(str(out[i])))
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
