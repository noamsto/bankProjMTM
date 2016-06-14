#!/bin/sh
#
#  rev.sh
#  
#  Yahel Tsufim 304952898
#  Noam Stolero 201581683

clear

echo "This script will reverse the text in each sentence"



#reverse text function, work on a single text file.
reverseText()  {
    
local text=() 
#set the IFS to '.' and read a line.    
while IFS='.' read -a line ; do

    for sen in "${line[@]}"; do #each sentence is now in line array, use sen to get them.
        local revSen=()
        local senArr=($sen) #convert the string to array.
        local len=${#senArr[@]}	#get the string length.

        for ((i=$len-1; i>=0 ; i--)); do    #run on the array reversed
            revSen=(${revSen[@]} ${senArr[$i]})
        done
        text=(${text[@]}${revSen[@]}'\n')   #save each line on a new line in text variable, will hold all the text.
    done
done <$1    #read next line from file.
echo ${text[@]} #return readed text.
}


for txt in $@; do   #do for each entered file name.
printf "`reverseText $txt`" > ${txt}rpl #print to new file.
banner "${txt}rpl"  #print filename with style.
cat ${txt}rpl   #print file.
done




