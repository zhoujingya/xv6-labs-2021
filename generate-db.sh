#! env bash

mkdir build || true

make --always-make --dry-run \
 | grep -wE 'gcc|g\+\+' \
 | grep -w '\-c' \
 | jq -nR '[inputs|{directory:"'$(pwd)'", command:., file: match(" [^ ]+$").string[1:]}]' \
 > build/compile_commands.json
