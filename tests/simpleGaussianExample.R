library(RHugin)
demo("simple", echo = FALSE)

compile(simple)
set.finding(simple, "Z", 1.5)
propagate(simple)

get.belief(simple, "X")
get.belief(simple, "Y")


