#!/bin/bash

# Path to your Minishell executable
MINISHELL="./minishell"

# Function to print colored text
print_in_color() {
    color_code="$1"
    text="$2"
    echo -e "\033[${color_code}m${text}\033[0m"
}

# Function to run a test case
run_test() {
    command="$1"
    expected_output=$(eval "$command")  # Run the command in the real shell for expected output

    # Run command in minishell and store output
    minishell_output=$(echo "$command" | $MINISHELL)

    # Remove the prompt (e.g., "Minishell>") from the Minishell output
    cleaned_output=$(echo "$minishell_output" | sed 's/Verishen: .*//g' | sed '/^$/d')

    # Compare the cleaned Minishell output with expected output
    if [ "$cleaned_output" == "$expected_output" ]; then
        print_in_color "32" "Test passed: '$command'"  # Green for passed
    else
        print_in_color "31" "Test failed: '$command'"  # Red for failed
        print_in_color "33" "Expected: '$expected_output'"  # Yellow for expected output
        print_in_color "36" "Got: '$cleaned_output'"  # Cyan for actual output
    fi
}

# Read the test cases from a file
while IFS= read -r command; do
    run_test "$command"
done < "test_cases.txt"
