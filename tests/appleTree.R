library(RHugin, lib.loc = "../")
demo("apple", echo = FALSE)

compile(apple)
set.finding(apple, "Loses", "yes")
propagate(apple)

get.belief(apple, "Sick")
get.belief(apple, "Dry")


