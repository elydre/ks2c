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

from mod.segmenteur import launch_segmenter as segmenter

version = "l-1.2"

class Lexer:

    # TODO:
    # - verifier si le nombre de push est correct
    # - améliorer le debug, plusieur niveaux de debug
    # - gestion des commentaires
    
    def __init__(self, file: str, debug: bool = False) -> None:
        self.brut = file
        self.debug = debug
        self.op = "+-*/^=!"

    
    def get_type(self, cde: str) -> dict:
        dico = {
            "type": "func",
            "cnt": cde,
        }

        if cde[0] == cde[-1] and cde[0] in ["\"", "'"]:
            dico["type"] = "string"

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
        for car in cde:
            if car in ["\"", "'"]:
                in_string = not in_string
            if in_string:
                temp += car
                continue
            if car in self.op:
                if not in_op:
                    out.append(self.get_type(temp))
                    temp, in_op = "", True
            elif in_op:
                in_op = False
                out.append(self.get_type(temp))
                temp = ""
            temp += car
        out.append(self.get_type(temp))
        return out

    def analyse(self, edit: str) -> dict:
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

        dico["cde"] = [self.cut_operators(e) for e in dico["cde"].split(",")]

        return dico


    def split_push(self, e: str) -> list:
        sortie = []
        in_string = False
        in_push = False
        code_to_analyse = ""
        for car in e:
            if car in ["\"", "'"]:
                in_string = not in_string
            if in_string:
                code_to_analyse += car
                continue
            if car == ">":
                in_push = True
            if in_push and car != ">":
                sortie.append(self.analyse(code_to_analyse))
                code_to_analyse = code_to_analyse[-sortie[-1]["oph"]:]
                in_push = False
            code_to_analyse += car

        sortie.append(self.analyse(code_to_analyse))
        return sortie


    def lexing(self, seg: list) -> list:
        sortie = []
        for e in seg:
            if type(e) == list:
                sortie.append(self.lexing(e))
            else:
                sortie.extend(self.split_push(e))
        return sortie


    def sup_space(self, e: str) -> str:
        # supression des espaces et gestion des sauts de ligne
        in_string = False
        out = ""
        for car in e:
            if car in ["\"", "'"]:
                in_string = not in_string
            if not in_string and car == " ":
                continue
            out += car

        out = out.replace("\n", ";").replace("\t", "")
        if self.debug: print(out)
        while ";;" in out:
            out = out.replace(";;", ";")

        return out.replace("?;", "").split(";")


    def run(self) -> list:
        seg = self.sup_space(self.brut)
        if self.debug: print(seg)
        out = []
        for e in seg:
            tmp = segmenter(e)
            if self.debug: print(tmp)
            tmp = self.lexing(tmp)
            if self.debug: print(tmp)
            out.append(tmp)

        if self.debug: print(out)
        return out