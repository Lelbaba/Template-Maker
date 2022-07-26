import os
Base = './Codes/'
def ProcessFile(f, name, W):
    if f.endswith((".txt", ".cpp")):
        W.write("\\begin{lstlisting}\n")
        with open(f) as CPP:
            for lines in CPP:
                W.write(lines)
        W.write("\\end{lstlisting}\n")

def ProcessDir(dir, name, depth, W):
    for subdir in sorted(os.listdir(dir)):
        if subdir == 'desktop.ini':
            continue
        s = '\\'
        for i in range(depth):
            s += 'sub'
        s += 'section{'
        s += os.path.splitext(subdir)[0]
        s += '}\n'
        W.write(s)
        pth = os.path.join(dir, subdir)
        if os.path.isfile(pth):
            ProcessFile(pth, subdir, W)
        else : 
            ProcessDir(pth, subdir, depth + 1, W)

print("Enter Team Name")
team = input()
print("Enter Uni Name")
uni = input()
print("Enter Number of Columns")
cols = input()
print("Which Orientation Do You Want?\n1. Portrait\n2. Landscape")
x = int(input())
ort = "portrait" if x == 1 else "landscape"
print("What font size?\n1. 10\n2. 11\n3. 12")
x = int(input())
fs = '10'
if x == 2: fs = '11'
if x == 3: fs = '12'


s = ""
with open('out.tex', 'w') as W:
    W.write('\\newcommand\\TEAM{' + team + '}\n')
    W.write('\\newcommand\\UNI{' + uni + '}\n')
    W.write('\\newcommand\\COLS{' + cols + '}\n')
    W.write('\\newcommand\\ORT{' + ort + '}\n')
    W.write('\\newcommand\\FSZ{' + fs + '}\n')
    with open("start.tex") as F:
        for line in F:
            W.write(line)

    ProcessDir(Base, '', 0, W)
    with open("end.tex") as F:
        for line in F:
            W.write(line)
