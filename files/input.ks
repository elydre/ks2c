0 > $max

1 > $n
500000 > LOOP

    $n + 2 > $n
    1 > $j
    1 > $prime

    $n > sqrt > $max

    $max / 2 > LOOP
        $j + 2 > $j
        $n, $j >> mod > not > IF
            0 > $prime
            BREAK
            END
        END

    $prime > IF
        $n > printn
        END

    END