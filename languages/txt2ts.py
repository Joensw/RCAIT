# -*- coding: utf-8 -*-
import sys
import xml.etree.ElementTree

from ftfy import fix_encoding

if __name__ == "__main__":
    import codecs

    filename = sys.argv[1][:-4]
    import xml.etree.ElementTree as ET

    with open(filename + ".ts", 'r') as xml_file:
        parser = xml.etree.ElementTree.XMLParser(encoding="utf-8")
        tree = ET.parse(xml_file, parser=parser)

    root = tree.getroot()
    inF = codecs.open(filename + ".txt", 'r', 'utf-8')

    print("INPUT MODE")

    line = 0
    lines = inF.readlines()

    for msg in root.iter('message'):
        for translation in msg.findall("translation/[@type='unfinished']"):
            if not translation.text:
                translation.attrib.pop('type')
                translation.text = fix_encoding(lines[line].replace("\\n", "\n").rstrip())
                line = line + 1
                print(translation.text)
        for translation in msg.findall("translation"):
            translation.text = fix_encoding(translation.text)
    tree.write(filename + ".ts", encoding='UTF-8')

    inF.close()
    input("Press Enter to continue...")
