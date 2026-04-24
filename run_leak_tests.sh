#!/bin/bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell <<< "ls > /dev/null"
valgrind --leak-check=full --show-leak-kinds=all ./minishell << 'EOF'
cat << DELIM > /dev/null
test
DELIM
EOF
valgrind --leak-check=full --show-leak-kinds=all ./minishell <<< "export A=1; export A=2; unset A"
