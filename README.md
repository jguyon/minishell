# 42 template c

Template to base [42 school](https://en.wikipedia.org/wiki/42_(school)) C projects on.

## Usage

```sh
git clone https://github.com/jguyon/42-template-c.git new_project && cd new_project
echo "NAME = progname" >> config.mk && echo "progname" >> .gitignore # Set executable name
rm srcs/hello.c includes/hello.h tests/test_hello.h # Remove example program and tests
# Write some code and tests
make && ./progname # Compile the program and run it
make fclean debug # Recompile with debug flags
make check # Compile and run the tests
make fclean && make release check # Test the release version
echo "DEFAULT_BUILD = debug" > local.mk # Compile the debug version by default on your local machine
npm install -g node-tap && echo "PROVE = tap" > local.mk # Change the tap output processor for tests
```
