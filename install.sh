#!/bin/bash

# Specify the directory to clone the repository
INSTALL_DIR="$HOME/cinnamon-interpreter"

# Clone the repository
git clone https://github.com/yucchannel/cinnamon.git "$INSTALL_DIR"

# Change to the project directory
cd "$INSTALL_DIR"

# Check if gcc is installed
if ! command -v gcc &> /dev/null
then
    echo "gcc is not installed. Installing gcc..."
    sudo apt-get update
    sudo apt-get install gcc
fi

# Build the project
make

# Completion message
echo "Installation complete. The cinnamon interpreter has been installed to '$INSTALL_DIR/cinnamon'."

# Verify installation
echo "Installation verification:"
"$INSTALL_DIR/cinnamon" "$INSTALL_DIR/examples/example.cin"
