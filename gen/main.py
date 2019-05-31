# coding=utf-8
from core import Generator

if __name__ == '__main__':
    with open('content.tex', 'w', encoding='utf-8') as f:
        f.write(Generator().populate())
