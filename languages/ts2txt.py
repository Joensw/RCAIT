# -*- coding: utf-8 -*-
import sys
import codecs

if __name__ == '__main__':
    
    filename = sys.argv[1][:-3]
    import xml.etree.ElementTree as ET

    with open(filename+".ts", 'r') as xml_file:
        tree = ET.parse(xml_file)

    root = tree.getroot()

    outF = codecs.open(filename+".txt", 'w', 'utf-8')

    print("OUTPUT MODE")
    for msg in root.iter('message'):
        for translation in msg.findall("translation/[@type='unfinished']"):
            if not translation.text:
                result = msg.find("source").text
                result = result.replace("\n", "\\n")
                print(result)
                outF.write(result)
                outF.write("\n")

    outF.close()
    input("Press Enter to continue...")
