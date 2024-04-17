#!/bin/zsh

random_numbers=""
target_length=$((RANDOM % 50 + 1))

while [[ ${#random_numbers} -lt $target_length ]]; do
    block_length=$((RANDOM % 5 + 1))
    random_block=""

    for digit_position in $(seq $block_length); do
        generated_digit=$((RANDOM % 10))
        random_block="${random_block}${generated_digit}"
    done

    [[ -n $random_numbers ]] && random_numbers="${random_numbers} $random_block" || random_numbers="${random_block}"
done

echo "$random_numbers"

