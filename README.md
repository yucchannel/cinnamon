# Cinnamon Programming Language

`Cinnamon` is a custom, C-like programming language designed for simplicity and flexibility. It features basic arithmetic operations, user-defined functions, and an extensible plugin system to load and execute external code. It is designed to be easy to understand and work with, providing a minimalistic yet functional experience for developers.

## Features

- **Basic Arithmetic**: Supports addition and number manipulation.
- **Variables**: Simple variable declarations and assignments.
- **Functions**: User-defined functions with parameters.
- **Plugins**: An extensible plugin system allowing external code to be loaded and executed.
- **C-like Syntax**: Designed to be similar to C, making it easy for C/C++ developers to pick up.

## Installation

You can install and build `cinnamon` from source using `git` and `make`. Follow the steps below:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/Yuto_DEVELOP/cinnamon.git
   cd cinnamon
   ```

2. **Build the project** using `make`:
   ```bash
   make
   ```

   This will compile the `cinnamon` interpreter. You will get an executable named `cinnamon`.

3. **Run the interpreter**:
   After building, you can run `cinnamon` with a `.cin` file:
   ```bash
   ./cinnamon1 example.cin
   ```

   Replace `example.cin` with your own `.cin` source code.

## Example

### Example `example.cin`

```cinnamon
// This is a simple example of a Cinnamon program

int main() {
    int a = 5;
    int b = 10;
    int result = a + b;
    
    print(result); // This will print: 15
    return 0;
}
```

### Running the Example

To run the example:

1. Save the above code into a file named `example.cin`.
2. Run the following command:
   ```bash
   ./cinnamon example.cin
   ```

   Output:
   ```
   15
   ```

## Plugin System

`Cinnamon` supports an extensible plugin system. Plugins are shared libraries that can be loaded dynamically and execute custom functions. Plugins are specified by name and executed when their corresponding function is called.

### Adding Plugins

1. **Create a Plugin**: Write your plugin in a separate C file. For example, create a `print_plugin.c` file:
   
   ```c
   #include <stdio.h>

   void print_plugin(const char *message) {
       printf("Plugin Message: %s\n", message);
   }
   ```

2. **Compile the Plugin**: Compile the plugin as a shared library:
   ```bash
   gcc -shared -o print_plugin.so -fPIC print_plugin.c
   ```

3. **Use the Plugin**: In your Cinnamon program, you can load and execute the plugin:

   ```cinnamon
   // Example usage of a plugin
   load_plugin("print_plugin.so");
   print_plugin("Hello from the plugin!");
   ```

### Loading Plugins

Plugins are loaded using the `load_plugin` function, and their functionality is executed by calling the appropriate plugin function.

Example:
```bash
./cinnamon my_program_with_plugins.cin
```

## File Structure

Here is the structure of the `cinnamon` repository:

```
cinnamon1/
├── LICENSE            # MIT License file
├── README.md          # Project description and instructions
├── src/               # Source code for cinnamon interpreter
│   └── cinnamon_interprenter.c        # main script
├── examples/          # Example Cinnamon programs
│   └── example.cin    # Example source file for cinnamon
├── Makefile           # Build script
├── LICENSE            # MIT License file (copy)
└── README.md          # Project description and instructions
```

## Contributing

Contributions to `cinnamon` are welcome! If you'd like to contribute, follow these steps:

1. Fork the repository.
2. Create a new branch for your changes.
3. Make your changes and commit them.
4. Push your changes to your fork.
5. Submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
```
