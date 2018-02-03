#!/bin/bash

file=SubstringDivisibility.java

if [ ! -f "$file" ]; then
    echo -e "Error: File '$file' not found.\nTest failed."
    exit 1
fi

num_right=0
total=0
line="________________________________________________________________________"
compiler=
interpreter=
language=
extension=${file##*.}
if [ "$extension" = "py" ]; then
    if [ ! -z "$PYTHON_PATH" ]; then
        interpreter=$(which python.exe)
    else
        interpreter=$(which python3.2)
    fi
    command="$interpreter $file"
    echo -e "Testing $file\n"
elif [ "$extension" = "java" ]; then
    language="java"
    command="java ${file%.java}"
    echo -n "Compiling $file..."
    javac $file
    echo -e "done\n"
elif [ "$extension" = "c" ] || [ "$extension" = "cpp" ]; then
    language="c"
    command="./${file%.*}"
    echo -n "Compiling $file..."
    results=$(make 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "\n$results"
        exit 1
    fi
    echo -e "done\n"
fi


run_test_args() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$2
    received=$( $command $1 2>&1 | tr -d '\r' | sed -n '$!p')
    if [ "$expected" = "$received" ]; then
        echo "success"
        (( ++num_right ))
    else
        echo -e "failure\n\nExpected$line\n$expected\nReceived$line\n$received\n"
    fi
}

run_test_args "0123456789" "1406357289
1430952867
1460357289
4106357289
4130952867
4160357289
Sum: 16695334890"

run_test_args "0123" "0132
0312
1032
1230
1302
1320
2130
2310
3012
3102
3120
3210
Sum: 22212"

run_test_args "0213" "0132
0312
1032
1230
1302
1320
2130
2310
3012
3102
3120
3210
Sum: 22212"

run_test_args "1234" "1234
1324
1342
1432
2134
2314
3124
3142
3214
3412
4132
4312
Sum: 31116"

run_test_args "1357" "Sum: 0"

run_test_args "123456789" "149635728
419635728
Sum: 569271456"

run_test_args "915623874" "149635728
419635728
Sum: 569271456"

run_test_args "09876" "06789
06987
09687
09768
09786
09867
60789
60987
69087
69708
69780
69807
78069
78609
78906
78960
87069
87609
87906
87960
90687
90768
90786
90867
96087
96708
96780
96807
Sum: 1867620"

run_test_args "1265" "1256
1526
1562
1652
2156
2516
5126
5162
5216
5612
6152
6512
Sum: 44448"

run_test_args "976543210" "Sum: 0"

echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ "$language" = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
