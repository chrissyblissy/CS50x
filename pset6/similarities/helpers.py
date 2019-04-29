#in directory $ flask run
from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    lines = []

    list_a = a.splitlines()
    list_b = b.splitlines()

    for itema in list_a:
        for itemb in list_b:
            if itema not in lines:
                if itema == itemb:
                    lines.append(itema)

    return lines


def sentences(a, b):
    """Return sentences in both a and b"""
    sentences = []

    list_a = sent_tokenize(a)
    list_b = sent_tokenize(b)
    for itema in list_a:
        for itemb in list_b:
            if itema not in sentences:
                if itema == itemb:
                    sentences.append(itema)

    return sentences

def get_substring(string, n):
    substring = []
    for i, char in enumerate(string):
        substring.append(string[i:i+n])
        if i == (len(string) - n):
            return substring


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substrings = []
    if n > len(a) or n > len(b):
        return substrings
    list_a = get_substring(a, n)
    list_b = get_substring(b, n)

    for itema in list_a:
        for itemb in list_b:
            if itema not in substrings:
                if itema == itemb:
                    substrings.append(itema)

    return substrings

