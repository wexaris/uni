
# Expected Results

|    Input    |     Expected Result   | ForwardList\<T> | ForwardList\<T*> |
|:-----------:|:---------------------:|:---------------:|:----------------:|
|  \<empty>   |        \<exit>        |        +        |        +         |
|    1 2 3    |         1 2 3         |        +        |        +         |
| a b c c b d |        a b c d        |        +        |        +         |
|  a aa a bb  |        a aa bb        |        +        |        +         |