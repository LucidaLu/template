# coding=utf-8
import logging
import re
from pathlib import Path

import settings


class Generator(object):
    PATTERN = re.compile(r'^\w+?_(?P<name>.+?)(\.(?P<lang>\w+)){0,1}$')

    def __init__(self):
        self.content = []

    def populate(self, folder=None, depth=0):
        """
        输出文档内容
        :param folder: 模板根目录
        :param depth: 遍历深度
        :return: str
        """
        if folder is None:
            folder = Path('./src')

        # 如果folder内只有一个项目，则不输出子标题
        unique = False
        if len([i for i in folder.iterdir() if self.PATTERN.match(i.name)]) == 1:
            unique = True

        for item in folder.iterdir():
            match = self.PATTERN.search(item.name)

            if match is None:
                logging.warning('Unknown file skipped: %r' % item.absolute())
                continue

            name, lang = match.group('name'), match.group('lang')
            if not unique:
                self.populate_section(name, depth)
            if item.is_dir():
                self.populate(item, depth + 1 - unique)
            if item.is_file():
                self.populate_file(name, lang, item.as_posix(), depth + 1 - unique)

        return '\n'.join(self.content)

    def populate_section(self, caption, depth):
        """
        输出段落
        :param caption: 标题
        :param depth: 遍历深度
        :return: str
        """
        line = ''.join(['  ' * depth, '\\', 'sub' * depth, 'section{%s}' % caption])
        self.content.append(line)

    def populate_file(self, caption, suffix, path, depth):
        """
        输出文件
        :param caption: 标题
        :param suffix: 后缀名
        :param path: 相对路径
        :param depth: 遍历深度
        :return: list
        """
        if suffix.lower() in settings.INPUT_TYPE:
            line = ''.join(['  ' * depth, '\\input{%s}' % path])
            self.content.append(line)
        if suffix.lower() in settings.CODE_TYPE:
            line = ''.join(['  ' * depth, '\\inputminted{%s}{%s}' % (suffix, path)])
            self.content.append(line)
