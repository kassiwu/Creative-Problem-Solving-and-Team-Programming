#!/bin/bash
if [ ! -f "SubstringDivisibility.class" ]; then
    javac SubstringDivisibility.java
fi


total=0
num_right=0

received="$(java SubstringDivisibility 123)"
(( ++total ))
if [ "$received" = "The total digits of the input number should be between 4 and 10" ]; then
    echo "Testing passed: 123"
    (( ++num_right ))
else
    echo "Testing failed: 123"
fi


received="$(java SubstringDivisibility 1234 5678)"
(( ++total ))
if [ "$received" =  "Wrong number of args" ]; then
    echo "Testing passed: 1234 5678"
    (( ++num_right ))
else
    echo "Testing failed: 1234 5678"
fi

received="$(java SubstringDivisibility abcd)"
(( ++total ))
if [ "$received" = "Input value must be an integer" ]; then
    echo "Testing passed: abcd"
    (( ++num_right ))
else
    echo "Testing failed: abcd"
fi


received="$(java SubstringDivisibility 0123456789)"
(( ++total ))
if [[ "$received" = "1406357289
1430952867
1460357289
4106357289
4130952867
4160357289
Sum: 16695334890"* ]]; then
    echo "Testing passed: 0123456789"
    (( ++num_right ))
else
    echo "Testing failed: 0123456789"
fi


received="$(java SubstringDivisibility 0123)"
(( ++total ))
if [[ "$received" = "0132
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
Sum: 22212"* ]]; then
    echo "Testing passed: 0132"
    (( ++num_right ))
else
    echo "Testing failed: 0132"
fi


received="$(java SubstringDivisibility 0213)"
(( ++total ))
if [[ "$received" = "0132
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
Sum: 22212"* ]]; then
    echo "Testing passed: 0213"
    (( ++num_right ))
else
    echo "Testing failed: 0213"
fi


received="$(java SubstringDivisibility 1234)"
(( ++total ))
if [[ "$received" = "1234
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
Sum: 31116"* ]]; then
    echo "Testing passed: 1234"
    (( ++num_right ))
else
    echo "Testing failed: 1234"
fi


received="$(java SubstringDivisibility 1357)"
(( ++total ))
if [[ "$received" = "Sum: 0"* ]]; then
    echo "Testing passed: 1357"
    (( ++num_right ))
else
    echo "Testing failed: 1357"
fi


received="$(java SubstringDivisibility 123456789)"
(( ++total ))
if [[ "$received" = "149635728
419635728
Sum: 569271456"* ]]; then
    echo "Testing passed: 123456789"
(( ++num_right ))
else
    echo "Testing failed: 123456789"
fi


received="$(java SubstringDivisibility 915623874)"
(( ++total ))
if [[ "$received" = "149635728
419635728
Sum: 569271456"* ]]; then
    echo "Testing passed: 915623874"
    (( ++num_right ))
else
    echo "Testing failed: 915623874"
fi


received="$(java SubstringDivisibility 09876)"
(( ++total ))
if [[ "$received" = "06789
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
Sum: 1867620"* ]]; then
    echo "Testing passed: 09876"
    (( ++num_right ))
else
    echo "Testing failed: 09876"
fi


received="$(java SubstringDivisibility 1265)"
(( ++total ))
if [[ "$received" = "1256
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
Sum: 44448"* ]]; then
    echo "Testing passed: 1265"
    (( ++num_right ))
else
    echo "Testing failed: 1265"
fi


received="$(java SubstringDivisibility 976543210)"
(( ++total ))
if [[ "$received" = "Sum: 0"* ]]; then
    echo "Testing passed: 976543210"
    (( ++num_right ))
else
    echo "Testing failed: 976543210"
fi


echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc
