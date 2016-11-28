#!/bin/sh

export TESTFILE=tree/pressings/beats/schizoid/foo123
MESSAGE="Make sure this variable isn't empty"

ROOT='tree'
DIRA=$ROOT/modulator
DIRB=$DIRA/barrette
DIRC=$DIRB/alarmed/sulfuric/citations/indicting

QUOTE='
"One repays a teacher badly if one always remains nothing but a pupil." 
   ― Friedrich Nietzsche
'

test -d tree/images || mkdir tree/images

for img in tree/generated/bin64_images/[a-zA-Z]*.[jJgGpP][pPiInN][gGfF].txt
do
    newname=${img%.txt}
    newfile=$(basename $newname)
    if [ ! -f "tree/images/"$newname ]; then
        base64 -i -d $img > "tree/images/"$newfile
    fi
done

testfun(){
   test -e "$TESTFILE"
}

cat <<ENDSCRIPT > tree/modulator/creaks/heredoc
#!/bin/sh
echo "This heredoc script works awesome"
echo "Ok, all done"
exit 0
ENDSCRIPT

printf "$QUOTE" > tree/generated/splines/setbacks/victualed/steadies/quote
