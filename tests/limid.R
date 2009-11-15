library(RHugin, lib.loc = "../")
demo("buildLimidNetwork", echo = FALSE)

compile(limid)
set.finding(limid, "Loses", "yes")
propagate(limid)

get.utility(limid, "Treat")


