# 42 template c

Template to base [42 school](https://en.wikipedia.org/wiki/42_(school)) C projects on.

## Usage

```sh
make # Compile the program
make fclean debug # Recompile with debug flags
make check # Compile and run the tests
make fclean && make release check # Test the release version
echo "DEFAULT_BUILD = debug" > local.mk # Compile the debug version by default on your local machine
npm install -g node-tap && echo "PROVE = tap" > local.mk # Change the tap output processor for tests
```
