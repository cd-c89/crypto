import os

clean = lambda : os.system("rm unsafe* keygen rsainc *.txt 2>/dev/null")
get_m = lambda: open("m.txt", "w").write("A+")
flags = "--std=c89 -Wall -Wextra -Werror -Wpedantic -O2 -o"
ghurl = "https://raw.githubusercontent.com/cd-c89/crypto/refs/heads/main/"

clean()
os.system(f"curl {ghurl}rsainc/keygen.py -o keygen.py 2>/dev/null")
os.system(f"curl {ghurl}rsainc/rsa_py.py -o rsa_py.py 2>/dev/null")
os.system(f"gcc keygen.c {flags} keygen")
os.system(f"gcc rsainc.c {flags} rsainc")

def test_order(k, e, d):
    get_m()
    if k:
        os.system("./keygen")
    else:
        os.system("python3 keygen.py")
    lang = lambda e: os.system("./rsainc" + args) if e else os.system("python3 rsa_py.py" + args)
    args = " -e m.txt c.txt"
    lang(e)
    args = " -d c.txt n.txt"
    lang(d)
    os.system("cat n.txt; echo")

for i in range(8):
    test_order(i//4%2,i//2%2,i%2)