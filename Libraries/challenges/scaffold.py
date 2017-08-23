from datetime import datetime
import os
import sys


class Scaffold:
    def __init__(self, conf):
        self.conf = conf

    def scaffold(self):
        directory = self.conf.get_challenge_dir()
        if os.path.exists(directory):
            sys.exit('Directory ' + directory + ' already exists.')
        else:
            try:
                os.makedirs(directory)
            except OSError:
                sys.exit('Sorry, could not create ' + directory + '.')

        # main.cpp
        file = self.conf.get_main_file()
        if os.path.exists(file):
            sys.exit('File ' + file + ' already exists.')
        else:
            try:
                with open(file, 'w') as handle:
                    handle.write(self.get_main_content())
            except OSError:
                sys.exit('Sorry, could not write ' + file + '.')

        # Challenge.h
        file = self.conf.get_header_file()
        if os.path.exists(file):
            sys.exit('File ' + file + ' already exists.')
        else:
            try:
                with open(file, 'w') as handle:
                    handle.write(self.get_header_content())
            except OSError:
                sys.exit('Sorry, could not write ' + file + '.')

        # Challenge.cpp
        file = self.conf.get_class_file()
        if os.path.exists(file):
            sys.exit('File ' + file + ' already exists.')
        else:
            try:
                with open(file, 'w') as handle:
                    handle.write(self.get_class_content())
            except OSError:
                sys.exit('Sorry, could not write ' + file + '.')

        # ChallengeTest.cpp
        file = self.conf.get_test_file()
        if os.path.exists(file):
            sys.exit('File ' + file + ' already exists.')
        else:
            try:
                with open(file, 'w') as handle:
                    handle.write(self.get_test_content())
            except OSError:
                sys.exit('Sorry, could not write ' + file + '.')

    def get_main_content(self):
        text = '''
//
// Created by Elmar Hinz on {}.
//

#include "{}.h"

int main()
{{
    {} challenge;
    challenge.run();
    return 0;
}}        
        '''
        n = self.conf.get_challenge_name();
        return text.strip().format(datetime.today(), n, n)

    def get_header_content(self):
        text = '''
//
// Created by Elmar Hinz on {}.
//

#ifndef BLCKNX_{}_H
#define BLCKNX_{}_H

#include <Challenge.h>

class {} : public blcknx::Challenge {{

public:
    void build() override;

    void calc() override;

    void format() override;

protected:
}};


#endif //BLCKNX_{}_H
        '''
        n = self.conf.get_challenge_name();
        return text.strip().format(
            datetime.today(),
            n.upper(), n.upper(), n, n.upper
        )

    def get_class_content(self):
        text = '''
//
// Created by Elmar Hinz on {}.
//

#include "{}.h"

void {}::build() {{
}}

void {}::calc() {{
}}

void {}::format() {{
}}        
        '''
        n = self.conf.get_challenge_name();
        return text.strip().format(datetime.today(), n, n, n, n)

    def get_test_content(self):
        text = '''
//
// Created by Elmar Hinz on {}.
//

#include "gtest/gtest.h"
#define protected public
#define private public
#include "{}.h"

TEST({}_test, main)
{{
    {} challenge;
    std::string given = "";
    std::string expected = "";
    EXPECT_EQ(expected, challenge.main(given));
}}        
        '''
        n = self.conf.get_challenge_name();
        return text.strip().format(datetime.today(), n, n.lower(), n)

