import sys
import time
import subprocess

from challenges.scaffold import Scaffold


class Runner:
    def __init__(self, conf):
        self.start = time.time()
        self.conf = conf
        conf.parse_arguments()

    def main(self):
        if self.conf.args.list:
            self.list_challenges()
        elif self.conf.args.clean:
            self.clean()
        elif self.conf.args.build:
            if self.conf.args.challenge:
                self.build_challenge_and_test()
            else:
                self.build_all()
        elif self.conf.args.unittest:
            if self.conf.args.challenge:
                self.run_unittest()
            else:
                self.conf.print_help()
        elif self.conf.args.tests:
            self.run_all_tests()
        elif self.conf.args.scaffold:
            if self.conf.args.challenge:
                Scaffold(self.conf).scaffold()
                self.reload_cmake()
                self.build_challenge_and_test()
                self.run_unittest()
            else:
                self.conf.print_help()
        elif self.conf.args.challenge:
            self.run_challenge()
            if self.conf.args.verbose:
                print("--- Time: %s ---" % str(time.time() - self.start))
        else:
            self.conf.print_help()

    def read_file(self):
        with open(self.conf.get_input_file(), 'r') as pointer:
            sample = pointer.read()
        return sample

    def list_challenges(self):
        print(' * ' + '\n * '.join(self.conf.get_challenges()))

    def run_unittest(self):
        popen = subprocess.Popen(self.conf.get_test_bin(),
                                 stdout=subprocess.PIPE,
                                 universal_newlines=True,
                                 bufsize=1)
        popen.wait()
        print(popen.stdout.read())

    def run_challenge(self):
        sample = ""
        if self.conf.args.file:
            sample = self.read_file()
        if not sample:
            self.conf.print_help()
        else:
            pipe = subprocess.Popen(self.conf.get_bin(),
                                    stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE,
                                    universal_newlines=True,
                                    bufsize=1)
            result = pipe.communicate(input=sample)[0]
            pipe.stdin.close()
            pipe.stdout.close()
            print(result)
            self.write(sample, result)

    def reload_cmake(self):
        subprocess.call(['cmake', self.conf.build])

    def write(self, sample, result):
        with open(self.conf.get_latest_file(), 'w') as pointer:
            pointer.write(result)
        with open(self.conf.get_latest_at_root(), 'w') as pointer:
            pointer.write(result)
        if self.conf.args.write:
            with open(self.conf.get_sample_file(), 'w') as pointer:
                pointer.write(sample)
            with open(self.conf.get_result_file(), 'w') as pointer:
                pointer.write(result)

    def clean(self):
        subprocess.call(['make', 'clean'], cwd=self.conf.build)

    def build_challenge_and_test(self):
        subprocess.call(['make', self.conf.get_test_target()],
                        cwd=self.conf.build)

    def build_all(self):
        subprocess.call(['make'], cwd=self.conf.build)

    def run_all_tests(self):
        self.build_all()
        subprocess.call(['make', 'test'], cwd=self.conf.build)

