# Check imports
try:
    import argparse
    import json
    import os
    from difflibparser import *
    
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)


def file_path(string):
    if os.path.isfile(string):
        return string
    else:
        raise FileNotFoundError(string)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Builds a JSON parsable diff from two files')
    parser.add_argument('file1', metavar='file1', type=file_path, help='First file')
    parser.add_argument('file2', metavar='file2', type=file_path, help='Second file')

    args = parser.parse_args()
    file1 = open(args.file1, 'r')
    file2 = open(args.file2, 'r')
    file1_content = file1.read()
    file2_content = file2.read()

    differ = DifflibParser(file1_content.splitlines(), file2_content.splitlines())

    for line in differ:
        print(json.dumps(line))
