# Проверить было ли передано два параметра
if [[ $# -ne 2 ]]
    then
    check="$1"
    if [[ $# -eq 0 ]]
       then
       echo "Please, enter some information below:"
       echo '"'"?"'"'" for help"
       echo '"'"generate"'"'" for generating new void files"
       echo "or <suffix>" 
       echo "   <username> for synonim creation"
       read check
    fi
    if [ $check = "?" ]||[ $check = "generate" ]
       then
	  echo " " 
       else
          suffix="$check"
          echo "Please, enter your username below"
          read username
    fi
    while [[ "$check" = "?"||"$check" = "generate" ]]
       do 
          if [[ "$check" == "?" ]]
             then
	        echo "For help"
	        echo "Usage: ?"
                echo "For synonim creation"  
                echo "Usage: <suffix>"
                echo "       <username>"
                echo "For extra files generation"
                echo "Usage: generate"
          fi
          if [[ "$check" == "generate" ]]
             then
                echo "Please, enter the suffix of files"
                read gen_suffix
		echo "Please, enter the number of files"
                read number
		if [[ $number < 0 ]]
		   then
			echo "Negative number of files? Interesting..."
			echo "...But you know, I can't do something like that :-)"
		   else
                      count=0
                      while [ $count -lt $number ]
                         do
                            (( count++ ))
                            echo "file$count.$gen_suffix"| xargs touch
                         done
                      count=0
		fi
          fi
	     echo "Please type "'"'"?"'"'", "'"'"generate"'"'" or <suffix>"
	     echo "                               <username> for continue"
	     read fix
	     check=${fix}
	     if [[ "${check}" == "?"||"${check}" == "generate" ]]
	     	then
		       continue	
	     	else
		   suffix=${check}
		   echo "Please, enter your username below"
		   read username
		   break
	     fi
          done
   else
      check=$1
      suffix=$check
      username=$2
fi

if [[ `echo ${suffix} | cut -c 1` == "." ]]
   then
       echo "Please, remove the dot at the beginning of suffix and write down it below again:"
       read suffix
fi
 
if [ ! -d "./synonyms" ]; then
    mkdir synonyms
fi
ls -l | grep -v "1 ${username}" | find *.${suffix} > list
 
for filename in $(cat list)
do
    resname=`echo $filename | sed "s/.$suffix//g"`
    ln "$filename" "./synonyms/${suffix}$resname"
done
