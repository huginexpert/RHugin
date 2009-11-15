library(RHugin, lib.loc = "../")
demo("buildSimpleGaussianNetwork", echo = FALSE)

compile(simpleGaussianExample)
set.finding(simpleGaussianExample, "Z", 1.5)
propagate(simpleGaussianExample)

get.belief(simpleGaussianExample, "X")
get.belief(simpleGaussianExample, "Y")


