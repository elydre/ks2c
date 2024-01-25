100 > LOOP > $i
    $i % 3 == 0 > IF
        $i % 5 == 0 > IF
            "FizzBuzz" > print
        END
        ELSE
            "Fizz" > print
        END
        CONTINUE
    END

    $i % 5 == 0 > IF
        "Buzz" > print
    END
    ELSE
        $i > print
    END
END
