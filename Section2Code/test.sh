clear
if [ $# -eq 3 ]; then
    keyName=$1
    plaintextFile=$2
    ciphertextFile=$3
    echo "./Main.out"
    ./Main.out
    echo "./Main.out -k $keyName 128"
    ./Main.out -k $keyName 128
    echo "hexdump $keyName -C"
    hexdump $keyName -C
    for x in ECB CBC CTR
    do
	echo -e "\n\n$x"
	echo -e "\nEncryption"
	echo "./Main.out -e"
	./Main.out -e
	echo "./Main.out $keyName $plaintextFile.txt ${ciphertextFile}$x.txt $x"
	./Main.out -e $keyName "$plaintextFile.txt" "${ciphertextFile}$x.txt" $x
	echo -e "\nDecryption"
	echo "./Main.out -d"
	./Main.out -d
	echo "./Main.out $keyName ${ciphertextFile}$x.txt ${plaintextFile}$x.txt $x"
	./Main.out -d $keyName "${ciphertextFile}$x.txt" "${plaintextFile}$x.txt" $x
    done
else
    echo "Necesito tres argumentos"
fi
    

