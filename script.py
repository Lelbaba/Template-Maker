import os
Base = './Codes/'
def ProcessFile(f, name, W):
    W.write("\\begin{lstlisting}\n")
    with open(f) as CPP:
        for lines in CPP:
            W.write(lines)
    W.write("\\end{lstlisting}\n")
def ProcessDir(dir,name,depth, W):
    for subdir in reversed(os.listdir(dir)):
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
s = ""
with open('out.tex', 'w') as W:
    with open("start.tex") as F:
        for line in F:
            W.write(line)

    ProcessDir(Base, '', 0, W)
    with open("end.tex") as F:
        for line in F:
            W.write(line)
