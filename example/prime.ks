5 > $n
$n -= 999999 > WHILE
    $n + 2 > $n
    $n % 2 == 0, $n % 3 == 0 >> or > IF
        CONTINUE
    END
    5 > $i
    $i * $i -= $n > WHILE
        $n % $i == 0 > IF
            0 > $i
            BREAK
        END
        $i + 2 > $i
        $n % $i == 0 > IF
            0 > $i
            BREAK
        END
        $i + 4 > $i
    END
    $i > IF
        $n > print
    END
END
