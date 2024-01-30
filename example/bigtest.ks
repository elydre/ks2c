"XOR test (should be false true true false)" > print

0, 0 >> $a, $b >> not, not >> $not_a, $not_b
$a, $not_b, $b, $not_a >>>> and, and >> or > print

0, 1 >> $a, $b >> not, not >> $not_a, $not_b
$a, $not_b, $b, $not_a >>>> and, and >> or > print

1, 0 >> $a, $b >> not, not >> $not_a, $not_b
$a, $not_b, $b, $not_a >>>> and, and >> or > print

1, 1 >> $a, $b >> not, not >> $not_a, $not_b
$a, $not_b, $b, $not_a >>>> and, and >> or > print

"LOOP test (should be 0 1 2 3 4)" > print

5 > LOOP > $ > print
END

"LOOP test + mod (should be 1 3)" > print

5 > LOOP > $i
    $i % 2 > IF
        $i > print
    END
END
