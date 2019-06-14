# minishell

A minimal shell. A [42 school](<https://en.wikipedia.org/wiki/42_(school)>) project.

## Usage

```sh
# Clone the project
git clone git@github.com:jguyon/minishell.git && cd minishell
git submodule init && git submodule update

make && ./minishell # Compile the program and run it
make fclean debug # Recompile with debug flags
make check # Compile and run the tests
make fclean && make release check # Test the release version
echo "DEFAULT_BUILD = debug" > local.mk # Compile the debug version by default on your local machine
npm install -g node-tap && echo "PROVE = tap" > local.mk # Change the tap output processor for tests
```
