#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
NC="\033[0m"

file_exists() {
    [ -e "$1" ] || [ -e "../$1" ]
}

check_files_and_display() {
    local file_list=("$@")
    local result="OK"
    for file in "${file_list[@]}"; do
        if file_exists "../$file"; then
            if [[ "$file" == "ft_"* ]]; then
                echo -e "\n[${GREEN}✔${NC}] $file"
            else
                echo -e "\n[${GREEN}✔${NC}] $file"
            fi
        else
            echo -e "\n[${RED}✖${NC}] $file"
            sleep 0.15
        fi
    done
}

print_info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

print_success() {
    echo -e "[${GREEN}✔${NC}] $1"
}

print_failure() {
    echo -e "[${RED}✖${NC}] $1"
}

makefile=("Makefile")
header=("libft.h")
function_files=("ft_strlcat.c" "ft_strlen.c" "ft_strlcpy.c" "ft_isalpha.c" "ft_isalnum.c" "ft_isdigit.c" "ft_isascii.c" "ft_isprint.c" "ft_strncmp.c" "ft_memset.c" "ft_bzero.c" "ft_memcpy.c" "ft_memmove.c" "ft_tolower.c" "ft_toupper.c" "ft_strchr.c" "ft_strrchr.c" "ft_strnstr.c" "ft_memchr.c" "ft_memcmp.c" "ft_atoi.c" "ft_calloc.c" "ft_strdup.c" "ft_substr.c" "ft_strjoin.c" "ft_strtrim.c" "ft_putendl_fd.c" "ft_strlen.c" "ft_strlcpy.c" "ft_putchar_fd.c" "ft_putnbr_fd.c" "ft_putstr_fd.c" "ft_striteri.c" "ft_strmapi.c" "ft_itoa.c" "ft_split.c")
bonus_function_files=("ft_lstnew_bonus.c" "ft_lstadd_front_bonus.c" "ft_lstsize_bonus.c" "ft_lstlast_bonus.c" "ft_lstadd_back_bonus.c" "ft_lstdelone_bonus.c" "ft_lstclear_bonus.c" "ft_lstiter_bonus.c" "ft_lstmap_bonus.c")

submission_status=(check_files_and_display "${function_files[@]}" "${bonus_function_files[@]}" "Makefile" "libft.h")

print_status "${submission_status[0]}"

#print_status(){
#   if [[ $1 == "success"]]: then
#       print_info "Cheking submitted files:"
#	print_status "Makefile"
#	print_status "libft.h"
#	print_status "Functions"
#	print_status "Bonus functions"
#  else
#	   print_info "Checking submitted files:"
#  print_status "Makefile"
#  print_status "libft.h"
#  print_status "Functions"
#  print_status "Bonus functions"
# fi

norminette_status="OK"

files_to_check=("$header" "${function_files[@]}" "${bonus_function_files[@]}")
for file in "${files_to_check[@]}"; do
    norminette "$file" > /dev/null 2>&1 || { norminette_status="Fail"; break; }
done

if [ "$norminette_status" == "OK" ]; then
    print_info "Norminette: OK"
else
    print_info "Norminette: Fail"
fi

print_info "Checking Makefile:"

rule_exists() {
    local rule_name="$1"
    grep -qE "^\s*$rule_name\s*:" "../Makefile"
}

#text_exists() {
#    local text="$1"
#     grep -qF "$text" "../Makefile"
#}

#variables_to_check=("NAME = libft.a")

#    for variable in "${variables_to_check[@]}"; do
#    	if text_exists "$variable"; then
#       	print_success "Variable: $variable"
#   	else
#        	print_failure "Variable: $variable"
#   	fi

    required_rules=("all" "clean" "fclean" "re" "bonus")
    missing_rules=""

    for rule in "${required_rules[@]}"; do
        if ! rule_exists "$rule"; then
            missing_rules="${missing_rules}, $rule"
        fi
    done
    
	if [ -z "$missing_rules" ]; then
        print_success "Rules:  all, clean, fclean, re, bonus"
    else
        print_failure "Rules missing:${missing_rules#, }"
    fi

makefile_timestamp=$(stat -c %Y ../Makefile > /dev/null 2>&1)
source_code_relinked=false
for source_file in "${submitted_files[@]}"; do
     if file_exists "../$source_file" && [ $(stat -c %Y "../$source_file"> /dev/null 2>&1) -gt "$makefile_timestamp" ]; then
         source_code_relinked=true
         break
     fi
 done
 if [ "$source_code_relinked" = true ]; then
     print_failure "No relink"
 else
     print_success "No relink"
 fi

bonus_relinked=false
for bonus_file in "${bonus_files[@]}"; do
     if file_exists "../$bonus_file" && [ $(stat -c %Y "../$bonus_file"> /dev/null 2>&1) -gt "$makefile_timestamp" ]; then
         bonus_relinked=true
         break
     fi
 done
 if [ "$bonus_relinked" = true ]; then
     print_failure "No bonus relink"
 else
     print_success "No bonus relink"
 fi

(cd .. && make > /dev/null 2>&1) && compiling_status="OK" || compiling_status="Fail"

print_info "Compiling: ${compiling_status}"

if [ "$compiling_status" == "OK" ]; then
    cp ../libft.h .
    cp ../libft.a .
else
    print_failure "Something failed. Skipping copy of libft.h and libft.a."
fi

gcc -Wall -Wextra -Werror -o libft_test_bavba libft_test_bavba.c -L. -lft #> /dev/null 2>&1

if [ $? -eq 0 ]; then
    ./libft_test_bavba > libft_test_result.txt
    print_info "Testing:"
    while IFS= read -r line; do
        if [[ $line == *"OK"* ]]; then
            print_success "$line"
        else
            print_failure "$line"
        fi
        sleep 0.15
    done < "libft_test_result.txt"
    mv libft_test_result.txt libft_test_results.log
else
    print_failure "Compilation failed."
fi

rm -f libft.a
rm -f libft.h

rm -f  ./libft_test_bavba
(cd .. && make -C .. clean > /dev/null 2>&1) && clean_status="OK" || clean_status="Fail"
print_info "Clean up: ${clean_status}"