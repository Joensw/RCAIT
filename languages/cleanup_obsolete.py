# -*- coding: utf-8 -*-
# Check imports
try:
    import xml.etree.ElementTree

    import sys
    from ftfy import fix_encoding
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)

if __name__ == "__main__":

    filename = sys.argv[1][:-3]
    import xml.etree.ElementTree as ET

    with open(filename + ".ts", "rt", encoding="utf-8") as xml_file:
        parser = xml.etree.ElementTree.XMLParser(encoding="unicode")
        tree = ET.parse(xml_file, parser=parser)

    root = tree.getroot()

    print("INPUT MODE")

    for context in root.findall('context'):
        for msg in context.findall('message'):
            for translation in msg.findall("translation/[@type='obsolete']"):
                context.remove(msg)
            for translation in msg.findall("translation/[@type='vanished']"):
                context.remove(msg)
            for translation in msg.findall("translation"):
                if translation.text:
                    translation.text = fix_encoding(translation.text)
        tree.write(filename + ".ts", encoding='UTF-8', xml_declaration=True)

    input("Press Enter to continue...")
