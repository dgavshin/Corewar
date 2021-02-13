#!/usr/bin/zsh

TIMEOUT=20

make &>/dev/null

echo -e "\t\tDebug\tWinner"

function test() {

    filename=`basename $1`
    my_log=my_$filename.log
    orig_log=orig_$filename.log

    RES_DEBUG=0
    RES_WINNER=0

    printf %-18.12s "$filename"


    timeout $TIMEOUT ./corewar -v 31 champs/cor/$filename 2>/dev/null 1> ~/$my_log
    timeout $(($TIMEOUT / 10)) ./vm-champ-linux/corewar -v 31 champs/cor/$filename 2>/dev/null 1> ~/$orig_log
    my_len=$((`wc -l < ~/$my_log`))
    orig_len=$((`wc -l < ~/$orig_log`))

    if [ $my_len -lt $orig_len ]; then
        DIFF=$(diff <(head -n $(($my_len - 1)) ~/$my_log) <(head -n $(($my_len - 1)) ~/$orig_log))
    elif [ $my_len -eq $orig_len ]; then
        DIFF=$(diff ~/$my_log ~/$orig_log)
    else
        DIFF=$(diff <(head -n $(($orig_len - 1)) ~/$my_log) <(head -n $(($orig_len - 1)) ~/$orig_log))
    fi



    if [[ "$DIFF" != "" ]]; then
        echo -ne "❌"
        mv ~/$my_log logs
        mv ~/$orig_log logs
    else
        RES_DEBUG=1
        echo -ne "✔️"
        rm ~/$my_log
        rm ~/$orig_log
    fi

    DIFF=`diff <(./corewar champs/cor/$filename 2>/dev/null) <(./vm-champ-linux/corewar champs/cor/$filename 2>/dev/null)`

    echo -ne "       "
    if [[ "$DIFF" != "" ]]; then
        echo -ne "❌"
    else
        RES_WINNER=1
        echo -ne "✔️"
    fi
    echo ""
}

files=(`ls champs/cor/`)

foreach file in $files; do
    test $file
done
