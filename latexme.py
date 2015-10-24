import sys
import os
from collections import namedtuple, defaultdict

CODE_DIR = 'code'

Sections = defaultdict(lambda : 'Other',
                       {
                           'graphs' : 'Graph',
                           'binary-search' : 'Binary Search',
                           'disjoint-set' : 'Disjoint Set',
                           'c++11' : 'C++11 Features',
                           'fenwick' : 'Fenwick',
                           'geometry' : 'Geometry',
                           'math' : 'Math',
                           'string' : 'String',
                       })

FileTypes = {
    'cpp' : 'C++',
    'md' : 'Markdown',
    'java' : 'Java',
    'py' : 'Python',
}

def is_code(code):
    return code.filetype in 'C++', 'Java', 'Python'

def latexify(text):
    return text.replace('_', r'\_').replace('[', r'\lbrack ').replace(
        ']', r'\rbrack ')

Entry = namedtuple('Entry', ['filename', 'text', 'filetype', 
                             'section', 'path'])

def append(collection, item):
    collection.append(item)

def recursive_collect(collection, directory):
    for fname in os.listdir(directory):
        path = os.path.join(directory, fname)
        if os.path.isdir(path):
            if not path.endswith('test'):
                recursive_collect(collection, path)

        elif os.path.isfile(path):
            with open(path, 'r') as f:
                content = [latexify(line) for line in f.readlines()]

            def first_match(dictionary, string):
                for key in dictionary:
                    if string.endswith(key):
                        return dictionary[key]
                return None

            filetype = first_match(FileTypes, fname)
            section = first_match(Sections, directory)
            append(collection, Entry(
                latexify(fname), content, latexify(filetype), 
                latexify(section), path))


header = r"""\title{A Competitive Programming Cheat Sheet}

\documentclass[landscape]{article}

\usepackage{listings}
\usepackage[landscape]{geometry}
\usepackage[usenames,dvipsnames]{color}

\definecolor{DarkGreen}{rgb}{0.0,0.4,0.0} % Comment color
\definecolor{highlight}{RGB}{255,251,204} % Code highlight color
\definecolor{light-gray}{gray}{0.85}
\lstset{
language=C++,
basicstyle=\footnotesize,
backgroundcolor=\color{light-gray}
}
\begin{document}
\maketitle

"""

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("'python3 latexme.py filename' needs to be run")
        exit(1)
    entries = []
    recursive_collect(entries, CODE_DIR)
    entries.sort(key=lambda x: x.section or "ZZZ")
    last_section = "TheCoolestPlaceholderAlive"
    sections = ""
    for entry in entries:
        if entry.section != last_section:
            sections += r"\clearpage" + "\n"
            sections += r"\section{" + entry.section + "}\n\n"
        if is_code(entry):
            sections += r'\subsection{' + entry.filename + '}\n'
            sections += r'\lstinputlisting{"' + entry.path + '"}\n\n'
        
        last_section = entry.section
    sections += r"\end{document}" + "\n"
    full_text = header + sections
    with open(sys.argv[1], 'w') as f:
        print(full_text, file=f)
            
    
