# https://www.linuxtopia.org/online_books/programming_books/python_programming/python_ch16s03.html
from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    first_line = set(a.split('\n'))
    second_line = set(b.split('\n'))

    """Contexto en la primera línea"""
    return first_line & second_line


def sentences(a, b):
    """Return sentences in both a and b"""

    a_sentences = set(sent_tokenize(a))
    b_sentences = set(sent_tokenize(b))

    return a_sentences & b_sentences


def subs(str, n):
    lista = []

    for i in range(len(str) - n + 1):
        lista.append(str[i:i+n])

    return set(lista)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    substring_a = subs(a, n)
    substring_b = subs(b, n)
    return substring_a & substring_b