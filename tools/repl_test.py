# Copyright 2018 the Deno authors. All rights reserved. MIT license.
import os
from subprocess import PIPE, Popen
from time import sleep

from util import build_path, executable_suffix


class Repl(object):
    def __init__(self, deno_exe):
        self.deno_exe = deno_exe

    def run(self, *lines, **kwargs):
        exit_ = kwargs.pop("exit", True)
        p = Popen([self.deno_exe], stdout=PIPE, stderr=PIPE, stdin=PIPE)
        try:
            for line in lines:
                p.stdin.write(line.encode("utf-8") + b'\n')
            if exit_:
                p.stdin.write(b'deno.exit(0)\n')
            else:
                sleep(1)  # wait to be killed by js
            out, err = p.communicate()
        except Exception as e:  # Should this be CalledProcessError?
            p.kill()
            p.wait()
            raise
        retcode = p.poll()
        return out, err, retcode

    def warm_up(self):
        # This may output an error message about the history file (ignore it)
        self.run("")

    def function_test(self):
        out, err, code = self.run("deno.writeFileSync")
        assert out == '[Function: writeFileSync]\n'
        assert err == ''
        assert code == 0

    def console_log_test(self):
        out, err, code = self.run("console.log('hello')", "'world'")
        assert out == 'hello\nundefined\nworld\n'
        assert err == ''
        assert code == 0

    def variable_test(self):
        out, err, code = self.run("var a = 123;", "a")
        assert out == 'undefined\n123\n'
        assert err == ''
        assert code == 0

    def settimeout_test(self):
        out, err, code = self.run(
            "setTimeout(() => { console.log('b'); deno.exit(0); }, 10)",
            "'a'",
            exit=False)
        assert out == '1\na\nb\n'
        assert err == ''
        assert code == 0

    def reference_error_test(self):
        out, err, code = self.run("not_a_variable")
        assert out == ''
        assert err == "ReferenceError: not_a_variable is not defined\n"
        assert code == 0

    def syntax_error_test(self):
        out, err, code = self.run("syntax error")
        assert out == ''
        assert err == "SyntaxError: Unexpected identifier\n"
        assert code == 0

    def type_error_test(self):
        out, err, code = self.run("console()")
        assert out == ''
        assert err == "TypeError: console is not a function\n"
        assert code == 0

    def exit_command_test(self):
        out, err, code = self.run(".exit", "'ignored'", exit=False)
        assert out == ''
        assert err == ''
        assert code == 0

    def tests(self):
        self.warm_up()
        self.function_test()
        self.console_log_test()
        self.variable_test()
        self.settimeout_test()
        self.reference_error_test()
        self.syntax_error_test()
        self.type_error_test()
        self.exit_command_test()


def repl_tests(deno_exe):
    Repl(deno_exe).tests()


if __name__ == "__main__":
    deno_exe = os.path.join(build_path(), "deno" + executable_suffix)
    repl_tests(deno_exe)
