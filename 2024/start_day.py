import os
import sys

# Boilerplate C++ code
cpp_boilerplate = """#include <bits/stdc++.h>

using namespace std;

int main() {

}
"""

def create_day_folder(day_number):
    # Create folder name
    folder_name = f"Day{day_number}"
    
    try:
        # Create the folder
        os.makedirs(folder_name, exist_ok=True)
        
        # Create empty files
        for filename in ['input.txt', 'example.txt']:
            file_path = os.path.join(folder_name, filename)
            open(file_path, 'w').close()

        # Create C++ files with boilerplate
        for filename in ['gold.cc', 'silver.cc']:
            file_path = os.path.join(folder_name, filename)
            with open(file_path, 'w') as file:
                file.write(cpp_boilerplate)

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Check for command line argument
    if len(sys.argv) != 2:
        print("Usage: python start_day.py <day_number>")
        sys.exit(1)

    try:
        day_number = int(sys.argv[1])
        create_day_folder(day_number)
    except ValueError:
        print("Please provide a valid integer as the day number.")
