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

version = "l-1.6"

class Lexer:

    # TODO: support for comments
    
    def __init__(self, file: str, debug_lvl: int = 0) -> None:
        self.brut = file
        self.debug_lvl = debug_lvl
        self.op = "+-*/=!%"
        self.keywords = ["LOOP", "IF", "END", "BREAK", "FUNC", "RETURN", "WHILE", "ELSE", "CONTINUE"]


    def debug_print(self, func_name: str, text: str, level: int) -> None:
        if self.debug_lvl >= level:
            print(f"LXR - {level}| {func_name} : {text}")


    def get_type(self, cde: str) -> dict:
        dico = {
            "type": "func",
            "cnt": cde,
        }


        if cde[0] == cde[-1] and cde[0] in ["\"", "'"]:
            dico["type"] = "string"

        elif cde in self.keywords:
            dico["type"] = "keyword"

        elif cde in {"True", "False", "true", "false"}:
            dico["type"] = "bool"

        elif all(char in "0123456789" for char in cde):
            dico["type"] = "int"

        elif all(char in "0123456789." for char in cde):
            dico["type"] = "float"

        elif all(char in self.op for char in cde):
            dico["type"] = "op"

        elif cde[0] == "$":
            dico["type"] = "var"

        return dico

    def cut_operators(self, cde: str) -> list:
        out = []
        temp = ""
        in_string, in_op = False, False
        for char in cde:
            self.debug_print("cut_operators", f"{temp}.{char} in_string={in_string} in_op={in_op}", 3)
            if char in ["\"", "'"]:
                in_string = not in_string
            if in_string:
                if in_op:
                    in_op = False
                    out.append(self.get_type(temp))
                    temp = ""
                temp += char
                continue
            if char in self.op:
                if not in_op:
                    if temp: out.append(self.get_type(temp))
                    temp, in_op = "", True
            elif in_op:
                in_op = False
                out.append(self.get_type(temp))
                temp = ""
            temp += char
        if temp: out.append(self.get_type(temp))
        self.debug_print("cut_operators", f"{out}", 2)
        return out

    def analyse(self, edit: str) -> dict:
        self.debug_print("analyse", f"{edit}", 2)
        dico = {
            "iph": 0,
            "oph": 0,
            "cde": "",
        }
        is_in = 1
        for car in edit:
            if car == ">":
                dico["iph" if is_in else "oph"] += 1
            else:
                dico["cde"] += car
                is_in = 0

        dico["cde"] = [self.cut_operators(e) for e in dico["cde"].split(",") if e]
        self.debug_print("analyse", f"{dico}", 2)
        return dico


    def split_push(self, e: str) -> list:
        sortie = []
        in_string = False
        in_push = False
        code_to_analyse = ""
        for car in e:
            self.debug_print("split_push", f"{code_to_analyse}.{car} in_string={in_string} in_push={in_push}", 3)
            if car in ["\"", "'"]:
                in_string = not in_string
            if in_string:
                code_to_analyse += car
                continue
            if car == ">":
                in_push = True
            if in_push and car != ">":
                if sum(c != ">" for c in code_to_analyse):
                    sortie.append(self.analyse(code_to_analyse))
                    code_to_analyse = code_to_analyse[-sortie[-1]["oph"]:]

                in_push = False
            code_to_analyse += car

        sortie.append(self.analyse(code_to_analyse))
        self.debug_print("split_push", f"{sortie}", 2)
        return sortie

    def sup_space(self, e: str) -> str:
        # removing spaces and handling line breaks
        in_string = False
        out = ""
        for car in e:
            if car in ["\"", "'"]:
                in_string = not in_string
            if not in_string and car == " ":
                continue
            out += car

        out = out.replace("\n", ";").replace("\t", "")
        self.debug_print("sup_space", f"{out}", 2)
        while ";;" in out:
            out = out.replace(";;", ";")

        return out.replace("?;", "").split(";")

    def remove_empty(self, e: list) -> list:
        for l in e:
            if len(l) == 1 and not (l[0]["iph"] + l[0]["oph"] + len(l[0]["cde"])):
                e.remove(l)
        return e

    def run(self) -> list:
        seg = self.sup_space(self.brut)
        self.debug_print("run", f"{seg}", 1)
        out = []
        
        for e in seg:
            self.debug_print("run (lexing)", f"{e}", 2)
            tmp = self.split_push(e)
            out.append(tmp)

        out = self.remove_empty(out)

        self.debug_print("run (out)", f"{out}", 1)
        return out
