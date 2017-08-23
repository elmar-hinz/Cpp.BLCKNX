import argparse
import glob
import os
import sys


class Conf:
    def __init__(self):
        sys.path.insert(0, '.')
        sys.setrecursionlimit(15000)
        self.root = os.path.realpath('./Challenges/')
        self.build = os.path.realpath('./cmake-build-debug/')
        self.parser = None
        self.args = None
        version_path = '{0}/version.txt'.format(
            os.path.realpath(os.path.dirname(__file__)))
        with open(version_path) as f:
            self.version = f.read().strip()

    def parse_arguments(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument('challenge', nargs='?',
                                 help='the challenge to run, to scaffold or '
                                      'to test')
        self.parser.add_argument('-f', '--file', action='store',
                                 help='load sample from given file')
        self.parser.add_argument('-k', '--klass', action='store_true',
                                 help='use sample form challenge class file - Not implemented yet')
        self.parser.add_argument('-l', '--list', action='store_true',
                                 help='list challenges')
        self.parser.add_argument('-s', '--scaffold', action='store_true',
                                 help="scaffold challenge")
        self.parser.add_argument('-u', '--unittest', action='store_true',
                                 help='unittest challenge')
        self.parser.add_argument('-v', '--verbose', action='store_true',
                                 help='verbose output')
        self.parser.add_argument('-V', '--version', action='version',
                                 version='%(prog)s {}'.format(self.version))
        self.parser.add_argument('-w', '--write', action='store_true',
                                 help='write input and sample file into '
                                      'challenge directory')
        if len(sys.argv) == 1:
            self.print_help()
        self.args = self.parser.parse_args()
        if self.args.challenge and self.args.challenge[-1:] == '/':
            self.args.challenge = self.args.challenge[0:-1]

    def print_help(self):
        self.parser.print_help()
        sys.exit(1)

    def get_challenge_name(self):
        lower = self.args.challenge.lower()
        return lower[:1].upper() + lower[1:]

    def get_challenge_name_upper(self):
        return self.args.challenge.upper()

    def get_challenge_name_lower(self):
        return self.args.challenge.lower()

    def get_challenge_dir(self):
        return os.path.realpath(
            self.root + '/' + self.args.challenge.upper()
        )

    def get_input_file(self):
        return os.path.realpath(self.args.file)

    def get_main_file(self):
        return '{}/main.cpp'.format(
            self.get_challenge_dir()
        )

    def get_header_file(self):
        return '{}/{}.h'.format(
            self.get_challenge_dir(),
            self.get_challenge_name()
        )

    def get_class_file(self):
        return '{}/{}.cpp'.format(
            self.get_challenge_dir(),
            self.get_challenge_name()
        )

    def get_test_file(self):
        return '{}/{}Test.cpp'.format(
            self.get_challenge_dir(),
            self.get_challenge_name()
        )

    def get_sample_file(self):
        return '{}/sample.txt'.format(self.get_challenge_dir())

    def get_result_file(self):
        return '{}/result.txt'.format(self.get_challenge_dir())

    def get_latest_file(self):
        return '{}/latest.txt'.format(self.get_challenge_dir())

    def get_latest_at_root(self):
        return os.path.realpath(self.root + '/latest.txt')

    def get_challenges(self):
        pattern = self.root + '/*/'
        return [d for d in
                (os.path.basename(d[:-1]) for d in glob.glob(pattern))
                if d[0:1] == d[0:1].upper() and d[0:1] != '_']

    def get_test_bin(self):
        return '{}/{}_test'.format(
            self.build, self.get_challenge_name_lower())

    def get_bin(self):
        return '{}/{}'.format(
            self.build, self.get_challenge_name_lower())
