#!/bin/sh

#  Script.sh
#  
#
#  Created by Noam Stolero on 4.6.2016.
#

clear

echo "This script will reverse the text in each sentence"

function reverseText  {
    local text=()

    while IFS='.' read -a line ; do

    for sen in "${line[@]}"; do
        local  revSen=()

        senArr=($sen)
        len=${#senArr[@]}

        for ((i=$len-1; i>=0 ; i--)); do
            revSen=(${revSen[@]} ${senArr[$i]})
        done
        text=(${text[@]}${revSen[@]}'\n')
        done
    done <$1

    echo ${text[@]}
}



for txt in "$*"; do
echo "`reverseText $txt`"
done




