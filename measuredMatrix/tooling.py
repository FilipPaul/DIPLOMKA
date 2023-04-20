from typing import List
class Tooling():
    def __init__(self, Length):
        self.Length = Length

with open("original_files/summary", "r") as f:
    tooling = f.read()

while("  " in tooling):
    tooling = tooling.replace("  ", " ")