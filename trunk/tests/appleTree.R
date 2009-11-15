library(RHugin, lib.loc = "../")
demo("buildAppleTreeNetwork", echo = FALSE)

compile(AppleTree)
set.finding(AppleTree, "Loses", "yes")
propagate(AppleTree)

get.belief(AppleTree, "Sick")
get.belief(AppleTree, "Dry")


