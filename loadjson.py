import json



with open('ftech.json', 'r') as vu:
    content = json.load(vu)
print(content)