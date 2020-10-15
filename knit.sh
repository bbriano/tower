for file in $(ls *.h *.cpp); do
    echo "# $file\n\`\`\`cpp\n""$(cat $file)""\n\`\`\`";
done | pandoc -V geometry:margin=1in -f markdown -o code.pdf
open code.pdf
