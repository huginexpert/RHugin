library(RHugin, lib.loc = "../")
demo("limid", echo = FALSE)

compile(limid)
set.finding(limid, "Loses", "yes")
propagate(limid)

get.utility(limid, "Treat")


